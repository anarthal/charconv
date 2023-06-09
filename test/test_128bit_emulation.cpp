// Copyright 2023 Matt Borland
// Distributed under the Boost Software License, Version 1.0.
// https://www.boost.org/LICENSE_1_0.txt

#include <boost/charconv/detail/emulated128.hpp>
#include <boost/core/lightweight_test.hpp>
#include <limits>
#include <iostream>
#include <climits>
#include <cstdint>

using boost::charconv::detail::uint128;

template <typename T>
void test_relational_operators(T val = (std::numeric_limits<T>::max)())
{
    uint128 test_val = UINT64_MAX;
    test_val += 1;

    BOOST_TEST(test_val > val);
    BOOST_TEST(!(test_val < val));
    BOOST_TEST(!(test_val == val));
    BOOST_TEST(test_val != val);

    const uint128 equal_val = val;

    BOOST_TEST(!(equal_val > val));
    BOOST_TEST(equal_val >= val);
    BOOST_TEST(!(equal_val < val));
    BOOST_TEST(equal_val <= val);
    BOOST_TEST(equal_val == val);
    BOOST_TEST(!(equal_val != val));

    int negative_val = -100;

    BOOST_TEST(test_val > negative_val);
    BOOST_TEST(!(test_val < negative_val));
    BOOST_TEST(!(test_val == negative_val));
    BOOST_TEST(test_val != negative_val);
}

void test_arithmetic_operators()
{
    // Only using low word
    const auto fixed_val = UINT64_MAX / 2;
    uint128 test_val = fixed_val;
    BOOST_TEST(test_val / 2 == UINT64_MAX / 4);
    BOOST_TEST(test_val + 1 == fixed_val + 1);
    test_val += 1;
    BOOST_TEST(test_val == fixed_val + 1);
    BOOST_TEST(test_val % fixed_val == 1);
    test_val -= 1;
    BOOST_TEST(test_val == fixed_val);
    BOOST_TEST(test_val % fixed_val == 0);
    BOOST_TEST(test_val / fixed_val == 1);

    // Add the high word
    uint128 test_high_word = UINT64_MAX;
    ++test_high_word;
    BOOST_TEST(test_high_word.high == 1 && test_high_word.low == 0);
    ++test_high_word;
    BOOST_TEST(test_high_word.high == 1 && test_high_word.low == 1);
}

int main()
{
    test_relational_operators<char>();
    test_relational_operators<signed char>();
    test_relational_operators<short>();
    test_relational_operators<int>();
    test_relational_operators<long>();
    test_relational_operators<long long>();
    test_relational_operators<unsigned char>();
    test_relational_operators<unsigned short>();
    test_relational_operators<unsigned>();
    test_relational_operators<unsigned long>();
    test_relational_operators<unsigned long long>();

    test_arithmetic_operators();

    return boost::report_errors();
}
