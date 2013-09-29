
#include <boost/test/unit_test.hpp>


#include "common.hpp"


BOOST_AUTO_TEST_SUITE( accessor )

BOOST_AUTO_TEST_CASE_TEMPLATE( implicite_conversion, T, ThreadPolicies )
{
	typedef Referenced<unsigned int, T> referenced_type;

	referenced_type * ptr = new referenced_type;
	ref_ptr<referenced_type> refPtr = ptr;

	referenced_type * ptr2 = refPtr;

	BOOST_CHECK_EQUAL( ptr, ptr2 );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( get, T, ThreadPolicies )
{
	typedef Referenced<unsigned int, T> referenced_type;

	referenced_type * ptr = new referenced_type;
	ref_ptr<referenced_type> refPtr = ptr;

	BOOST_CHECK_EQUAL( refPtr.get(), ptr );
}

BOOST_AUTO_TEST_CASE_TEMPLATE( valid, T, ThreadPolicies )
{
	typedef Referenced<unsigned int, T> referenced_type;
	typedef Derived<T> derived_type;

	ref_ptr<referenced_type> refPtr;

	BOOST_CHECK_EQUAL( refPtr.valid(), false );

	refPtr = new derived_type;
	BOOST_CHECK_EQUAL( refPtr.valid(), true );

	refPtr = NULL;
	BOOST_CHECK_EQUAL( refPtr.valid(), false );
}

BOOST_AUTO_TEST_SUITE_END()

