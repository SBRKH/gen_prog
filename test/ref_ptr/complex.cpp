///////////////////////////////////////////////////////////////////////////////
/// \file test/ref_ptr/complex.cpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)



#include <boost/test/unit_test.hpp>

#include "common.hpp"



template <class T>
class Node : public Referenced<unsigned int, T>
{
public:
    ref_ptr<Node> _child;
};



BOOST_AUTO_TEST_SUITE( complex )

BOOST_AUTO_TEST_CASE_TEMPLATE( parent_child_relation, T, ThreadPolicies )
{
    typedef Node<T> node_type;

    ref_ptr< node_type > parent(new node_type);
    parent->_child = new node_type;

    parent = parent->_child;

    BOOST_CHECK_EQUAL(parent->ref_count(), 1);
}


BOOST_AUTO_TEST_SUITE_END()

