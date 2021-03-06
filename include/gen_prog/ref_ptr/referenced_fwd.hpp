///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/referenced_fwd.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__REFERENCED_FWD_HPP_
#define GEN_PROG__REF_PTR__REFERENCED_FWD_HPP_


#include <gen_prog/ref_ptr/config.hpp>


namespace gen_prog
{

struct single_thread;

struct no_delete_handler;

struct empty_class {};

struct referenced_default_parameter
{
    typedef GEN_PROG__REF_PTR__DEFAULT_COUNTER_TYPE	        	counter_type;
    typedef GEN_PROG__REF_PTR__DEFAULT_THREAD_POLICY       		thread_policy;
    typedef GEN_PROG__REF_PTR__DEFAULT_DELETE_HANDLER_POLICY   	delete_handle;
    typedef empty_class         								base_class;
};


// forward declaration
template <typename T                   = referenced_default_parameter::counter_type,
          class    ThreadPolicy        = referenced_default_parameter::thread_policy,
          class    DeleteHandlerPolicy = referenced_default_parameter::delete_handle,
          class    BaseClassT          = referenced_default_parameter::base_class>
class referenced;

}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__REFERENCED_HPP_ ** //
// End of file
