///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/thread_policy/ref_ptr/boost_mutex.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__THREAD_POLICY__BOOST_MUTEX_HPP_
#define GEN_PROG__REF_PTR__THREAD_POLICY__BOOST_MUTEX_HPP_


#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>


namespace gen_prog
{

struct boost_mutex
{
    template <typename T>
    struct MutexGuardCounter
    {
        MutexGuardCounter():
            _counter(0)
        {}
        MutexGuardCounter(T t):
            _counter(t)
        {}
        MutexGuardCounter(const MutexGuardCounter &):
            _counter(0)
        {}
        boost::mutex _mutex;
        T _counter;
    };

    template <typename T>
    struct counter
    {
        typedef MutexGuardCounter<T> type;
    };

    template <typename T>
    static T increment(MutexGuardCounter<T> & t)
    {
        boost::lock_guard<boost::mutex> locker(t._mutex);
        return ++t._counter;
    }

    template <typename T>
    static T decrement(MutexGuardCounter<T> & t)
    {
        boost::lock_guard<boost::mutex> locker(t._mutex);
        return --t._counter;
    }

    template <typename T>
    static T get(const MutexGuardCounter<T> & t)
    {
        return t._counter;
    }
};


}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__THREAD_POLICY__BOOST_MUTEX_HPP_ ** //
// End of file
