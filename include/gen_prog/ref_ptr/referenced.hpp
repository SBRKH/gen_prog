///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/referenced.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__REFERENCED_HPP_
#define GEN_PROG__REF_PTR__REFERENCED_HPP_



#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/observer.hpp>
#include <gen_prog/ref_ptr/referenced_fwd.hpp>
#include <gen_prog/ref_ptr/referenced_definition.hpp>
#include <gen_prog/ref_ptr/policy/delete_handler/no_delete_handler.hpp>
#include <gen_prog/ref_ptr/policy/thread/single_thread.hpp>


namespace boost
{
template<class T>
void checked_delete(T *);
}


namespace gen_prog
{

template <typename T,
          class    ThreadPolicy,
          class    DeleteHandlerPolicy,
          class    BaseClassT>
class referenced : public referenced_definition<T,
                                                ThreadPolicy,
                                                DeleteHandlerPolicy,
                                                BaseClassT>::base_class
{
    typedef referenced_definition<T,
                                  ThreadPolicy,
                                  DeleteHandlerPolicy,
                                  BaseClassT>                   definition;


public:
    typedef typename definition::counter_type                   counter_type;
    typedef typename definition::thread_policy                  thread_policy;
    typedef typename definition::delete_handler_policy          delete_handler_policy;

    typedef typename definition::referenced_type                this_type;
    typedef typename definition::observer_type                  observer_type;

    typedef typename definition::base_class                     base_class;

    typedef typename definition::delete_handler_wrapper         delete_handler_wrapper;
    typedef typename definition::delete_handler                 delete_handler;


private:
    typedef typename definition::counter_impl                   counter_impl;
    typedef typename definition::observer_impl                  observer_impl;


public:
    referenced(): _counter(0), _observer(GEN_PROG__NULL) {}
    referenced(const referenced &): _counter(0), _observer(GEN_PROG__NULL) {}

    const referenced & operator = (const referenced &) { return *this; }


    ///////////////////////////////////////////////////////////////////////////
    // reference counter interface
    ///////////////////////////////////////////////////////////////////////////
    counter_type ref() const { return thread_policy::increment(_counter); }
    counter_type unref() const
    {
        counter_type newRefCount = thread_policy::decrement(_counter);
        if (newRefCount == 0) this->delete_handler_wrapper::do_delete( this );
        return newRefCount;
    }
    counter_type unref_nodelete() const { return thread_policy::decrement(_counter); }

    counter_type ref_count() const { return thread_policy::get(_counter); }



    ///////////////////////////////////////////////////////////////////////////
    // observer interface
    ///////////////////////////////////////////////////////////////////////////
    observer_type * get_observer() const { return thread_policy::get(_observer); }
    observer_type * get_or_create_observer()
    {
        observer_type * current_observer = get_observer();
        if ( ! current_observer )
        {
            observer_type * new_observer = new observer_type(this);
            new_observer->ref();

            if (thread_policy::compare_exchange(_observer, current_observer, new_observer))
            {
                current_observer = new_observer;
            }
            else
            {
                new_observer->unref();
            }
        }
        return current_observer;
    }


    ///////////////////////////////////////////////////////////////////////////
    // delete handler interface
    // define in DeleteHandlerPolicy implementation
    ///////////////////////////////////////////////////////////////////////////
    //(static) bool set_delete_handler(delete_handler * dh);
    //(static) delete_handler * get_delete_handler();


protected:
    virtual ~referenced()
    {
        observer_type * current_observer = get_observer();
        if ( current_observer )
        {
            current_observer->signal_delete();
            current_observer->unref();
        }
    }


private:
    mutable counter_impl _counter;
    mutable observer_impl _observer;
};



}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__REFERENCED_HPP_ ** //
// End of file
