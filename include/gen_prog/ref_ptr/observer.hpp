///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/observer.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__OBSERVER_HPP_
#define GEN_PROG__REF_PTR__OBSERVER_HPP_



#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/referenced_fwd.hpp>
#include <gen_prog/ref_ptr/policy/delete_handler/no_delete_handler.hpp>



namespace gen_prog
{


/// base class for any observer class.
/// This base class define interface (abstract function) required in observer class template
class observer_base
{
public:
    observer_base() {}

    /// @return true if observed pointer is not valid or NULL, false otherwise
    virtual bool expired() const = 0;

    /// increment reference
    virtual void do_ref() = 0;
    virtual void do_unref() = 0;


protected:
    observer_base(const observer_base & /*other*/) {}
    const observer_base & operator = (const observer_base & /*other*/) { return *this; }
    virtual ~observer_base() {}
};


template <class ReferencedT>
struct observer_definition
{
    typedef ReferencedT                                referenced_type;

    typedef typename referenced_type::counter_type     counter_type;
    typedef typename referenced_type::thread_policy    thread_policy;

    typedef typename thread_policy::template
                     mutex_wrapper<observer_base>      mutex_impl;

    typedef referenced<counter_type,
                       thread_policy,
                       no_delete_handler,
                       mutex_impl>                     base_class;
};


template <class ReferencedT>
class observer : public observer_definition<ReferencedT>::base_class
{
    typedef observer_definition<ReferencedT>                    definition;


public:
    typedef typename definition::counter_type                   counter_type;
    typedef typename definition::referenced_type                referenced_type;
    typedef typename definition::thread_policy                  thread_policy;

    typedef referenced_type*                                    referenced_pointer_type;


public:
    observer(referenced_pointer_type ref):_observed_ptr(ref) {}

    void signal_delete()
    {
        typename thread_policy::lock_guard lock(*this);
        _observed_ptr = GEN_PROG__NULL;
    }

    referenced_pointer_type add_ref_lock()
    {
        // quick exit
        if ( ! _observed_ptr ) return GEN_PROG__NULL;

        // lock observer
        typename thread_policy::lock_guard lock(*this);

        // quit if _observed_ptr is NULL
        if ( ! _observed_ptr ) return GEN_PROG__NULL;

        if (_observed_ptr->ref() == 1)
        {
            // _observed_ptr is currently in its delete function,
            // but signal_delete is not yet call or blocked by lock
            // of this function. so unref and leave to unlock delete process
            _observed_ptr->unref_nodelete();
            return GEN_PROG__NULL;
        }
        return _observed_ptr;
    }

    virtual bool expired() const { return _observed_ptr == GEN_PROG__NULL; }


    virtual void do_ref() { this->ref(); }
    virtual void do_unref() { this->unref(); }


protected:
    observer(const observer &): _observed_ptr(GEN_PROG__NULL) {}
    const observer & operator = (const observer &) { return *this; }
    virtual ~observer() {}


private:
    referenced_pointer_type _observed_ptr;
};


}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__OBSERVER_HPP_ ** //
// End of file
