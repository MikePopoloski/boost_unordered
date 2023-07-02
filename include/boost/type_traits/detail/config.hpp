
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef BOOST_TT_CONFIG_HPP_INCLUDED
#define BOOST_TT_CONFIG_HPP_INCLUDED

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif
#include <boost/version.hpp>

//
// whenever we have a conversion function with ellipses
// it needs to be declared __cdecl to suppress compiler
// warnings from MS and Borland compilers (this *must*
// appear before we include is_same.hpp below):
#if defined(BOOST_MSVC) || (defined(BOOST_BORLANDC) && !defined(BOOST_DISABLE_WIN32))
#   define BOOST_TT_DECL __cdecl
#else
#   define BOOST_TT_DECL /**/
#endif

# if defined(__ghs)     && defined(BOOST_NO_IS_ABSTRACT)

#   define BOOST_TT_NO_CONFORMING_IS_CLASS_IMPLEMENTATION 1

#endif

#ifndef BOOST_TT_NO_CONFORMING_IS_CLASS_IMPLEMENTATION
# define BOOST_TT_HAS_CONFORMING_IS_CLASS_IMPLEMENTATION 1
#endif

//
// define BOOST_TT_TEST_MS_FUNC_SIGS
// when we want to test __stdcall etc function types with is_function etc
// (Note, does not work with Borland, even though it does support __stdcall etc):
//
#if defined(_MSC_EXTENSIONS) && !defined(BOOST_BORLANDC)
#  define BOOST_TT_TEST_MS_FUNC_SIGS
#endif

//
// define BOOST_TT_NO_CV_FUNC_TEST
// if tests for cv-qualified member functions don't 
// work in is_member_function_pointer
//

//
// Macros that have been deprecated, defined here for backwards compatibility:
//
#define BOOST_BROKEN_COMPILER_TYPE_TRAITS_SPECIALIZATION(x)
#define BOOST_TT_BROKEN_COMPILER_SPEC(x)

//
// Can we implement "accurate" binary operator detection:
//
#if !defined(BOOST_NO_SFINAE_EXPR) && !defined(BOOST_NO_CXX11_DECLTYPE)
#  define BOOST_TT_HAS_ACCURATE_BINARY_OPERATOR_DETECTION
#endif

#if defined(__clang__) && (__clang_major__ == 3) && (__clang_minor__ < 2) && defined(BOOST_TT_HAS_ACCURATE_BINARY_OPERATOR_DETECTION)
#undef BOOST_TT_HAS_ACCURATE_BINARY_OPERATOR_DETECTION
#endif

//
// Can we implement accurate is_function/is_member_function_pointer (post C++03)?
//
#if !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
#  define BOOST_TT_HAS_ACCURATE_IS_FUNCTION
#endif

#if defined(_MSVC_LANG) && (_MSVC_LANG >= 201703) 
#  define BOOST_TT_NO_DEDUCED_NOEXCEPT_PARAM
#endif
#if defined(__APPLE_CC__) && defined(__clang_major__) && (__clang_major__ == 9) && (__clang_minor__ == 0)
#  define BOOST_TT_NO_DEDUCED_NOEXCEPT_PARAM
#  define BOOST_TT_NO_NOEXCEPT_SEPARATE_TYPE
#endif
//
// If we have the SD6 macros (check for C++11's __cpp_rvalue_references), and we don't have __cpp_noexcept_function_type
// set, then don't treat noexcept functions as seperate types.  This is a fix for msvc with the /Zc:noexceptTypes- flag set.
//
#if defined(__cpp_rvalue_references) && !defined(__cpp_noexcept_function_type) && !defined(BOOST_TT_NO_NOEXCEPT_SEPARATE_TYPE)
#  define BOOST_TT_NO_NOEXCEPT_SEPARATE_TYPE
#endif
//
// Check MSVC specific macro on older msvc compilers that don't support the SD6 macros, we don't rely on this
// if the SD6 macros *are* available as it appears to be undocumented.
//
#if defined(BOOST_MSVC) && !defined(__cpp_rvalue_references) && !defined(BOOST_TT_NO_NOEXCEPT_SEPARATE_TYPE) && !defined(_NOEXCEPT_TYPES_SUPPORTED)
#  define BOOST_TT_NO_NOEXCEPT_SEPARATE_TYPE
#endif
#if defined(__cpp_rvalue_references) && defined(__NVCC__) && defined(__CUDACC__) && !defined(BOOST_TT_NO_NOEXCEPT_SEPARATE_TYPE)
#  define BOOST_TT_NO_NOEXCEPT_SEPARATE_TYPE
#endif

#endif // BOOST_TT_CONFIG_HPP_INCLUDED


