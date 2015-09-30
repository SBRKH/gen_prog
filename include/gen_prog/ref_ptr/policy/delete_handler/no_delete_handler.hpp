///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/policy/delete_handler/no_delete_handler.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__POLICY__DELETE_HANDLER__NO_DELETE_HANDLER_HPP_
#define GEN_PROG__REF_PTR__POLICY__DELETE_HANDLER__NO_DELETE_HANDLER_HPP_



#include <boost/checked_delete.hpp>

#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/ref_ptr.hpp>
#include <gen_prog/ref_ptr/referenced_fwd.hpp>



namespace gen_prog
{

struct no_delete_handler
{
    // base class that provide delete fonctionality
    // for consistance with other delete handler policy
    //template <class ReferencedT, typename T, class ThreadPolicy>



    // wrapper that containe the deleter
    template <class ReferencedT, typename T, class ThreadPolicy, class BaseClassT>
    class wrapper : public BaseClassT
    {
        typedef ReferencedT         referenced_type;
        typedef ThreadPolicy        thread_policy;
        typedef BaseClassT          base_class;


    public:
        struct delete_handler : public referenced<T, ThreadPolicy, no_delete_handler, empty_class>
        {
            public:
                static void do_delete(const wrapper * x)
                {
                    // from boost/checked_delete.hpp
                    // can't define boost::checked_delete as friend in wrapper with VC 2003 .NET
                    // so just copy code for now (hate Microsoft)
                    typedef char type_must_be_complete[ sizeof(wrapper)? 1: -1 ];
                    (void) sizeof(type_must_be_complete);
                    delete x;
                }
        };

        typedef ref_ptr<delete_handler> delete_handler_ref_ptr;


    public:
        // Constructor
        wrapper(): base_class()
        {}
        wrapper(const wrapper & other): base_class(other)
        {}
    protected:
        friend struct delete_handler;
        // Destructor
        virtual ~wrapper() {}


    public:
        // Operator
        wrapper & operator = (const wrapper & other)
        {
            base_class::operator=(other);
            return *this;
        }


    public:
        // Manipulator
        // for consistance with other delete handler policy
        bool set_delete_handler( delete_handler * )
        { return false; }

        // Accessor
        // for consistance with other delete handler policy
        delete_handler * get_delete_handler()
        { return GEN_PROG__NULL; }


    protected:
        void do_delete(const referenced_type * ref) const
        { delete_handler::do_delete( static_cast<const wrapper*>(ref) ); }
    };
};

} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__POLICY__DELETE_HANDLER__NO_DELETE_HANDLER_HPP_ ** //
// End of file
