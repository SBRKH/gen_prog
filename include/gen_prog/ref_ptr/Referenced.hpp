///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/Referenced.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__REFERENCED_HPP_
#define GEN_PROG__REF_PTR__REFERENCED_HPP_



#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/observer.hpp>
#include <gen_prog/ref_ptr/thread_policy/single_thread.hpp>



namespace gen_prog
{

class empty_class {};


template <typename T            = unsigned int,
          class    ThreadPolicy = single_thread,
          class    BaseClass    = empty_class>
class Referenced : public BaseClass
{
public:
    typedef T                                                   counter_type;
    typedef ThreadPolicy                                        thread_policy;
    typedef BaseClass                  							base_class;

    typedef Referenced                                          this_type;
    typedef Referenced                                          referenced_type;

    typedef observer<this_type>                                 observer_type;

    typedef typename thread_policy::template thread_safe_type<counter_type>::type       counter_impl;
    typedef typename thread_policy::template thread_safe_type<observer_type*>::type     observer_impl;


public:
    Referenced(): _counter(0), _observer(GEN_PROG__NULL) {}
    Referenced(const Referenced &): _counter(0), _observer(GEN_PROG__NULL) {}


    const Referenced & operator = (const Referenced &) { return *this; }


    counter_type ref() const { return thread_policy::increment(_counter); }
    counter_type unref() const
    {
        counter_type newRefCount = thread_policy::decrement(_counter);
        if (newRefCount == 0) delete this;
        return newRefCount;
    }
    counter_type unref_nodelete() const { return thread_policy::decrement(_counter); }

    counter_type ref_count() const { return thread_policy::get(_counter); }

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


protected:
    virtual ~Referenced()
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
