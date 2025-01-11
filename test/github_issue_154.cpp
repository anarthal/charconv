// Copyright 2024 Matt Borland
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt
//
// See: https://github.com/boostorg/charconv/issues/154

#ifdef BOOST_USE_MODULES
#include <boost/core/lightweight_test_macros.hpp>
#include <boost/charconv/detail/global_module_fragment.hpp>
#include <boost/charconv/detail/config.hpp>
import std;
import boost.core;
import boost.charconv;
#else
#include <boost/charconv.hpp>
#include <boost/core/lightweight_test.hpp>
#endif

int main()
{
    #if BOOST_CHARCONV_LDBL_BITS == 80
    const long double test_value = -35896.53987658756543653653365436L;
    char buffer[256] {};
    auto r = boost::charconv::to_chars(buffer, buffer + sizeof(buffer), test_value, boost::charconv::chars_format::hex);
    BOOST_TEST(r);
    BOOST_TEST_CSTR_EQ(buffer, "-8.c388a355a1f783ap+12");
    #endif

    return boost::report_errors();
}
