#include "pch.h"
#include <gtest/gtest.h>
#include <iostream>
#include <assert.h>
#include <sstream>
#include "complex.h"
#include "matrix.h"
#include "polynomial.h"
#include <string>
#include "fraction.h"


namespace Fraction {
class FractionTest : public ::testing::Test {
protected:

};

TEST(Constructor, DefaultConstructor) {
    fraction<int> f;
    EXPECT_EQ(f.getNumerator(), 0);
    EXPECT_EQ(f.getDenominator(), 1);
}

// Тест конструктора с одним аргументом
TEST(Constructor, SingleArgConstructor) {
    fraction<int> f(5);
    EXPECT_EQ(f.getNumerator(), 5);
    EXPECT_EQ(f.getDenominator(), 1);
}

// Тест конструктора с двумя аргументами
TEST(Constructor, TwoArgConstructor) {
    fraction<int> f(2, 4);
    EXPECT_EQ(f.getNumerator(), 1);
    EXPECT_EQ(f.getDenominator(), 2);
}

// Тест оператора сложения
TEST(Operator, AdditionOperator) {
    fraction<int> f1(1, 2);
    fraction<int> f2(1, 3);
    fraction<int> result = f1 + f2;
    EXPECT_EQ(result.getNumerator(), 5);
    EXPECT_EQ(result.getDenominator(), 6);
}

// Тест оператора умножения
TEST(Operator, MultiplicationOperator) {
    fraction<int> f1(2, 3);
    fraction<int> f2(3, 4);
    fraction<int> result = f1 * f2;
    EXPECT_EQ(result.getNumerator(), 1);
    EXPECT_EQ(result.getDenominator(), 2);
}

// Тест оператора деления
TEST(Operator, DivisionOperator) {
    fraction<int> f1(2, 3);
    fraction<int> f2(3, 4);
    fraction<int> result = f1 / f2;
    EXPECT_EQ(result.getNumerator(), 8);
    EXPECT_EQ(result.getDenominator(), 9);
}

// Тест оператора вычитания
TEST(Operator, SubtractionOperator) {
    fraction<int> f1(5, 6);
    fraction<int> f2(1, 6);
    fraction<int> result = f1 - f2;
    EXPECT_EQ(result.getNumerator(), 2);
    EXPECT_EQ(result.getDenominator(), 3);
}

// Тест метода сокращения дроби
TEST(Metode, SimplifyFraction) {
    fraction<int> f(8, 12);
    f.reduce();
    EXPECT_EQ(f.getNumerator(), 2);
    EXPECT_EQ(f.getDenominator(), 3);
}
// Тест метода сравнения двух дробей
TEST(Equality_method, CompareFractions) {
    fraction<int> f1(1, 2);
    fraction<int> f2(2, 4);
    bool result = f1 == f2;
    EXPECT_TRUE(result);
}
}
namespace Polynomial {



    TEST(PolynomialTest, AdditionOperatorTest) {
        polynomial<int> p1; p1.newsize(2);
        p1[0] = 1;
        p1[1] = 2;

        polynomial<int> p2; p2.newsize(2);
        p2[0] = 3;
        p2[1] = 4;

        polynomial<int> sum = p1 + p2;
        EXPECT_EQ(sum[0], 4);
        EXPECT_EQ(sum[1], 6);
    }


    TEST(PolynomialTest, InputOperatorTest) {
        std::stringstream ss("3\n1 2 3\n");
        polynomial<int> p;
        ss >> p;
        EXPECT_EQ(p.deg, 3);
        EXPECT_EQ(p[0], 1);
        EXPECT_EQ(p[1], 2);
        EXPECT_EQ(p[2], 3);
    }

