/*
Copyright 2019 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_CORE_NVP_HPP
#define BOOST_CORE_NVP_HPP

#include <boost/minconfig.hpp>

namespace boost {
namespace serialization {

template<class T>
class nvp {
public:
    nvp(const char* n, T& v) noexcept
        : n_(n)
        , v_(std::addressof(v)) { }

    const char* name() const noexcept {
        return n_;
    }

    T& value() const noexcept {
        return *v_;
    }

    const T& const_value() const noexcept {
        return *v_;
    }

private:
    const char* n_;
    T* v_;
};

template<class T>
inline const nvp<T>
make_nvp(const char* n, T& v) noexcept
{
    return nvp<T>(n, v);
}

} /* serialization */

using serialization::nvp;
using serialization::make_nvp;

} /* boost */

#define BOOST_NVP(v) boost::make_nvp(BOOST_STRINGIZE(v), v)

#endif
