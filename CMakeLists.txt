cmake_minimum_required(VERSION 3.15)

if(NOT DEFINED BUS_MASTER_PROJECT)
  set(BUS_MASTER_PROJECT OFF)
  if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(BUS_MASTER_PROJECT ON)
    message(STATUS "CMake version: ${CMAKE_VERSION}")
  endif()
endif()

# Protect against in-tree builds.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
  message(
    FATAL_ERROR "In-source builds are not supported. You may need to delete "
                "'CMakeCache.txt' and 'CMakeFiles/' before building again.")
endif()

project(
  boost_unordered
  VERSION 1.0.0
  LANGUAGES CXX
  HOMEPAGE_URL "https://github.com/boostorg/unordered"
  DESCRIPTION "standalone boost::unordered library")

option(BUS_INCLUDE_TESTS "Include tests in the build" ${BUS_MASTER_PROJECT})
option(BUS_SYSTEM_INCLUDE "Mark boost_unordered headers as system includes" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(BUS_SYSTEM_INCLUDE)
  set(BUS_SYSTEM_TAG "SYSTEM")
endif()

add_library(boost_unordered INTERFACE)
target_include_directories(
  boost_unordered
  ${BUS_SYSTEM_TAG} INTERFACE
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
  $<INSTALL_INTERFACE:include>)

if(BUS_INCLUDE_TESTS)
  include(CTest)
  add_subdirectory(test)
endif()
