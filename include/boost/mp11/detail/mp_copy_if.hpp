#ifndef BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED
#define BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED

//  Copyright 2015-2019 Peter Dimov.
//
//  Distributed under the Boost Software License, Version 1.0.
//
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt

#include <boost/mp11/utility.hpp>
#include <boost/mp11/detail/mp_list.hpp>
#include <boost/mp11/detail/mp_append.hpp>
#include <boost/mp11/detail/config.hpp>

namespace boost
{
namespace mp11
{

// mp_copy_if<L, P>
namespace detail
{

template<class L, template<class...> class P> struct mp_copy_if_impl
{
};

template<template<class...> class L, class... T, template<class...> class P> struct mp_copy_if_impl<L<T...>, P>
{
    template<class U> using _f = mp_if<P<U>, mp_list<U>, mp_list<>>;
    using type = mp_append<L<>, _f<T>...>;
};

} // namespace detail

template<class L, template<class...> class P> using mp_copy_if = typename detail::mp_copy_if_impl<L, P>::type;
template<class L, class Q> using mp_copy_if_q = mp_copy_if<L, Q::template fn>;

} // namespace mp11
} // namespace boost

#endif // #ifndef BOOST_MP11_DETAIL_MP_COPY_IF_HPP_INCLUDED
