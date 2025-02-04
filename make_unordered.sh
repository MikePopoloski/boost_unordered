#wget https://boostorg.jfrog.io/artifactory/main/release/1.85.0/source/boost_1_87_0.tar.gz
#tar -xvf boost_1_87_0.tar.gz
mkdir temp_boost
bcp --boost=../boost_1_87_0 boost/unordered/unordered_flat_map.hpp boost/unordered/unordered_flat_set.hpp boost/unordered/unordered_node_map.hpp boost/unordered/unordered_node_set.hpp boost/unordered/concurrent_flat_map.hpp boost/unordered/concurrent_flat_set.hpp boost/unordered/concurrent_node_map.hpp boost/unordered/concurrent_node_set.hpp temp_boost

cd temp_boost/boost
rm version.hpp
rm predef.h
rm limits.hpp
rm cstdint.hpp
rm config.hpp
rm static_assert.hpp
rm core/addressof.hpp
rm core/allocator_access.hpp
rm core/allocator_traits.hpp
rm core/bit.hpp
rm core/pointer_traits.hpp
rm -rf config
rm -rf describe
rm -rf detail
rm -rf predef

cp ../../include/boost/minconfig.hpp .

coan source -R '-DBOOST_WORKAROUND(a,b)=0' -DBOOST_HAS_PRAGMA_ONCE -UBOOST_NO_CXX11_DEFAULTED_FUNCTIONS -UBOOST_NO_CXX11_RVALUE_REFERENCES -UBOOST_NO_CXX11_VARIADIC_TEMPLATES -UBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION .

find . -name '*.hpp' -exec gsed -i 's/<boost\/config.hpp>/<boost\/minconfig.hpp>/g' {} \;

find . -name '*.hpp' -exec gsed -i '/boost\/core\/allocator_access.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/boost\/core\/allocator_traits.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/boost\/core\/bit.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/boost\/core\/pointer_traits.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/boost\/core\/addressof.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/boost\/config\/workaround.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/boost\/config\/pragma_message.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/boost\/cstdint.hpp/d' {} \;
find . -name '*.hpp' -exec gsed -i '/<boost\/predef/d' {} \;
find . -name '*.hpp' -exec gsed -i '/<boost\/describe/d' {} \;
find . -name '*.hpp' -exec gsed -i '/friend class boost::serialization/d' {} \;

find . -name '*.hpp' -exec gsed -i 's/BOOST_CONSTEXPR/constexpr/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_CXX14_CONSTEXPR/constexpr/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_INLINE_CONSTEXPR/inline constexpr/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_NOEXCEPT_OR_NOTHROW/noexcept/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_NOEXCEPT/noexcept/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_OVERRIDE/override/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_ATTRIBUTE_NO_UNIQUE_ADDRESS/[[no_unique_address]]/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_ATTRIBUTE_NODISCARD/[[nodiscard]]/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/BOOST_NULLPTR/nullptr/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::uint64_t/std::uint64_t/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::uint32_t/std::uint32_t/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::uint_least32_t/std::uint_least32_t/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::to_address/std::to_address/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::pointer_traits/std::pointer_traits/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::core::bit_width/std::bit_width/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::core::countr_zero/std::countr_zero/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::addressof/std::addressof/g' {} \;
find . -name '*.hpp' -exec gsed -i 's/boost::allocator_traits/std::allocator_traits/g' {} \;

find . -name '*.hpp' -exec perl -0777 -pi -e 's/boost::allocator_construct\(([\S\s]*?),([\S\s]*?)\);/std::allocator_traits<std::remove_cvref_t<decltype(\1)>>::construct(\1,\2);/gs' {} \;
find . -name '*.hpp' -exec perl -0777 -pi -e 's/boost::allocator_deallocate\(([\S\s]*?),([\S\s]*?)\);/std::allocator_traits<std::remove_cvref_t<decltype(\1)>>::deallocate(\1,\2);/gs' {} \;
find . -name '*.hpp' -exec perl -pi -e 's|boost::allocator_destroy\(([\S\s]*?),([\S\s]*)\)|std::allocator_traits<std::remove_cvref_t<decltype(\1)>>::destroy(\1, \2)|' {} \;
find . -name '*.hpp' -exec perl -pi -e 's|boost::allocator_allocate\(([\S\s]*?),([\S\s]*)\)|std::allocator_traits<std::remove_cvref_t<decltype(\1)>>::allocate(\1, \2)|' {} \;
find . -name '*.hpp' -exec perl -pi -e 's|boost::allocator_pointer<(.*?)>::type|std::allocator_traits<\1>::pointer|' {} \;
find . -name '*.hpp' -exec perl -pi -e 's|boost::allocator_void_pointer<(.*?)>::type|std::allocator_traits<\1>::void_pointer|' {} \;
find . -name '*.hpp' -exec perl -pi -e 's|boost::allocator_const_pointer<(.*?)>::type|std::allocator_traits<\1>::const_pointer|' {} \;
find . -name '*.hpp' -exec perl -pi -e 's|boost::allocator_is_always_equal<(.*?)>::type|std::allocator_traits<\1>::is_always_equal|' {} \;
find . -name '*.hpp' -exec perl -0777 -pi -e 's/boost::allocator_propagate_on_container_swap<([\S\s]*?)>::type/std::allocator_traits<\1>::propagate_on_container_swap/gs' {} \;
find . -name '*.hpp' -exec perl -0777 -pi -e 's/boost::allocator_propagate_on_container_move_assignment<([\S\s]*?)>::type/std::allocator_traits<\1>::propagate_on_container_move_assignment/gs' {} \;
find . -name '*.hpp' -exec perl -0777 -pi -e 's/boost::allocator_rebind<([\S\s]*?),([\S\s]*?)>::type/std::allocator_traits<\1>::template rebind_alloc<\2>/gs' {} \;
find . -name '*.hpp' -exec perl -0777 -pi -e 's/boost::allocator_select_on_container_copy_construction\(([\S\s]*?\(\))\)/std::allocator_traits<std::remove_cvref_t<decltype(\1)>>::select_on_container_copy_construction(\1)/gs' {} \;
find . -name '*.hpp' -exec perl -0777 -pi -e 's/BOOST_STATIC_CONSTANT\(int,value=version<T>::value\);/static const int value=version<T>::value;/gs' {} \;
