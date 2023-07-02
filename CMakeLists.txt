cmake_minimum_required(VERSION 3.15)

project(
  boost_unordered
  VERSION 1.0.0
  LANGUAGES CXX
  DESCRIPTION "standalone boost::unordered library")

add_executable(test main.cpp)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
