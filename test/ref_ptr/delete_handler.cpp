///////////////////////////////////////////////////////////////////////////////
/// \file test/ref_ptr/delete_handler.cpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



#include <boost/test/unit_test.hpp>

#include "common.hpp"



BOOST_AUTO_TEST_SUITE( delete_handler )

BOOST_AUTO_TEST_CASE_TEMPLATE( do_delete, T, DeleteHandlerPolicies )
{
    typedef referenced<unsigned int, single_thread, T> referenced_type;

    referenced_type * ptr = new referenced_type;
    BOOST_CHECK_EQUAL( ptr->ref_count(), 0 );

    ref_ptr<referenced_type> refPtr( ptr );

    {
        ref_ptr<referenced_type> refPtr2( ptr );

        BOOST_CHECK_EQUAL( refPtr.get(), ptr );
        BOOST_CHECK_EQUAL( refPtr2.get(), ptr );
        BOOST_CHECK_EQUAL( ptr->ref_count(), 2 );
    }

    BOOST_CHECK_EQUAL( ptr->ref_count(), 1 );
}

BOOST_AUTO_TEST_SUITE_END()

