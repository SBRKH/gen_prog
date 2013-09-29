
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

