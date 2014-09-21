///////////////////////////////////////////////////////////////////////////////
/// \file gen_prog/ref_ptr/referenced.hpp
//
//  Copyright 2013 David Callu. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef GEN_PROG__REF_PTR__SERIALIZATION_HPP_
#define GEN_PROG__REF_PTR__SERIALIZATION_HPP_


#include <boost/serialization/nvp.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/tracking.hpp>

#include <gen_prog/ref_ptr/ref_ptr.hpp>


namespace boost
{
namespace serialization
{

template<class Archive, class T>
inline void save(Archive & ar, const gen_prog::ref_ptr<T> & t, const unsigned int)
{
    // The most common cause of trapping here would be serializing
    // something like ref_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    const T * t_ptr = t.get();
    ar << boost::serialization::make_nvp("ptr", t_ptr);
}
template<class Archive, class T>
inline void load(Archive & ar, gen_prog::ref_ptr<T> & t, const unsigned int)
{
    // The most common cause of trapping here would be serializing
    // something like ref_ptr<int>.  This occurs because int
    // is never tracked by default.  Wrap int in a trackable type
    BOOST_STATIC_ASSERT((tracking_level< T >::value != track_never));
    T* t_ptr;
    ar >> boost::serialization::make_nvp("ptr", t_ptr);
    t = t_ptr;
}

template<class Archive, class T>
inline void serialize(
    Archive & ar,
    gen_prog::ref_ptr< T > &t,
    const unsigned int file_version
){
    // correct ref_ptr serialization depends upon object tracking
    // being used.
    BOOST_STATIC_ASSERT(
        boost::serialization::tracking_level< T >::value
        != boost::serialization::track_never
    );
    split_free(ar, t, file_version);
}

} // namespace serialization
} // namespace boost

#endif // ** GEN_PROG__REF_PTR__SERIALIZATION_HPP_ ** //
