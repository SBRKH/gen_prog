///////////////////////////////////////////////////////////////////////////////
/// \file test/ref_ptr/constructor.cpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



#define BOOST_TEST_MODULE ref_ptr
#include <boost/test/unit_test.hpp>

#include "common.hpp"



BOOST_AUTO_TEST_SUITE( constructor )

BOOST_AUTO_TEST_CASE_TEMPLATE( default_constructor, T, ThreadPolicies )
{
    typedef Referenced<unsigned int, T> referenced_type;

    ref_ptr<referenced_type> refPtr;
    BOOST_CHECK_EQUAL(refPtr.get(), (void*)0);
}

BOOST_AUTO_TEST_CASE_TEMPLATE( pointer_constructor, T, ThreadPolicies )
{
    typedef Referenced<unsigned int, T> referenced_type;

    referenced_type * ptr = new referenced_type;
    BOOST_CHECK_EQUAL( ptr->ref_count(), 0 );


    ref_ptr<referenced_type> refPtr( ptr );
    BOOST_CHECK_EQUAL( refPtr.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 1 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( copy_constructor, T, ThreadPolicies )
{
    typedef Referenced<unsigned int, T> referenced_type;

    referenced_type * ptr = new referenced_type;
    BOOST_CHECK_EQUAL( ptr->ref_count(), 0 );


    ref_ptr<referenced_type> refPtr( ptr );
    BOOST_CHECK_EQUAL( refPtr.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 1 );

    ref_ptr<referenced_type> refPtr2( refPtr );
    BOOST_CHECK_EQUAL( refPtr2.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( other_pointer_constructor, T, ThreadPolicies )
{
    typedef Referenced<unsigned int, T> referenced_type;
    typedef Derived<T> derived_type;


    derived_type * ptr = new derived_type;
    BOOST_CHECK_EQUAL( ptr->ref_count(), 0 );

    ref_ptr<referenced_type> refPtr( ptr );
    BOOST_CHECK_EQUAL( refPtr.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 1 );


    ref_ptr<referenced_type> refPtr2( refPtr );
    BOOST_CHECK_EQUAL( refPtr2.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( other_copy_constructor, T, ThreadPolicies )
{
    typedef Referenced<unsigned int, T> referenced_type;
    typedef Derived<T> derived_type;


    derived_type * ptr = new derived_type;
    BOOST_CHECK_EQUAL( ptr->ref_count(), 0 );

    ref_ptr<derived_type> refPtr( ptr );
    BOOST_CHECK_EQUAL( refPtr.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 1 );


    ref_ptr<referenced_type> refPtr2( refPtr );
    BOOST_CHECK_EQUAL( refPtr2.get(), ptr );
    BOOST_CHECK_EQUAL( ptr->ref_count(), 2 );
}

BOOST_AUTO_TEST_SUITE_END()

