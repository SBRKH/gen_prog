///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/policy/checking/assert_check.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__POLICY__CHECKING__ASSERT_CHECK_HPP_
#define GEN_PROG__REF_PTR__POLICY__CHECKING__ASSERT_CHECK_HPP_



#include <boost/assert.hpp>



namespace gen_prog
{

struct assert_check
{
    template <class T>
    class checker
    {
    public:
        static void on_default(const T*)
        {}
 
        static void on_init(const T*)
        {}

        static void on_dereference(const T * val) const
        { BOOST_ASSERT(val != 0); }
    };
};

} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__POLICY__CHECKING__NO_CHECK_HPP_ ** //
// End of file
