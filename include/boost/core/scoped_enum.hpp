//  scoped_enum.hpp  ---------------------------------------------------------//

//  Copyright Beman Dawes, 2009
//  Copyright (C) 2011-2012 Vicente J. Botet Escriba
//  Copyright (C) 2012 Anthony Williams

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CORE_SCOPED_ENUM_HPP
#define BOOST_CORE_SCOPED_ENUM_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost
{


  template <typename EnumType>
  struct native_type
  {
    typedef EnumType type;
  };

  template <typename UnderlyingType, typename EnumType>
  inline
  BOOST_CONSTEXPR UnderlyingType underlying_cast(EnumType v) BOOST_NOEXCEPT
  {
    return static_cast<UnderlyingType>(v);
  }

  template <typename EnumType>
  inline
  BOOST_CONSTEXPR EnumType native_value(EnumType e) BOOST_NOEXCEPT
  {
    return e;
  }

}



#define BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(EnumType,UnderlyingType) enum class EnumType : UnderlyingType
#define BOOST_SCOPED_ENUM_DECLARE_BEGIN(EnumType) enum class EnumType
#define BOOST_SCOPED_ENUM_DECLARE_END2()
#define BOOST_SCOPED_ENUM_DECLARE_END(EnumType) ;

#define BOOST_SCOPED_ENUM_NATIVE(EnumType) EnumType
#define BOOST_SCOPED_ENUM_FORWARD_DECLARE(EnumType) enum class EnumType


// Deprecated macros
#define BOOST_SCOPED_ENUM_START(name) BOOST_SCOPED_ENUM_DECLARE_BEGIN(name)
#define BOOST_SCOPED_ENUM_END BOOST_SCOPED_ENUM_DECLARE_END2()
#define BOOST_SCOPED_ENUM(name) BOOST_SCOPED_ENUM_NATIVE(name)

#endif  // BOOST_CORE_SCOPED_ENUM_HPP
