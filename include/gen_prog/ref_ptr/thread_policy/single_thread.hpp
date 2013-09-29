///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/thread_policy/ref_ptr/single_thread.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

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
