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
#include <gen_prog/ref_ptr/policy/thread/boost_atomic.hpp>
#endif

#ifdef GEN_PROG__BOOST_THREAD_AVAILABLE
#include <gen_prog/ref_ptr/policy/thread/boost_mutex.hpp>
#endif

#include <gen_prog/ref_ptr/policy/thread/single_thread.hpp>

#ifdef GEN_PROG__CXX11_AVAILABLE
#include <gen_prog/ref_ptr/policy/thread/std_atomic.hpp>
#endif


#include <gen_prog/ref_ptr/policy/delete_handler/no_delete_handler.hpp>
#include <gen_prog/ref_ptr/policy/delete_handler/static_delete_handler.hpp>
#include <gen_prog/ref_ptr/policy/delete_handler/local_delete_handler.hpp>

using namespace gen_prog;

#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>

// thread policy list
typedef boost::mpl::vector< single_thread

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

// delete_handler policy list
typedef boost::mpl::vector< no_delete_handler, static_delete_handler, local_delete_handler > DeleteHandlerPolicies;


//struct EmptyMix {};
//template< typename SequenceT, class MixPolicyT=EmptyMix >
//struct MixPolicy
//{
//    typedef boost::mpl::transform<SequenceT, >::type type;
//
//
//};

typedef boost::mpl::vector< > EmptyList;



//typedef MixPolicy< DeleteHandlerPolicies,
//                   MixPolicy<ThreadPolicies>
//                   >::type policies;

template <typename T>
class Derived : public referenced<unsigned int, T>
{};

#endif // ** TEST__REF_PTR__COMMON_HPP_ ** //
// End of file
