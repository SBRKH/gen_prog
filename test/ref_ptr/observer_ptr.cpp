///////////////////////////////////////////////////////////////////////////////
/// \file test/ref_ptr/accessor.cpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



#include <boost/test/unit_test.hpp>

#include "common.hpp"
#include <gen_prog/ref_ptr/observer_ptr.hpp>

class Node;

BOOST_AUTO_TEST_SUITE( observer_ptr )

BOOST_AUTO_TEST_CASE_TEMPLATE( re_ptr_assign_operator, T, ThreadPolicies )
{
    typedef referenced<unsigned int, T> referenced_type;

    referenced_type * ptr = new referenced_type;
    ref_ptr<referenced_type> refPtr = ptr;
    gen_prog::observer_ptr<referenced_type> observerPtr = refPtr;

    referenced_type * ptr2 = refPtr;

    BOOST_CHECK_EQUAL( ptr, ptr2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( unknow_type_ptr, T, ThreadPolicies )
{
    typedef gen_prog::ref_ptr<Node> refPtr;
    typedef gen_prog::observer_ptr<Node> observerPtr;
}


BOOST_AUTO_TEST_SUITE_END()