    TEST(OutputOperatorTest, Polynomial_OutputOperatorTest_FULL) {
        polynomial<int> p(3);
        p.newsize(3);
        p.outm_E = output_mode::FULL;
        p[0] = 1;
        p[1] = 2;
        p[2] = 3;

        std::stringstream ss;
        ss << p;

        std::string expectedOutput = "Degree: 3, Coefficients: 1 + 2x + 3x^2";
        EXPECT_EQ(ss.str(), expectedOutput);
    }
    TEST(OutputOperatorTest, Polynomial_OutputOperatorTest_ABBREVIATED) {
        polynomial<int> p(3);
        p.newsize(3);
        p.outm_E = output_mode::ABBREVIATED;
        p[0] = 1;
        p[1] = 2;
        p[2] = 3;

        std::stringstream ss;
        ss << p;

        std::string expectedOutput = "1+2x+3x^2";
        EXPECT_EQ(ss.str(), expectedOutput);
    }
    TEST(OutputOperatorTest,Polynomial_OutputOperatorTest_SHORT) {
        polynomial<int> p(3);
        p.newsize(3);
        p.outm_E = output_mode::SHORT;
        p[0] = 1;
        p[1] = 2;
        p[2] = 3;

        std::stringstream ss;
        ss << p;

        std::string expectedOutput = "1 2x 3x^2";
        EXPECT_EQ(ss.str(), expectedOutput);
    }

    TEST(PolynomialTest, MultiplyTest) {
        polynomial<int> p1;
        p1.newsize(3);
        p1.outm_E = output_mode::FULL;
        p1[0] = 2;
        p1[1] = 3;
        p1[2] = 1;
        
        polynomial<int> p2;
        p2.newsize(3);
        p2[0] = 2;
        p2[1] = 3;
        p2[2] = 1;

        polynomial<int> product; product = p1 * p2;


        std::stringstream ss;
        ss << product;

        std::string expectedOutput = "Degree: 5, Coefficients: 4 + 12x + 13x^2 + 6x^3 + 1x^4";
        EXPECT_EQ(ss.str(), expectedOutput);


    }

    TEST(PolynomialTest, DivideTest) {
        polynomial<double> p1;
        p1.newsize(3);
        p1[0] = 4;
        p1[1] = 8;
        p1[2] = 12;

        polynomial<double> p2; p2.newsize(1);
        p2[0] = 2;

        polynomial<double> quotient = p1 / p2;
        EXPECT_EQ(quotient.deg, 3);
        EXPECT_EQ(quotient[0], 2);
        EXPECT_EQ(quotient[1], 4);
        EXPECT_EQ(quotient[2], 6);
    }

    TEST(PolynomialTest, ModulusTest) {
        polynomial<double> p1;
        p1.newsize(4);
        p1[0] = 5;
        p1[1] = 10;
        p1[2] = 15;
        p1[3] = 20;

        polynomial<double> p2;
        p2.newsize(2);
        p2[0] = 3;
        p2[1] = 6;

        polynomial<double> remainder = p1 % p2;
        EXPECT_EQ(remainder.deg, 1);
        EXPECT_EQ(remainder[0], 1.25);
        
    }

}
namespace Matrix {
    TEST(MatrixTest, ConstructorWithSize)
    {
        matrix<int> m(3, 3);
        EXPECT_EQ(m.getcol(), 3);
        EXPECT_EQ(m.getrow(), 3);
    }

    // Тест для оператора умножения матриц
    TEST(MatrixTest, MatrixMultiplication)
    {
        matrix<int> m1(2, 2);
        m1[0][0] = 1; m1[0][1] = 2;
        m1[1][0] = 3; m1[1][1] = 4;

        matrix<int> m2(2, 2);
        m2[0][0] = 5; m2[0][1] = 6;
        m2[1][0] = 7; m2[1][1] = 8;

        matrix<int> result( m1* m2);

        EXPECT_EQ(result[0][0], 19);
        EXPECT_EQ(result[0][1], 22);
        EXPECT_EQ(result[1][0], 43);
        EXPECT_EQ(result[1][1], 50);
    }

    // Тест для оператора транспонирования матрицы
    TEST(MatrixTest, MatrixTranspose)
    {
        matrix<double> m(2, 3);
        m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
        m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;

        matrix<double> transposed = m.transpose();

        EXPECT_EQ(transposed.getcol(), 3);
        EXPECT_EQ(transposed.getrow(), 2);
        EXPECT_EQ(transposed[0][0], 1);
        EXPECT_EQ(transposed[1][0], 2);
        EXPECT_EQ(transposed[2][0], 3);
        EXPECT_EQ(transposed[0][1], 4);
        EXPECT_EQ(transposed[1][1], 5);
        EXPECT_EQ(transposed[2][1], 6);
    }
}


int main(int argc, char** argv) {
    ::testing::GTEST_FLAG(catch_exceptions) = false;
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}