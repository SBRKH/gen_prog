///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/policy/delete_handler/local_delete_handler.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__POLICY__DELETE_HANDLER__LOCAL_DELETE_HANDLER_HPP_
#define GEN_PROG__REF_PTR__POLICY__DELETE_HANDLER__LOCAL_DELETE_HANDLER_HPP_



#include <boost/checked_delete.hpp>

#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/empty_class.hpp>
#include <gen_prog/ref_ptr/referenced_fwd.hpp>
#include <gen_prog/ref_ptr/referenced_definition.hpp>



namespace gen_prog
{

struct local_delete_handler
{
    // base class that provide delete fonctionality
    template <class ReferencedT, typename T, class ThreadPolicy>
    class deleter : public referenced<T, ThreadPolicy>
    {
        typedef ReferencedT referenced_type;
        virtual void do_delete(referenced_type * ref) const
        {
            boost::checked_delete(ref);
        }
    };


    // wrapper that containe the deleter
    template <class ReferencedT, class ThreadPolicy, class BaseClassT>
    class wrapper : public BaseClassT
    {
        typedef ReferencedT         referenced_type;
        typedef ThreadPolicy        thread_policy;
        typedef BaseClassT          base_class;

        typedef deleter<ReferencedT> deleter_type;
        typedef ref_ptr<deleter_type> deleter_ref_ptr;


    public:
        // Constructor
        wrapper(): base_class(), _deleter(new deleter_type)
        {}
        wrapper(const wrapper & other): base_class(other), _deleter(new deleter_type)
        {}
    protected:
        // Destructor
        virtual ~wrapper()


    public:
        // Operator
        wrapper & operator = (const wrapper & other): base_class(other),
        {
            base_class::operator=(other);
            return *this;
        }


        // Manipulator
        bool set_deleter( deleter_type * dh )
        {
            if (dh)
            {
                _deleter = dh;
                return true;
            }
            else
            {
                return false;
            }
        }


        // Accessor
        deleter_type * get_deleter()
        {
            return _deleter;
        }


    protected:
        void do_delete(referenced_type * ref) const
        { _deleter->do_delete(); }


    private:

        deleter_ref_ptr _deleter;
    };
};

} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__POLICY__DELETE_HANDLER__LOCAL_DELETE_HANDLER_HPP_ ** //
// End of file
