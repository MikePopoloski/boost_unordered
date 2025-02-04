// Copyright (c) 2014 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_CORE_IGNORE_UNUSED_HPP
#define BOOST_CORE_IGNORE_UNUSED_HPP

#include <boost/minconfig.hpp>

namespace boost {



template <typename... Ts>
BOOST_FORCEINLINE constexpr void ignore_unused(Ts&& ...)
{}


template <typename... Ts>
BOOST_FORCEINLINE constexpr void ignore_unused()
{}


} // namespace boost

#endif // BOOST_CORE_IGNORE_UNUSED_HPP
