/*
 * Referenced.hpp
 *
 *  Created on: 27 sept. 2013
 *      Author: ledocc
 */

#ifndef GEN_PROG__REF_PTR__REFERENCED_HPP_
#define GEN_PROG__REF_PTR__REFERENCED_HPP_



#include <gen_prog/ref_ptr/thread_policy/single_thread.hpp>



namespace gen_prog
{

class empty_class {};

template <typename 	T				= unsigned int,
		  class 	ThreadPolicy	= single_thread,
		  class 	BaseClass		= empty_class>
class Referenced : public BaseClass
{
public:
	typedef T 													value_type;
	typedef ThreadPolicy 										thread_policy;
	typedef BaseClass 											base_class;

	typedef typename thread_policy::template counter<value_type>::type counter_type;


public:
	Referenced(): _counter(0) {}
	Referenced(const Referenced &): _counter(0) {}


	Referenced & operator = (const Referenced &) { return *this; }


	value_type ref() const { return thread_policy::increment(_counter); }
	value_type unref() const
	{
		value_type newRefCount = thread_policy::decrement(_counter);
		if (newRefCount == 0) delete this;
		return newRefCount;
	}

	value_type ref_count() const { return thread_policy::get(_counter); }


protected:
	virtual ~Referenced() {}


private:
	mutable counter_type _counter;
};


}  // namespace gen_prog


#endif // ** GEN_PROG__REF_PTR__REFERENCED_HPP_ ** //
// End of file
