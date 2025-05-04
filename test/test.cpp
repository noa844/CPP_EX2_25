// noa.honigstein@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../src/SquareMat.hpp"
#include <sstream>
using namespace std;
using namespace matrix;

TEST_CASE("Construction and access") {
    SquareMat mat(2);
    CHECK_NOTHROW(mat[0][0] = 1.5);
    CHECK(mat[0][0] == doctest::Approx(1.5));
    CHECK(mat[1][1] == doctest::Approx(0.0)); // default initialized
//Throws on out-of-bound access
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

TEST_CASE("Scalar division operator") {
    SquareMat a(2);
    a[0][0] = 4; a[0][1] = 8;
    a[1][0] = 12; a[1][1] = 16;

    SquareMat result = a / 4.0;

    CHECK(result[0][0] == doctest::Approx(1.0));
    CHECK(result[0][1] == doctest::Approx(2.0));
    CHECK(result[1][0] == doctest::Approx(3.0));
    CHECK(result[1][1] == doctest::Approx(4.0));
}

TEST_CASE("Power operator") {
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
TEST_CASE("Prefix increment ++mat") {
    SquareMat mat(2);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;

    SquareMat& result = ++mat;

    CHECK(result[0][0] == doctest::Approx(2.0));
    CHECK(result[0][1] == doctest::Approx(3.0));
    CHECK(result[1][0] == doctest::Approx(4.0));
    CHECK(result[1][1] == doctest::Approx(5.0));
}

TEST_CASE("Postfix increment mat++") {
    SquareMat mat(2);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;

    SquareMat before = mat++;
    CHECK(before[0][0] == doctest::Approx(1.0));
    CHECK(before[0][1] == doctest::Approx(2.0));
    CHECK(before[1][0] == doctest::Approx(3.0));
    CHECK(before[1][1] == doctest::Approx(4.0));

    //after
    CHECK(mat[0][0] == doctest::Approx(2.0));
    CHECK(mat[0][1] == doctest::Approx(3.0));
    CHECK(mat[1][0] == doctest::Approx(4.0));
    CHECK(mat[1][1] == doctest::Approx(5.0));
}

TEST_CASE("Prefix increment --mat") {
    SquareMat mat(2);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;

    SquareMat& result = --mat;

    CHECK(result[0][0] == doctest::Approx(0.0));
    CHECK(result[0][1] == doctest::Approx(1.0));
    CHECK(result[1][0] == doctest::Approx(2.0));
    CHECK(result[1][1] == doctest::Approx(3.0));
}

TEST_CASE("Postfix increment mat--") {
    SquareMat mat(2);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;

    SquareMat before = mat--;
    CHECK(before[0][0] == doctest::Approx(1.0));
    CHECK(before[0][1] == doctest::Approx(2.0));
    CHECK(before[1][0] == doctest::Approx(3.0));
    CHECK(before[1][1] == doctest::Approx(4.0));

    //after
    CHECK(mat[0][0] == doctest::Approx(0.0));
    CHECK(mat[0][1] == doctest::Approx(1.0));
    CHECK(mat[1][0] == doctest::Approx(2.0));
    CHECK(mat[1][1] == doctest::Approx(3.0));
}

TEST_CASE("Transpose operator") {
    SquareMat mat(2);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;

    SquareMat t = ~mat;

    CHECK(t[0][0] == doctest::Approx(1.0));
    CHECK(t[0][1] == doctest::Approx(3.0));
    CHECK(t[1][0] == doctest::Approx(2.0));
    CHECK(t[1][1] == doctest::Approx(4.0));
}

TEST_CASE("Sum of matrix elements with sumMat()") {
    SquareMat mat(2);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;

    CHECK(mat.sumMat() == doctest::Approx(10.0));
}

TEST_CASE("Equality and inequality oparator") {
    SquareMat a(2), b(2), c(2);
    a[0][0] = 1; a[0][1] = 2; 
    a[1][0] = 3; a[1][1] = 4.1;  // a = 10.1

    b[0][0] = 2; b[0][1] = 2; 
    b[1][0] = 3; b[1][1] = 3.1;  // b = 10.1

    c[0][0] = 0; c[0][1] = 0; 
    c[1][0] = 0; c[1][1] = 0;  // c = 0

    CHECK(a.sumMat() == doctest::Approx(b.sumMat()));
    CHECK_FALSE(a == c);
    CHECK(a != c);
    CHECK_FALSE(a != b);
}

TEST_CASE("Comparison operators") {
    SquareMat a(2), b(2), c(2);
    a[0][0] = 1; a[0][1] = 2; 
    a[1][0] = 3; a[1][1] = 4;  // a  = 10

    b[0][0] = 5; b[0][1] = 5;
    b[1][0] = 5; b[1][1] = 5;  // b  = 20

    c[0][0] = 0; c[0][1] = 0; 
    c[1][0] = 0; c[1][1] = 10;  // c  = 10

    CHECK(a < b);
    CHECK(b > a);
    CHECK(a <= c);
    CHECK_FALSE(b <= a);
    CHECK_FALSE(b <= c);
    CHECK(b >= a);
    CHECK(b >= c);
    CHECK_FALSE(a >= b);
}


TEST_CASE("Matrix output with operator<<") {
    SquareMat mat(2);
    mat[0][0] = 1.0; mat[0][1] = 2.0;
    mat[1][0] = 3.0; mat[1][1] = 4.0;

    std::stringstream ss;
    ss << mat;

    std::string expected = "|1|2|\n|3|4|\n";
    CHECK(ss.str() == expected);
}

TEST_CASE("Determinant of matrix ") {
    SquareMat mat(2);
    mat[0][0] = 4.0; mat[0][1] = 6.0;
    mat[1][0] = 3.0; mat[1][1] = 8.0;
    CHECK((!mat) == doctest::Approx(14.0));
}

TEST_CASE("Operator += and -=") {
    SquareMat a(2), b(2);
    a[0][0] = 1; a[0][1] = 0; 
    a[1][0] = 0; a[1][1] = 4;

    b[0][0] = 1; b[0][1] = 0; 
    b[1][0] = 0; b[1][1] = 1;

    a += b;
    CHECK(a[0][0] == doctest::Approx(2));
    CHECK(a[1][1] == doctest::Approx(5));

    a -= b;
    CHECK(a[0][0] == doctest::Approx(1));
    CHECK(a[1][1] == doctest::Approx(4));
}

TEST_CASE("Operator *= with scalar and matrix") {
    SquareMat a(2);
    a[0][0] = 1; a[0][1] = 2; 
    a[1][0] = 3; a[1][1] = 4;

    a *= 2;
    CHECK(a[0][0] == doctest::Approx(2));
    CHECK(a[1][1] == doctest::Approx(8));

    SquareMat b(2);
    b[0][0] = 1; b[0][1] = 0; 
    b[1][0] = 0; b[1][1] = 1;

    a *= b;
    CHECK(a[0][0] == doctest::Approx(2));
    CHECK(a[1][1] == doctest::Approx(8));
}

TEST_CASE("Operator /= with scalar") {
    SquareMat a(2);
    a[0][0] = 4; a[0][1] = 6; 
    a[1][0] = 8; a[1][1] = 10;

    a /= 2;
    CHECK(a[0][0] == doctest::Approx(2));
    CHECK(a[1][1] == doctest::Approx(5));
}

TEST_CASE("Operator %= with scalar and matrix") {
    SquareMat a(2);
    a[0][0] = 5; a[0][1] = 8; 
    a[1][0] = 10; a[1][1] = 13;

    a %= 3;
    CHECK(a[0][0] == doctest::Approx(fmod(5,3)));
    CHECK(a[1][1] == doctest::Approx(fmod(13,3)));

    SquareMat b(2);
    b[0][0] = 1; b[0][1] = 2; 
    b[1][0] = 0.5; b[1][1] = 2;

    a %= b;
    CHECK(a[0][0] == doctest::Approx(fmod(5,3) * 1));
    CHECK(a[1][1] == doctest::Approx(fmod(13,3) * 2));
}

TEST_CASE("Mismatched sizes throws") {
    SquareMat a(2);
    SquareMat b(3);
    CHECK_THROWS(a + b);
    CHECK_THROWS(a - b);
    CHECK_THROWS(a * b);
    CHECK_THROWS(a %= b);
    CHECK_THROWS(a += b);
    CHECK_THROWS(a -= b);
    CHECK_THROWS(a *= b);
}

TEST_CASE("Throws on division/modulo by zero") {
    SquareMat a(2);
    CHECK_THROWS(a / 0.0);
    CHECK_THROWS(a %= 0);
    CHECK_THROWS(a /= 0.0);
}

TEST_CASE("Throws on negative power") {
    SquareMat a(2);
    CHECK_THROWS(a ^ -1);
}





