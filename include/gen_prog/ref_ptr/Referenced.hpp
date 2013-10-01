///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/Referenced.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__REFERENCED_HPP_
#define GEN_PROG__REF_PTR__REFERENCED_HPP_


#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/thread_policy/single_thread.hpp>



namespace gen_prog
{

class empty_class {};

template <typename 	T,
          class 	ThreadPolicy,
          class 	BaseClass>
class Referenced;


template <class ReferenceT, typename T, class ThreadPolicy>
class observer_set : public Referenced<T, ThreadPolicy, typename ThreadPolicy::mutex_wrapper>
{
public:
    typedef T 										                            		counter_type;
    typedef ReferenceT 										                            referenced_type;
    typedef referenced_type* 										                    referenced_poiner_type;
    typedef ThreadPolicy 										                        thread_policy;


public:
    observer_set():_observed_ptr(0) {}

    void signal_delete()
    {
        typename thread_policy::lock_guard lock(*this);
        _observed_ptr = GEN_PROG__NULL;
    }

    referenced_type * add_ref_lock()
    {
        if ( ! _observed_ptr ) return GEN_PROG__NULL;

        typename thread_policy::lock_guard lock(*this);

        if (_observed_ptr->ref() == 1)
        {
            // _observed_ptr is currently in its delete function,
            // but signal_delete is not yet call or blocked by lock
            // of this function. nothing to do, just leave
            _observed_ptr->unref_nodelete();
            return GEN_PROG__NULL;
        }

        return _observed_ptr;
    }


protected:
    observer_set(const observer_set & other): _observed_ptr(GEN_PROG__NULL) {}
    const observer_set & operator = (const observer_set & other) { return *this; }
    ~observer_set() {}


private:
    referenced_poiner_type _observed_ptr;
};





template <typename 	T				= unsigned int,
          class 	ThreadPolicy	= single_thread,
          class 	BaseClass		= empty_class>
class Referenced : public BaseClass
{
public:
    typedef T 													counter_type;
    typedef ThreadPolicy 										thread_policy;
    typedef BaseClass 											base_class;

    typedef Referenced                                          this_type;

    typedef observer_set<this_type, counter_type, thread_policy>  observer_set_type;

    typedef typename thread_policy::template thread_safe_type<counter_type>::type           counter_impl;
    typedef typename thread_policy::template thread_safe_type<observer_set_type*>::type     observer_set_impl;


public:
    Referenced(): _counter(0), _observer_set(GEN_PROG__NULL) {}
    Referenced(const Referenced &): _counter(0), _observer_set(GEN_PROG__NULL) {}


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

    observer_set_type * get_observer_set() const { return thread_policy::get(_observer_set); }
    observer_set_type * get_or_create_observer_set()
    {
        observer_set_type * observers = get_observer_set();
        if ( ! observers )
        {
            observer_set_type * new_observers = new observer_set_type(this);
            new_observers->ref();
            if (thread_policy::compare_exchange(_observer_set, observers, new_observers))
            {
                observers = new_observers;
            }
            else
            {
                new_observers->unref();
            }
        }
        return observers;
    }


protected:
    virtual ~Referenced()
    {
        observer_set_type * observers = get_observer_set();
        if ( observers )
        {
            observers->signal_delete();
            observers->unref();
        }
    }


private:
    mutable counter_impl _counter;
    mutable observer_set_impl _observer_set;
};



}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__REFERENCED_HPP_ ** //
// End of file
