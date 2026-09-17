# Copyright 2018, 2019 Peter Dimov
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt

#======================================================================
# 1. Enable experimental 'import std;' support
#======================================================================
# gersemi: off
if(NOT DEFINED CMAKE_EXPERIMENTAL_CXX_IMPORT_STD)
    if(CMAKE_VERSION VERSION_GREATER_EQUAL "4.4.0")
        set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
            "f35a9ac6-8463-4d38-8eec-5d6008153e7d"
        )
    elseif(CMAKE_VERSION VERSION_GREATER_EQUAL "4.3.0")
        set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
            "451f2fe2-a8a2-47c3-bc32-94786d8fc91b"
        )
    elseif(CMAKE_VERSION VERSION_GREATER_EQUAL "3.30.0")
        if(CMAKE_VERSION VERSION_LESS "3.31.8")
            set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
                "0e5b6991-d74f-4b3d-a41c-cf096e0b2508"
            )
        elseif(CMAKE_VERSION VERSION_LESS "4.0.0")
            set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
                "d0edc3af-4c50-42ea-a356-e2862fe7a444"
            )
        elseif(CMAKE_VERSION VERSION_LESS "4.0.3")
            set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
                "a9e1cf81-9932-4810-974b-6eccaf14e457"
            )
        elseif(CMAKE_VERSION VERSION_LESS "4.3.0")
            set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD
                "d0edc3af-4c50-42ea-a356-e2862fe7a444"
            )
        endif()
    endif()
endif()
# gersemi: on

cmake_minimum_required(VERSION 3.21...4.4)

project(cmake_subdir_test LANGUAGES CXX VERSION 1.90.0)

#======================================================================
# Check if import std; is available for the current toolchain
#======================================================================
if(${CMAKE_CXX_STANDARD} IN_LIST CMAKE_CXX_COMPILER_IMPORT_STD)
    set(CMAKE_CXX_MODULE_STD 1)
    message(STATUS "Using `import std;`")
else()
    message(WARNING "`import std;` is not available for C++${CMAKE_CXX_STANDARD}")
    set(CMAKE_CXX_SCAN_FOR_MODULES OFF)
    set(CMAKE_CXX_MODULE_STD OFF)
    set(BOOST_USE_MODULES OFF)
endif()

add_subdirectory(../.. boostorg/charconv)

set(deps
    # Primary dependencies
    assert
    config
    core
    # Secondary dependencies
    throw_exception
    # only for module install test (CK)
    type_traits
    optional
)

foreach(dep IN LISTS deps)
    add_subdirectory(../../../${dep} boostorg/${dep})
endforeach()

include(cmake/boost-install-library.cmake)
boost_install_library(boost_config TARGETS boost_config)
boost_install_library(boost_assert TARGETS boost_assert DEPENDENCIES "boost_config ${PROJECT_VERSION}")
boost_install_library(boost_throw_exception TARGETS boost_throw_exception DEPENDENCIES "boost_assert ${PROJECT_VERSION}")
boost_install_library(boost_core TARGETS boost_core DEPENDENCIES "boost_throw_exception ${PROJECT_VERSION}")
boost_install_library(boost_charconv TARGETS boost_charconv DEPENDENCIES "boost_assert ${PROJECT_VERSION}"
    "boost_core ${PROJECT_VERSION}" "boost_config ${PROJECT_VERSION}" "boost_throw_exception ${PROJECT_VERSION}"
)
# only for module install test (CK)
boost_install_library(boost_type_traits TARGETS boost_type_traits DEPENDENCIES "boost_config ${PROJECT_VERSION}")
boost_install_library(boost_optional TARGETS boost_optional DEPENDENCIES "boost_type_traits ${PROJECT_VERSION}"
    "boost_assert ${PROJECT_VERSION}" "boost_core ${PROJECT_VERSION}" "boost_throw_exception ${PROJECT_VERSION}"
)

add_executable(quick ../quick.cpp)
target_link_libraries(quick PRIVATE Boost::charconv)

enable_testing()
add_test(quick quick)

add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure -C $<CONFIG>)
