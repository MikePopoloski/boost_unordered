// Copyright 2017 Peter Dimov.
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_HASH_IS_RANGE_HPP_INCLUDED
#define BOOST_HASH_IS_RANGE_HPP_INCLUDED

#include <boost/container_hash/detail/requires_cxx11.hpp>
#include <boost/config.hpp>
#include <iterator>

namespace boost
{
#if !defined(BOOST_NO_SFINAE_EXPR)

namespace hash_detail
{

template<class T, class It>
    std::integral_constant< bool, !std::is_same<typename std::remove_cv<T>::type, typename std::iterator_traits<It>::value_type>::value >
        is_range_check( It first, It last );

template<class T> decltype( is_range_check<T>( std::declval<T const&>().begin(), std::declval<T const&>().end() ) ) is_range_( int );
template<class T> std::false_type is_range_( ... );

} // namespace hash_detail

namespace container_hash
{

template<class T> struct is_range: decltype( hash_detail::is_range_<T>( 0 ) )
{
};

} // namespace container_hash

#else

namespace hash_detail
{

template<class T, class E = true_type> struct is_range_: false_type
{
};

template<class T> struct is_range_< T, integral_constant< bool,
        is_same<typename T::value_type, typename std::iterator_traits<typename T::const_iterator>::value_type>::value &&
        is_integral<typename T::size_type>::value
    > >: true_type
{
};

} // namespace hash_detail

namespace container_hash
{

template<class T> struct is_range: hash_detail::is_range_<T>
{
};

} // namespace container_hash

#endif // !defined(BOOST_NO_CXX11_DECLTYPE) && !defined(BOOST_NO_SFINAE_EXPR)

} // namespace boost

#endif // #ifndef BOOST_HASH_IS_RANGE_HPP_INCLUDED
