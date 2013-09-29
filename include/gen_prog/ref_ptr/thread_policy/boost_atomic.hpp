/*
 * boost_atomic_policy.hpp
 *
 *  Created on: 28 sept. 2013
 *      Author: ledocc
 */

#ifndef GEN_PROG__REF_PTR__THREAD_POLICY__BOOST_ATOMIC_HPP_
#define GEN_PROG__REF_PTR__THREAD_POLICY__BOOST_ATOMIC_HPP_


#include <boost/atomic.hpp>


 namespace gen_prog
 {

struct boost_atomic
{
	template <typename T>
	struct counter { typedef boost::atomic<T> type; };

	template <typename T>
	static T increment(boost::atomic<T> & t) { return t.fetch_add(1, boost::memory_order_relaxed)+1; }

	template <typename T>
	static T decrement(boost::atomic<T> & t) { return t.fetch_sub(1, boost::memory_order_relaxed)-1; }

	template <typename T>
	static T get(boost::atomic<T> & t) { return t.load(boost::memory_order_relaxed); }
};

} // namespace gen_prog




#endif // ** GEN_PROG__REF_PTR__THREAD_POLICY__BOOST_ATOMIC_HPP_ ** //
// End of file
