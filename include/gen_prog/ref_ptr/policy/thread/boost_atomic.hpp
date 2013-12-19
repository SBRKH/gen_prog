///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/policy/thread/boost_atomic.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__POLICY__THREAD__BOOST_ATOMIC_HPP_
#define GEN_PROG__REF_PTR__POLICY__THREAD__BOOST_ATOMIC_HPP_



#include <boost/atomic.hpp>
#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>



 namespace gen_prog
 {

struct boost_atomic
{
    template <class BaseClassT>
    struct mutex_wrapper : public BaseClassT
    {
        mutex_wrapper() {}
        mutex_wrapper(const mutex_wrapper & ) {}
        virtual ~mutex_wrapper() {}

        const mutex_wrapper & operator = (const mutex_wrapper & ) {}
        mutable boost::mutex _mutex;
    };

    struct lock_guard
    {
        template <class MutexWrapperT>
        lock_guard(const MutexWrapperT & wrapper): _locker(wrapper._mutex) {}
        boost::lock_guard<boost::mutex> _locker;
    };


    template <typename T>
    struct thread_safe_type { typedef boost::atomic<T> type; };

    template <typename T>
    static T increment(boost::atomic<T> & t) { return t.fetch_add(1, boost::memory_order_relaxed)+1; }

    template <typename T>
    static T decrement(boost::atomic<T> & t) { return t.fetch_sub(1, boost::memory_order_relaxed)-1; }

    template <typename T>
    static T decrement_before_delete(boost::atomic<T> & t)
    {
        T new_value = t.fetch_sub(1, boost::memory_order_release)-1;
        if ( ! new_value )
            boost::atomic_thread_fence(boost::memory_order_acquire);
        return new_value;
    }

    template <typename T>
    static T get(boost::atomic<T> & t) { return t.load(boost::memory_order_relaxed); }

    template <typename T>
    static void set(boost::atomic<T> & t, const T & value) { t.store(value, boost::memory_order_relaxed); }

    template <typename T>
    static bool compare_exchange(boost::atomic<T> & t, T & expected, const T & value)
    { return t.compare_exchange_strong(expected, value, boost::memory_order_acq_rel, boost::memory_order_relaxed); }
};

} // namespace gen_prog




#endif // ** GEN_PROG__REF_PTR__POLICY__THREAD__BOOST_ATOMIC_HPP_ ** //
// End of file
