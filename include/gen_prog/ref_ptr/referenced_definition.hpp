///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/referenced.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__REFERENCED_DEFINITION_HPP_
#define GEN_PROG__REF_PTR__REFERENCED_DEFINITION_HPP_



#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/referenced_fwd.hpp>



namespace gen_prog
{

// referenced definition
template <typename T                    = referenced_default_parameter::counter_type,
          class    ThreadPolicy         = referenced_default_parameter::thread_policy,
          class    DeleteHandlerPolicy  = referenced_default_parameter::delete_handle,
          class    BaseClassT           = referenced_default_parameter::base_class>
struct referenced_definition
{
    // template parameters
    typedef T                                                   counter_type;
    typedef ThreadPolicy                                        thread_policy;
    typedef DeleteHandlerPolicy                                 delete_handler_policy;
    typedef BaseClassT                                          base_class_template_parameter;


    // referenced type
    typedef referenced<counter_type, 
                       thread_policy, 
                       delete_handler_policy, 
                       base_class_template_parameter>           referenced_type;
    // observer type
    typedef observer<referenced_type>                           observer_type;


    // thread policy type deduction
    typedef typename thread_policy::template 
                     thread_safe_type<counter_type>::type       counter_impl;
    typedef typename thread_policy::template 
                     thread_safe_type<observer_type*>::type     observer_impl;


    // delete handler policy type deduction
    typedef typename delete_handler_policy::template 
                     wrapper<referenced_type,
                             counter_type,
                             thread_policy,
                             base_class_template_parameter>     delete_handler_wrapper;
    
    typedef typename delete_handler_wrapper::delete_handler     delete_handler;


    // base class of referenced class
    typedef delete_handler_wrapper                              base_class;
};


}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__REFERENCED_HPP_ ** //
// End of file
