#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/SquareMat.hpp"

using namespace matrix;

TEST_CASE("Construction and access") {
    SquareMat mat(2);
    CHECK_NOTHROW(mat[0][0] = 1.5);
    CHECK(mat[0][0] == doctest::Approx(1.5));
    CHECK(mat[1][1] == doctest::Approx(0.0)); // default initialized

    CHECK_THROWS(mat[-1][0]); 
    CHECK_THROWS(mat[2][0]);  
    CHECK_THROWS(mat[0][-1]); 
    CHECK_THROWS(mat[0][2]);  
}

TEST_CASE("Copy constructor") {
    SquareMat origin(2);
    origin[0][0] = 3.56;

    SquareMat copy = SquareMat(origin);
    CHECK(copy[0][0] == doctest::Approx(3.56));
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

TEST_CASE("Mismatched sizes throws") {
    SquareMat a(2);
    SquareMat b(3);
    CHECK_THROWS(a + b);
    CHECK_THROWS(a * b);

}

TEST_CASE("Subtraction of two matrices") {
    SquareMat a(2), b(2);
    a[0][0] = 5; a[0][1] = 4;
    a[1][0] = 3; a[1][1] = 2;

    b[0][0] = 1; b[0][1] = 1;
    b[1][0] = 1; b[1][1] = 1;

    SquareMat result = a - b;

    CHECK(result[0][0] == doctest::Approx(4));
    CHECK(result[0][1] == doctest::Approx(3));
    CHECK(result[1][0] == doctest::Approx(2));
    CHECK(result[1][1] == doctest::Approx(1));
}

TEST_CASE("Unary minus on a matrix") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = -2;
    a[1][0] = 3; a[1][1] = -4;

    SquareMat mat = -a;

    CHECK(mat[0][0] == doctest::Approx(-1));
    CHECK(mat[0][1] == doctest::Approx(2));
    CHECK(mat[1][0] == doctest::Approx(-3));
    CHECK(mat[1][1] == doctest::Approx(4));
}

TEST_CASE("Matrix multiplication") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 5; b[0][1] = 6;
    b[1][0] = 7; b[1][1] = 8;

    SquareMat result = a * b;

    CHECK(result[0][0] == doctest::Approx(19));  
    CHECK(result[0][1] == doctest::Approx(22));  
    CHECK(result[1][0] == doctest::Approx(43));  
    CHECK(result[1][1] == doctest::Approx(50));  
}

TEST_CASE("Matrix multiplied by scalar (member)") {
    SquareMat mat(2);
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    SquareMat result = mat * 2.0;

    CHECK(result[0][0] == doctest::Approx(2.0));
    CHECK(result[0][1] == doctest::Approx(4.0));
    CHECK(result[1][0] == doctest::Approx(6.0));
    CHECK(result[1][1] == doctest::Approx(8.0));
}

TEST_CASE("Scalar multiplied by matrix (non-member)") {
    SquareMat mat(2);
    mat[0][0] = 1; mat[0][1] = 2;
    mat[1][0] = 3; mat[1][1] = 4;

    SquareMat result = 2.0 * mat;

    CHECK(result[0][0] == doctest::Approx(2.0));
    CHECK(result[0][1] == doctest::Approx(4.0));
    CHECK(result[1][0] == doctest::Approx(6.0));
    CHECK(result[1][1] == doctest::Approx(8.0));
}

TEST_CASE("Multiplication with operator %") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[0][1] = 2;
    a[1][0] = 3; a[1][1] = 4;

    b[0][0] = 2; b[0][1] = 0;
    b[1][0] = 1; b[1][1] = 5;

    SquareMat result = a % b;

    CHECK(result[0][0] == doctest::Approx(2.0));
    CHECK(result[0][1] == doctest::Approx(0.0));
    CHECK(result[1][0] == doctest::Approx(3.0));
    CHECK(result[1][1] == doctest::Approx(20.0));
}

TEST_CASE("Modulo with scalar") {
    SquareMat a(2);
    a[0][0] = 5; a[0][1] = 7;
    a[1][0] = 9; a[1][1] = 11;

    SquareMat result = a % 4;

    CHECK(result[0][0] == doctest::Approx(1.0));
    CHECK(result[0][1] == doctest::Approx(3.0));
    CHECK(result[1][0] == doctest::Approx(1.0));
    CHECK(result[1][1] == doctest::Approx(3.0));
}

TEST_CASE("Scalar division") {
    SquareMat a(2);
    a[0][0] = 4; a[0][1] = 8;
    a[1][0] = 12; a[1][1] = 16;

    SquareMat result = a / 4.0;

    CHECK(result[0][0] == doctest::Approx(1.0));
    CHECK(result[0][1] == doctest::Approx(2.0));
    CHECK(result[1][0] == doctest::Approx(3.0));
    CHECK(result[1][1] == doctest::Approx(4.0));
}

TEST_CASE("Power") {
    SquareMat mat(2);
    mat[0][0] = 1; mat[0][1] = 1;
    mat[1][0] = 1; mat[1][1] = 0;

    // Power 0: 
    SquareMat identity = mat ^ 0;
    CHECK(identity[0][0] == doctest::Approx(1.0));
    CHECK(identity[0][1] == doctest::Approx(0.0));
    CHECK(identity[1][0] == doctest::Approx(0.0));
    CHECK(identity[1][1] == doctest::Approx(1.0));

     // Power 1: mat 
     SquareMat power1 = mat ^ 1;
     CHECK(power1[0][0] == doctest::Approx(1.0));
     CHECK(power1[0][1] == doctest::Approx(1.0));
     CHECK(power1[1][0] == doctest::Approx(1.0));
     CHECK(power1[1][1] == doctest::Approx(0.0));

    // Power 2: mat * mat 
    SquareMat power2 = mat ^ 2;
    CHECK(power2[0][0] == doctest::Approx(2.0));
    CHECK(power2[0][1] == doctest::Approx(1.0));
    CHECK(power2[1][0] == doctest::Approx(1.0));
    CHECK(power2[1][1] == doctest::Approx(1.0));
}



