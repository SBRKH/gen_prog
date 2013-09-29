///////////////////////////////////////////////////////////////////////////////
/// \file test/ref_ptr/common.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef TEST__REF_PTR__COMMON_HPP_
#define TEST__REF_PTR__COMMON_HPP_



#include <gen_prog/ref_ptr.hpp>

#ifdef GEN_PROG__BOOST_ATOMIC_AVAILABLE
#include <gen_prog/ref_ptr/thread_policy/boost_atomic.hpp>
#endif

#ifdef GEN_PROG__BOOST_THREAD_AVAILABLE
#include <gen_prog/ref_ptr/thread_policy/boost_mutex.hpp>
#endif

#include <gen_prog/ref_ptr/thread_policy/single_thread.hpp>

#ifdef GEN_PROG__CXX11_AVAILABLE
#include <gen_prog/ref_ptr/thread_policy/std_atomic.hpp>
#endif



using namespace gen_prog;


#include <boost/mpl/vector.hpp>

typedef boost::mpl::vector<single_thread

#ifdef GEN_PROG__BOOST_ATOMIC_AVAILABLE
		,boost_atomic
#endif

#ifdef GEN_PROG__BOOST_THREAD_AVAILABLE
		,boost_mutex
#endif

#ifdef GEN_PROG__CXX11_AVAILABLE
		, std_atomic
#endif
		> ThreadPolicies;



template <typename T>
class Derived : public Referenced<unsigned int, T>
{};



#endif // ** TEST__REF_PTR__COMMON_HPP_ ** //
// End of file
