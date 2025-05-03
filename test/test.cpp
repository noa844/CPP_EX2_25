#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/SquareMat.hpp"

using namespace matrix;

TEST_CASE("Construction and access") {
    SquareMat m(2);
    CHECK_NOTHROW(m[0][0] = 1.5);
    CHECK(m[0][0] == doctest::Approx(1.5));
    CHECK(m[1][1] == doctest::Approx(0.0)); // default initialized

    CHECK_THROWS(m[-1][0]); // invalid row
    CHECK_THROWS(m[2][0]);  // out of bounds row
    CHECK_THROWS(m[0][-1]); // invalid col
    CHECK_THROWS(m[0][2]);  // out of bounds col
}

TEST_CASE("Copy constructor") {
    SquareMat original(2);
    original[0][0] = 3.14;

    SquareMat copy = original;
    CHECK(copy[0][0] == doctest::Approx(3.14));
    CHECK(copy[1][1] == doctest::Approx(0.0)); // still zero
}

TEST_CASE("Assignment operator") {
    SquareMat a(2), b(2);
    a[1][1] = 7.0;
    b = a;
    CHECK(b[1][1] == doctest::Approx(7.0));
}

TEST_CASE("Addition") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;
    b[0][0] = 10; b[0][1] = 20;
    b[1][0] = 30; b[1][1] = 40;

    SquareMat result = a + b;
    CHECK(result[0][0] == doctest::Approx(11));
    CHECK(result[0][1] == doctest::Approx(22));
    CHECK(result[1][0] == doctest::Approx(33));
    CHECK(result[1][1] == doctest::Approx(44));
}

TEST_CASE("Addition with mismatched sizes throws") {
    SquareMat a(2);
    SquareMat b(3);
    CHECK_THROWS(a + b);
}

