
// Copyright 2006-2009 Daniel James.
// Copyright 2022-2023 Christian Mazakas.
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include "../helpers/unordered.hpp"

#include "../helpers/test.hpp"
#include <boost/limits.hpp>
#include "../helpers/random_values.hpp"

#if defined(BOOST_MSVC)
#pragma warning(push)
#pragma warning(disable : 4127) // conditional expression is constant
#endif

namespace load_factor_tests {

  test::seed_t initialize_seed(783656);

  template <class X> void set_load_factor_tests(X*)
  {
    X x;
#ifdef BOOST_UNORDERED_FOA_TESTS
    BOOST_TEST(x.max_load_factor() == boost::unordered::detail::foa::mlf);
    BOOST_TEST(x.load_factor() == 0);

    // A valid implementation could fail these tests, but I think they're
    // reasonable.
    x.max_load_factor(2.0);
    BOOST_TEST(x.max_load_factor() == boost::unordered::detail::foa::mlf);
    x.max_load_factor(0.5);
    BOOST_TEST(x.max_load_factor() == boost::unordered::detail::foa::mlf);
#else
    BOOST_TEST(x.max_load_factor() == 1.0);
    BOOST_TEST(x.load_factor() == 0);

    // A valid implementation could fail these tests, but I think they're
    // reasonable.
    x.max_load_factor(2.0);
    BOOST_TEST(x.max_load_factor() == 2.0);
    x.max_load_factor(0.5);
    BOOST_TEST(x.max_load_factor() == 0.5);
#endif
  }

  template <class X>
  void insert_test(X*, float mlf, test::random_generator generator)
  {
    X x;
    x.max_load_factor(mlf);
    float b = x.max_load_factor();

    test::random_values<X> values(1000, generator);

    for (typename test::random_values<X>::const_iterator it = values.begin(),
                                                         end = values.end();
         it != end; ++it) {
      typename X::size_type old_size = x.size(),
                            old_bucket_count = x.bucket_count();
      x.insert(*it);
      if (static_cast<double>(old_size + 1) <=
          b * static_cast<double>(old_bucket_count))
        BOOST_TEST(x.bucket_count() == old_bucket_count);
    }
  }

  template <class X>
  void load_factor_insert_tests(X* ptr, test::random_generator generator)
  {
    insert_test(ptr, 1.0f, generator);
    insert_test(ptr, 0.1f, generator);
    insert_test(ptr, 100.0f, generator);

    insert_test(ptr, (std::numeric_limits<float>::min)(), generator);

    if (std::numeric_limits<float>::has_infinity)
      insert_test(ptr, std::numeric_limits<float>::infinity(), generator);
  }

  using test::default_generator;
  using test::generate_collisions;
  using test::limited_range;

#ifdef BOOST_UNORDERED_FOA_TESTS
  boost::unordered_flat_set<int>* int_set_ptr;
  boost::unordered_flat_map<int, int>* int_map_ptr;
  boost::unordered_node_set<int>* int_node_set_ptr;
  boost::unordered_node_map<int, int>* int_node_map_ptr;

  // clang-format off
  UNORDERED_TEST(set_load_factor_tests, 
    ((int_set_ptr)(int_map_ptr)(int_node_set_ptr)(int_node_map_ptr)))

  UNORDERED_TEST(load_factor_insert_tests,
    ((int_set_ptr)(int_map_ptr)(int_node_set_ptr)(int_node_map_ptr))(
      (default_generator)(generate_collisions)(limited_range)))
// clang-format on
#else
  boost::unordered_set<int>* int_set_ptr;
  boost::unordered_multiset<int>* int_multiset_ptr;
  boost::unordered_flat_map<int, int>* int_map_ptr;
  boost::unordered_multimap<int, int>* int_multimap_ptr;

  UNORDERED_TEST(set_load_factor_tests,
    ((int_set_ptr)(int_multiset_ptr)(int_map_ptr)(int_multimap_ptr)))

  UNORDERED_TEST(load_factor_insert_tests,
    ((int_set_ptr)(int_multiset_ptr)(int_map_ptr)(int_multimap_ptr))(
      (default_generator)(generate_collisions)(limited_range)))
#endif
}

RUN_TESTS()

#if defined(BOOST_MSVC)
#pragma warning(pop)
#pragma warning(disable : 4127) // conditional expression is constant
#endif
