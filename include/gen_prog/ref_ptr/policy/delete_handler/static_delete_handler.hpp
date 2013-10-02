///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/delete_handler_policy/static_delete_handler.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__DELETE_HANDLER_POLICY__STATIC_DELETE_HANDLER_HPP_
#define GEN_PROG__REF_PTR__DELETE_HANDLER_POLICY__STATIC_DELETE_HANDLER_HPP_



#include <boost/checked_delete.hpp>

#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/empty_class.hpp>
#include <gen_prog/ref_ptr/referenced_fwd.hpp>



namespace gen_prog
{

struct static_delete_handler
{
    // base class that provide delete fonctionality
    template <class ReferencedT, typename T, class ThreadPolicy>
    class deleter : public referenced<T, ThreadPolicy>
    {
        typedef ReferencedT referenced_type;

        virtual void do_delete(referenced_type * ref)
        {
            boost::checked_delete(ref);
        }
    };


    // wrapper that containe the deleter
    template <class ReferencedT, class ThreadPolicy, class BaseClassT>
    class type : public BaseClassT
    {
        typedef ReferencedT referenced_type;

        typedef deleter<referenced_type>    deleter_type;
        typedef ref_ptr<deleter_type> d     eleter_ref_ptr;


    public:        
        // Constructor
        wrapper(): base_class()
        {}
        wrapper(const wrapper & other): base_class(other)
        {}
    protected:
        // Constructor
        virtual ~wrapper()
           

    public:
        // Operator
        wrapper & operator = (const wrapper & other): base_class(other), 
        {
            base_class::operator=(other);
            return *this;
        }
    

        // Manipulator
        static bool set_deleter( deleter_type * dh )
        {
            if (dh)
            {
                get_static_ref_ptr() = dh;
                return true;
            }
            else 
            {
                return false;
            }
        }


        // Accessor
        static deleter_type * get_deleter()
        {
            return get_static_ref_ptr();
        }


    protected:
        static void do_delete(referenced_type * ref) const
        { get_static_ref_ptr()->do_delete(ref); }


    private:
        static deleter_ref_ptr & get_static_ref_ptr()
        (
            static deleter_ref_ptr s_deleter( new deleter_type );
            return s_deleter;
        }
    };
};

} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__THREAD_POLICY__SINGLE_THREAD_HPP_ ** //
// End of file
