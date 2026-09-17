# Copyright 2018, 2019 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

cmake_minimum_required(VERSION 3.21...4.3)

project(cmake_install_test LANGUAGES CXX)

find_package(boost_charconv 1.90.0 EXACT REQUIRED)

add_executable(quick ../quick.cpp)
target_link_libraries(quick PRIVATE Boost::charconv)

if(BOOST_USE_MODULES)
    # Enable and propagate C++23, import std, and the modules macro
    target_compile_features(quick PUBLIC cxx_std_23)
    set_target_properties(quick PROPERTIES CXX_MODULE_STD 1)
endif()

enable_testing()
add_test(quick quick)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>)
