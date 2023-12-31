
// Copyright 2007-2009 Daniel James.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

// clang-format off
#include "../helpers/prefix.hpp"
#include "../helpers/postfix.hpp"
// clang-format on

#include "../helpers/test.hpp"

namespace insert_stable {
  struct member
  {
    int tag1_;
    int tag2_;

    member() : tag1_(0), tag2_(0) {}
    member(int t1, int t2) : tag1_(t1), tag2_(t2) {}

    friend bool operator==(member const& x, member const& y)
    {
      return x.tag1_ == y.tag1_;
    }

    friend bool operator!=(member const& x, member const& y)
    {
      return x.tag1_ != y.tag1_;
    }
  };
}

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
namespace boost
#else
namespace insert_stable
#endif
{
  std::size_t hash_value(insert_stable::member const& x)
  {
    return static_cast<std::size_t>(x.tag1_);
  }
}

// This is no longer supported, as there's no longer an efficient way to get to
// the end of a group of equivalent nodes.
#if 0

UNORDERED_AUTO_TEST(stable_insert_test1)
{
    boost::unordered_multiset<insert_stable::member> x;

    x.insert(insert_stable::member(1, 1));
    x.insert(insert_stable::member(1, 2));
    x.insert(insert_stable::member(1, 3));

    BOOST_TEST(x.count(insert_stable::member(1, 4)) == 3);

    boost::unordered_multiset<insert_stable::member>::const_iterator
        it = x.begin(),
        end = x.end();
    BOOST_TEST(it != end);
    if (it != end) {
        BOOST_TEST(it->tag2_ == 1);
        ++it;
    }
    BOOST_TEST(it != end);
    if (it != end) {
        BOOST_TEST(it->tag2_ == 2);
        ++it;
    }
    BOOST_TEST(it != end);
    if (it != end) {
        BOOST_TEST(it->tag2_ == 3);
        ++it;
    }
    BOOST_TEST(it == end);
}

UNORDERED_AUTO_TEST(stable_insert_test2)
{
    boost::unordered_multimap<insert_stable::member, int> x;
    typedef boost::unordered_multimap<insert_stable::member,
        int>::const_iterator iterator;

    iterator it = x.emplace(insert_stable::member(1, 1), 1);
    it = x.emplace(insert_stable::member(1, 2), 2);
    it = x.emplace(insert_stable::member(1, 3), 3);

    BOOST_TEST(x.count(insert_stable::member(1, 4)) == 3);

    it = x.begin();
    iterator end = x.end();
    BOOST_TEST(it != end);
    if (it != end) {
        BOOST_TEST(it->first.tag2_ == 1 && it->second == 1);
        ++it;
    }
    BOOST_TEST(it != end);
    if (it != end) {
        BOOST_TEST(it->first.tag2_ == 2 && it->second == 2);
        ++it;
    }
    BOOST_TEST(it != end);
    if (it != end) {
        BOOST_TEST(it->first.tag2_ == 3 && it->second == 3);
        ++it;
    }
    BOOST_TEST(it == end);
}

#endif

RUN_TESTS()
