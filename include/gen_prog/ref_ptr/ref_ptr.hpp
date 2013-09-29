///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/ref_ptr.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__REF_PTR_HPP_
#define GEN_PROG__REF_PTR__REF_PTR_HPP_



namespace gen_prog
{

template <class T>
struct ref_ptr_traits
{
	typedef T 				value_type;
	typedef value_type* 	pointer_type;
	typedef value_type& 	reference_type;
};


template <class T>
class ref_ptr
{
public:
	typedef typename ref_ptr_traits<T>::value_type 		value_type;
	typedef typename ref_ptr_traits<T>::pointer_type 	pointer_type;
	typedef typename ref_ptr_traits<T>::reference_type 	reference_type;


	///////////////////////////////////////////////////////////////////////////
	// CTOR / DTOR
	///////////////////////////////////////////////////////////////////////////
	// default constructor
	 ref_ptr(): _ptr(NULL) {}

	// pointer constructor
	ref_ptr(pointer_type ptr): _ptr(ptr) { constructor_ref(); }

	// copy constructor
	ref_ptr(const ref_ptr & rp): _ptr(rp._ptr) { constructor_ref(); }

	// other pointer constructor
	template <class Other>
	ref_ptr(Other * ptr): _ptr(ptr) { constructor_ref(); }

	// other copy constructor
	template <class Other>
	ref_ptr(const ref_ptr<Other> & rp): _ptr(rp.get()) { constructor_ref(); }

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
#if 0
		_ptr    ^= rp._ptr;
		rp._ptr ^=    _ptr;
		_ptr    ^= rp._ptr;
#else

		pointer_type tmp = _ptr;
		_ptr = rp._ptr;
		rp._ptr = tmp;
#endif
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
	bool valid() const { return _ptr != NULL; }

	// @brief indirection operator
	// @return internal pointer
	pointer_type operator -> () { return _ptr; }

	// @return reference on internal pointer
	reference_type operator * () { return *_ptr; }


private:
	void constructor_ref()
	{ if (_ptr) _ptr->ref(); }

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
