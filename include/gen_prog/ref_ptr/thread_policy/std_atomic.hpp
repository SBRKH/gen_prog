/*
 * std_atomic_policy.hpp
 *
 *  Created on: 28 sept. 2013
 *      Author: ledocc
 */

#ifndef GEN_PROG__REF_PTR__THREAD_POLICY__STD_ATOMIC_HPP_
#define GEN_PROG__REF_PTR__THREAD_POLICY__STD_ATOMIC_HPP_

#include <atomic>

namespace gen_prog
{

struct std_atomic
{
	template <typename T>
	struct counter { typedef std::atomic<T> type; };

	template <typename T>
	static T increment(std::atomic<T> & t) { return ++t; }

	template <typename T>
	static T decrement(std::atomic<T>  & t) { return --t; }

	template <typename T>
	static T get(const std::atomic<T> & t) { return t; }
};

} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__THREAD_POLICY__STD_ATOMIC_HPP_ ** //
// End of file
