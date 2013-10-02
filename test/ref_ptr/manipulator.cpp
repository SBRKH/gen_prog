///////////////////////////////////////////////////////////////////////////////
/// \file test/ref_ptr/manipulator.cpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



#include <boost/test/unit_test.hpp>

#include "common.hpp"



BOOST_AUTO_TEST_SUITE( manipulator )

BOOST_AUTO_TEST_CASE_TEMPLATE( pointer_assign_operator, T, ThreadPolicies )
{
    typedef referenced<unsigned int, T> referenced_type;

    referenced_type * ptr = new referenced_type;
    ref_ptr<referenced_type> refPtr = ptr;

    BOOST_CHECK_EQUAL( refPtr.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 1 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( assign_operator, T, ThreadPolicies )
{
    typedef referenced<unsigned int, T> referenced_type;

    referenced_type * ptr = new referenced_type;
    ref_ptr<referenced_type> refPtr = ptr;
    ref_ptr<referenced_type> refPtr2 = refPtr;

    BOOST_CHECK_EQUAL( refPtr2.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( other_pointer_assign_operator, T, ThreadPolicies )
{
    typedef referenced<unsigned int, T> referenced_type;
    typedef Derived<T> derived_type;

    derived_type * ptr = new derived_type;
    ref_ptr<referenced_type> refPtr = ptr;

    BOOST_CHECK_EQUAL( refPtr.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 1 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( other_assign_operator, T, ThreadPolicies )
{
    typedef referenced<unsigned int, T> referenced_type;
    typedef Derived<T> derived_type;

    derived_type * ptr = new derived_type;

    ref_ptr<derived_type> refPtr = ptr;
    ref_ptr<referenced_type> refPtr2 = refPtr;

    BOOST_CHECK_EQUAL( refPtr2.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( swap, T, ThreadPolicies )
{
    typedef referenced<unsigned int, T> referenced_type;

    referenced_type * ptr1 = new referenced_type;
    referenced_type * ptr2 = new referenced_type;

    ref_ptr<referenced_type> refPtr1( ptr1 );
    ref_ptr<referenced_type> refPtr2( ptr2 );

    refPtr1.swap(refPtr2);

    BOOST_CHECK_EQUAL( refPtr1.get(), ptr2 );
    BOOST_CHECK_EQUAL( refPtr2.get(), ptr1 );
}

BOOST_AUTO_TEST_SUITE_END()

