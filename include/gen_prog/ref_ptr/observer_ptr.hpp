///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/observer_ptr.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__OBSERVER_PTR_HPP_
#define GEN_PROG__REF_PTR__OBSERVER_PTR_HPP_



#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/ref_ptr.hpp>



namespace gen_prog
{

template <class T>
class observer_ptr
{
public:
    typedef typename ref_ptr_traits<T>::value_type 		value_type;
    typedef typename ref_ptr_traits<T>::pointer_type 	pointer_type;
    typedef typename ref_ptr_traits<T>::reference_type 	reference_type;

    typedef typename T::observer_set_type 				observer_set_type;

    typedef ref_ptr<T>		ref_ptr_type;

    ///////////////////////////////////////////////////////////////////////////
    // CTOR / DTOR
    ///////////////////////////////////////////////////////////////////////////
    // default constructor
    observer_ptr(): _observer_set(GEN_PROG__NULL) {}

    // pointer constructor
    observer_ptr(pointer_type ptr): _observer_set(ptr ? ptr->get_or_create_observer_set() : GEN_PROG__NULL) {}

    // ref_ptr constructor
    observer_ptr(const ref_ptr_type & rp): _observer_set(rp ? rp->get_or_create_observer_set() : GEN_PROG__NULL) {}

    // copy constructor
    observer_ptr(const observer_ptr & op): _observer_set(op._observer_set) {}

    // other pointer constructor
    template <class Other>
    observer_ptr(Other * ptr): _observer_set(ptr ? ptr->get_or_create_observer_set() : GEN_PROG__NULL) {}

    // other ref_ptr constructor
    template <class Other>
    observer_ptr(const ref_ptr<Other> & rp): _observer_set(rp ? rp->get_or_create_observer_set() : GEN_PROG__NULL) {}

    // other copy constructor
    template <class Other>
    observer_ptr(const observer_ptr<Other> & op): _observer_set(op ? op->get_or_create_observer_set() : GEN_PROG__NULL) {}

    // destructor
    ~observer_ptr() {}


    ///////////////////////////////////////////////////////////////////////////
    // Manipulator
    ///////////////////////////////////////////////////////////////////////////
    // pointer copy operator
    const observer_ptr & operator = (pointer_type ptr) { assign(ptr); return *this; }

    // copy operator
    const observer_ptr & operator = (const ref_ptr_type & rp) { assign(rp._ptr); return *this; }

    // copy operator
    const observer_ptr & operator = (const observer_ptr & op) { assign(op._observer_set); return *this; }

    // other pointer copy operator
    template <class Other>
    const observer_ptr & operator = (Other * ptr) { assign(ptr); return *this; }

    // other copy operator
    template <class Other>
    const observer_ptr & operator = (const ref_ptr<Other> & rp) { assign(rp.get()); return *this; }

    // other copy operator
    template <class Other>
    const observer_ptr & operator = (const observer_ptr<Other> & rp) { assign(op._observer_set); return *this; }

    // swap
    void swap(observer_ptr & op)
    {
        _observer_set.swap( op._observer_set );
    }


    ///////////////////////////////////////////////////////////////////////////
    // Accessor
    ///////////////////////////////////////////////////////////////////////////
    // lock observed pointer
    // @return true if observed pointer is still valid, false otherwise
    bool lock(ref_ptr_type & rp) const
    {
        if ( ! _observer_set )
        {
            pointer_type ptr = _observer_set->add_ref_lock();
            if ( ptr )
            {
                rp = ptr;
                ptr->unref();
                return true;
            }
        }

        rp = GEN_PROG__NULL;
        return false;

    }


private:
    void assign(pointer_type ptr)
    {
        _observer_set = ptr ? ptr->get_or_create_observer_set() : GEN_PROG__NULL;
    }


private:
    ref_ptr<observer_set_type> _observer_set;
};


} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__OBSERVER_PTR_HPP_ ** //
// End of file
