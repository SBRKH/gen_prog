///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/observer.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__OBSERVER_HPP_
#define GEN_PROG__REF_PTR__OBSERVER_HPP_



#include <gen_prog/config.hpp>



namespace gen_prog
{

template <typename     T,
          class     ThreadPolicy,
          class     BaseClass>
class Referenced;


class observer_base
{
public:
    observer_base() {}

    virtual bool expired() const = 0;

    virtual void do_ref() = 0;
    virtual void do_unref() = 0;

protected:
    observer_base(const observer_base & other) {}
    const observer_base & operator = (const observer_base & other) { return *this; }
    virtual ~observer_base() {}
};



template <class ReferenceT>
class observer : public Referenced<typename ReferenceT::counter_type,
                                   typename ReferenceT::thread_policy,
                                   typename ReferenceT::thread_policy::template mutex_wrapper<observer_base> >
{
public:
    typedef typename ReferenceT::counter_type                   counter_type;
    typedef ReferenceT                                          referenced_type;
    typedef referenced_type*                                    referenced_pointer_type;
    typedef typename ReferenceT::thread_policy                  thread_policy;


public:
    observer(referenced_type * ref):_observed_ptr(ref) {}

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
            // of this function. nothing to do, just leave
            _observed_ptr->unref_nodelete();
            return GEN_PROG__NULL;
        }
        return _observed_ptr;
    }

    virtual bool expired() const { return _observed_ptr == GEN_PROG__NULL; }


    virtual void do_ref() { this->ref(); }
    virtual void do_unref() { this->unref(); }


protected:
    observer(const observer & other): _observed_ptr(GEN_PROG__NULL) {}
    const observer & operator = (const observer & other) { return *this; }
    ~observer() {}


private:
    referenced_pointer_type _observed_ptr;
};


}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__OBSERVER_HPP_ ** //
// End of file
