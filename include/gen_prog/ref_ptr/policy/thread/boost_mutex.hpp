///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/policy/thread/boost_mutex.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__POLICY__THREAD__BOOST_MUTEX_HPP_
#define GEN_PROG__REF_PTR__POLICY__THREAD__BOOST_MUTEX_HPP_



#include <boost/thread/locks.hpp>
#include <boost/thread/mutex.hpp>



namespace gen_prog
{

struct boost_mutex
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
    struct MutexGuardElement
    {
        MutexGuardElement():
            _element(0)
        {}
        MutexGuardElement(T t):
            _element(t)
        {}
        MutexGuardElement(const MutexGuardElement &):
            _element(0)
        {}
        boost::mutex _mutex;
        T _element;
    };

    template <typename T>
    struct thread_safe_type
    {
        typedef MutexGuardElement<T> type;
    };

    template <typename T>
    static T increment(MutexGuardElement<T> & t)
    {
        boost::lock_guard<boost::mutex> locker(t._mutex);
        return ++t._element;
    }

    template <typename T>
    static T decrement(MutexGuardElement<T> & t)
    {
        boost::lock_guard<boost::mutex> locker(t._mutex);
        return --t._element;
    }

    template <typename T>
    static T decrement_before_delete(MutexGuardElement<T> & t)
    {
        return decrement(t);
    }

    template <typename T>
    static T get(const MutexGuardElement<T> & t)
    {
#ifdef GEN_PROG__USE_LESS_32_BIT_PROCESSOR
        boost::lock_guard<boost::mutex> locker(t._mutex);
#endif
        return t._element;
    }

    template <typename T>
    static void set(MutexGuardElement<T> & t, const T & value)
    {
        boost::lock_guard<boost::mutex> locker(t._mutex);
        t._element = value;
    }

    template <typename T>
    static bool compare_exchange(MutexGuardElement<T> & t, T & expected, const T & value)
    {
        boost::lock_guard<boost::mutex> locker(t._mutex);
        if (t._element == expected)
        {
            t._element = value;
            return true;
        }
        else
        {
            expected = t._element;
            return false;
        }
    }
};


}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__POLICY__THREAD__BOOST_MUTEX_HPP_ ** //
// End of file
