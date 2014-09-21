///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/ref_ptr.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__REF_PTR_HPP_
#define GEN_PROG__REF_PTR__REF_PTR_HPP_



#include <gen_prog/config.hpp>



namespace gen_prog
{

template <class T>
struct ref_ptr_traits
{
    typedef T               value_type;
    typedef value_type*     pointer_type;
    typedef value_type&     reference_type;
};

template <class T> class observer_ptr;

template <class T>
class ref_ptr
{
    typedef ref_ptr<T> this_type;


public:
    typedef T                                            referenced_type;
    typedef typename ref_ptr_traits<T>::value_type       value_type;
    typedef typename ref_ptr_traits<T>::pointer_type     pointer_type;
    typedef typename ref_ptr_traits<T>::reference_type   reference_type;


    ///////////////////////////////////////////////////////////////////////////
    // CTOR / DTOR
    ///////////////////////////////////////////////////////////////////////////
    // default constructor
    ref_ptr(): _ptr(GEN_PROG__NULL) {}

    // pointer constructor
    ref_ptr(pointer_type ptr): _ptr( constructor_ref(ptr) ) {}

    // copy constructor
    ref_ptr(const ref_ptr & rp): _ptr( constructor_ref(rp._ptr) ) {}

    // other pointer constructor
    template <class Other>
    ref_ptr(Other * ptr): _ptr( constructor_ref(ptr) ) {}

    // other copy constructor
    template <class Other>
    ref_ptr(const ref_ptr<Other> & rp): _ptr( constructor_ref(rp.get()) ) {}


    // other observer constructor
    template <class Other>
    ref_ptr(const observer_ptr<Other> & op): _ptr(GEN_PROG__NULL)
    {
        // try to use boost::is_base_of and static dispatch

        typedef typename referenced_type::observer_type observer_type;

        observer_type * observer = dynamic_cast<observer_type *>(op.get_observer_base());
        if (observer == GEN_PROG__NULL) return;


        typedef typename observer_type::referenced_type local_referenced_type;
        local_referenced_type * localPtr = observer->add_ref_lock();
        if (localPtr == GEN_PROG__NULL) return;


        T * castedLocalPtr = dynamic_cast<T*>(localPtr);
        if (castedLocalPtr) _ptr = constructor_ref(castedLocalPtr);

        localPtr->unref();
    }

    // destructor
    ~ref_ptr() { if (_ptr) _ptr->unref(); }


    ///////////////////////////////////////////////////////////////////////////
    // Manipulator
    ///////////////////////////////////////////////////////////////////////////
    // pointer copy operator
    ref_ptr & operator = (pointer_type ptr) { assign(ptr); return *this; }

    // copy operator
    ref_ptr & operator = (const ref_ptr & rp) { assign(rp._ptr); return *this; }

    // other pointer copy operator
    template <class Other>
    ref_ptr & operator = (Other * ptr) { assign(ptr); return *this; }

    // other copy operator
    template <class Other>
    ref_ptr & operator = (const ref_ptr<Other> & rp) { assign(rp.get()); return *this; }

    // swap
    void swap(ref_ptr & rp)
    {
        std::swap(_ptr, rp._ptr);
    }

    // reset
    void reset()
    {
        this_type().swap(*this);
    }


    ///////////////////////////////////////////////////////////////////////////
    // Accessor
    ///////////////////////////////////////////////////////////////////////////
    // cast operator
    // @return internal pointer
    operator pointer_type() const { return get(); }

    // @return internal pointer
    pointer_type get() const { return _ptr; }

    // @return true if internal pointer is valid, false otherwise
    bool valid() const { return _ptr != GEN_PROG__NULL; }

    // @brief indirection operator
    // @return internal pointer
    pointer_type operator -> () const { return _ptr; }

    // @return reference on internal pointer
    reference_type operator * () const { return *_ptr; }


private:
    pointer_type constructor_ref(pointer_type ptr)
    { if (ptr) ptr->ref(); return ptr;}

    void assign(pointer_type ptr)
    {
        if (_ptr == ptr) return;

        pointer_type previous_ptr = _ptr;

        _ptr = ptr;
        if (_ptr) _ptr->ref();

        if (previous_ptr) previous_ptr->unref();
    }


private:
    pointer_type _ptr;
};


} // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__REF_PTR_HPP_ ** //


// End of file
