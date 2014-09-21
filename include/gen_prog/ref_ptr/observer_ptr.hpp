///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/observer_ptr.hpp
///
///  Copyright 2013 David Callu. Distributed under the Boost
///  Software License, Version 1.0. (See accompanying file
///  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__OBSERVER_PTR_HPP_
#define GEN_PROG__REF_PTR__OBSERVER_PTR_HPP_



#include <gen_prog/config.hpp>
#include <gen_prog/ref_ptr/observer.hpp>
#include <gen_prog/ref_ptr/ref_ptr.hpp>



namespace gen_prog
{

template <class T>
class observer_ptr
{
    typedef observer_ptr<T> this_type;


public:
    typedef typename ref_ptr_traits<T>::value_type        value_type;
    typedef typename ref_ptr_traits<T>::pointer_type      pointer_type;
    typedef typename ref_ptr_traits<T>::reference_type    reference_type;

    typedef observer<T>                                   observer_type;
    typedef ref_ptr<T>                                    ref_ptr_type;

    ///////////////////////////////////////////////////////////////////////////
    /// CTOR / DTOR
    ///////////////////////////////////////////////////////////////////////////
    /// default constructor
    observer_ptr(): _observer(GEN_PROG__NULL) {}

    /// pointer constructor
    observer_ptr(pointer_type ptr): _observer(GEN_PROG__NULL) { assign(ptr); }

    /// ref_ptr constructor
    observer_ptr(const ref_ptr_type & rp): _observer(GEN_PROG__NULL) { assign(rp.get()); }

    /// copy constructor
    observer_ptr(const observer_ptr & op): _observer(GEN_PROG__NULL) { assign(op._observer); }

    /// other pointer constructor
    template <class Other>
    observer_ptr(Other * ptr): _observer(GEN_PROG__NULL) { assign(ptr); }

    /// other ref_ptr constructor
    template <class Other>
    observer_ptr(const ref_ptr<Other> & rp): _observer(GEN_PROG__NULL) { assign(rp.get()); }

    /// other copy constructor
    template <class Other>
    observer_ptr(const observer_ptr<Other> & op): _observer(GEN_PROG__NULL) { assign(op._observer); }

    /// destructor
    ~observer_ptr() { assign( static_cast<observer_base*>(GEN_PROG__NULL) ); }


    ///////////////////////////////////////////////////////////////////////////
    /// Manipulator
    ///////////////////////////////////////////////////////////////////////////
    /// pointer copy operator
    observer_ptr & operator = (pointer_type ptr) { assign(ptr); return *this; }

    /// copy operator
    observer_ptr & operator = (const ref_ptr_type & rp) { assign(rp._ptr); return *this; }

    /// copy operator
    observer_ptr & operator = (const observer_ptr & op) { assign(op._observer); return *this; }

    /// other pointer copy operator
    template <class Other>
    observer_ptr & operator = (Other * ptr) { assign(ptr); return *this; }

    /// other copy operator
    template <class Other>
    observer_ptr & operator = (const ref_ptr<Other> & rp) { assign(rp.get()); return *this; }

    /// other copy operator
    template <class Other>
    observer_ptr & operator = (const observer_ptr<Other> & op) { assign(op._observer); return *this; }

    /// swap
    void swap(observer_ptr & op) { std::swap(_observer, op._observer); }
    /// reset
    void reset() { this_type().swap(*this); }


    ///////////////////////////////////////////////////////////////////////////
    /// Accessor
    ///////////////////////////////////////////////////////////////////////////

    /// lock observed pointer and fill \"rp\" with it
    /// @return true if observed pointer is still valid, false otherwise
    bool lock(ref_ptr_type & rp) const { rp = ref_ptr_type(*this); return rp.valid(); }

    /// @return true if observed pointer is not valid or NULL, false otherwise
    bool expired() const { return _observer ? _observer->expired() : true; }


protected:
    template<class Other>
    friend class observer_ptr;
    template<class Other>
    friend class ref_ptr;

    observer_base * get_observer_base() const { return _observer; }


private:
    void assign(pointer_type ptr)
    {
        assign(static_cast<observer_base*>(ptr ? ptr->get_or_create_observer() : GEN_PROG__NULL));
    }
    void assign(observer_base * observer)
    {
        if (_observer) _observer->do_unref();
        _observer = observer;
        if (_observer) _observer->do_ref();
    }


private:
    observer_base * _observer;
};


} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__OBSERVER_PTR_HPP_ ** //
// End of file
