/*
 * single_thread_policy.hpp
 *
 *  Created on: 28 sept. 2013
 *      Author: ledocc
 */

#ifndef GEN_PROG__REF_PTR__THREAD_POLICY__SINGLE_THREAD_HPP_
#define GEN_PROG__REF_PTR__THREAD_POLICY__SINGLE_THREAD_HPP_



namespace gen_prog
{

struct single_thread
{
	template <typename T>
	struct counter { typedef T type; };

	template <typename T>
	static T increment(T & t) { return ++t; }

	template <typename T>
	static T decrement(T & t) { return --t; }

	template <typename T>
	static T get(T & t) { return t; }
};

} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__THREAD_POLICY__SINGLE_THREAD_HPP_ ** //
// End of file
