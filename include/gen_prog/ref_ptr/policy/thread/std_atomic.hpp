///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/policy/thread/std_atomic.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__POLICY__THREAD__STD_ATOMIC_HPP_
#define GEN_PROG__REF_PTR__POLICY__THREAD__STD_ATOMIC_HPP_



#include <atomic>
#include <mutex>



namespace gen_prog
{

struct std_atomic
{
    template <class BaseClassT>
    struct mutex_wrapper : public BaseClassT
    {
        mutex_wrapper() {}
        mutex_wrapper(const mutex_wrapper & ) {}
        virtual ~mutex_wrapper() {}

        const mutex_wrapper & operator = (const mutex_wrapper & ) {}
        mutable std::mutex _mutex;
    };

    struct lock_guard
    {
        template <class MutexWrapperT>
        lock_guard(const MutexWrapperT & wrapper): _locker(wrapper._mutex) {}
        std::lock_guard<std::mutex> _locker;
    };


    template <typename T>
    struct thread_safe_type { typedef std::atomic<T> type; };

    template <typename T>
    static T increment(std::atomic<T> & t) { return t.fetch_add(1, std::memory_order_relaxed)+1;; }

    template <typename T>
    static T decrement(std::atomic<T>  & t) { return t.fetch_sub(1, std::memory_order_relaxed)-1; }

    template <typename T>
    static T decrement_before_delete(std::atomic<T> & t)
    {
        T new_value = t.fetch_sub(1, std::memory_order_release)-1;
        if ( ! new_value )
            std::atomic_thread_fence(std::memory_order_acquire);
        return new_value;
    }

    template <typename T>
    static T get(const std::atomic<T> & t) { return t.load(std::memory_order_relaxed); }

    template <typename T>
    static void set(std::atomic<T> & t, const T & value) { t.store(value); }

    template <typename T>
    static bool compare_exchange(std::atomic<T> & t, T & expected, const T & value)
    { return t.compare_exchange_strong(expected, value, std::memory_order_acq_rel, std::memory_order_relaxed); }
};

} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__POLICY__THREAD__STD_ATOMIC_HPP_ ** //
// End of file
