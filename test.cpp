
#include "gtest/gtest.h"
#include "matrix_oop.h"

// --------------------------------------------------Constructors-------------------------------------------------------------------
// Basic Constructor:
TEST(ConstructorTest, BasicMatrix) {
  Matrix a;

  int rows = a.GetRows();
  int cols = a.GetCols();

  EXPECT_EQ(rows, 0);
  EXPECT_EQ(cols, 0);
}

// Parametered:
TEST(ParameteredConstructorTest, ExampleOne) {
  Matrix a(4, 5);

  int rows = a.GetRows();
  int cols = a.GetCols();

  EXPECT_EQ(rows, 4);
  EXPECT_EQ(cols, 5);
}

// Copy:
TEST(CopyConstructorTest, ExampleOne) {
  Matrix a(4, 5);
  a.SetMatrixWithValue(2);
  Matrix b(a);

  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, true);
}

// Move:
TEST(MoveConstructorTest, ExampleOne) {
  Matrix a(4, 5);
  a.SetMatrixWithValue(2);

  Matrix tmp = a;

  Matrix b(std::move(a));

  bool res = b.EqMatrix(tmp);
  EXPECT_EQ(res, true);

  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
}

// Destruct:
TEST(DestructorTest, ExampleOne) {
  Matrix a(4, 5);
  a.SetMatrixWithValue(2);

  a.~Matrix();

  EXPECT_EQ(a.GetRows(), 0);
  EXPECT_EQ(a.GetCols(), 0);
}

// --------------------------------------------------Setters-------------------------------------------------------------------
// SetRows:
TEST(SetRowsTest, Up) {
  Matrix a(3, 3);
  EXPECT_EQ(a.GetRows(), 3);
  a.SetRows(5);
  EXPECT_EQ(a.GetRows(), 5);
}

TEST(SetRowsTest, Down) {
  Matrix b(3, 3);
  EXPECT_EQ(b.GetRows(), 3);
  b.SetRows(2);
  EXPECT_EQ(b.GetRows(), 2);
}

TEST(SetRowsTest, Equal) {
  Matrix c(3, 3);
  EXPECT_EQ(c.GetRows(), 3);
  c.SetRows(3);
  EXPECT_EQ(c.GetRows(), 3);
}

// SetCols:
TEST(SetColsTest, Up) {
  Matrix a1(3, 3);
  a1.SetCols(5);
  EXPECT_EQ(a1.GetCols(), 5);
}

TEST(SetColsTest, Down) {
  Matrix c1(3, 3);
  c1.SetCols(2);
  EXPECT_EQ(c1.GetCols(), 2);
}

TEST(SetColsTest, Equal) {
  Matrix c1(3, 3);
  c1.SetCols(3);
  EXPECT_EQ(c1.GetCols(), 3);
}

// SetMatrix:
TEST(SetMatrix, ExampleOne) {
  Matrix a(3, 3);
  Matrix b(3, 3);
  a.SetMatrix();

  b(0, 0) = 0;
  b(0, 1) = 0;
  b(0, 2) = 0;

  b(1, 0) = 0;
  b(1, 1) = 0;
  b(1, 2) = 0;

  b(2, 0) = 0;
  b(2, 1) = 0;
  b(2, 2) = 0;

  bool expect = a == b;
  EXPECT_EQ(expect, true);
}

// SetMatrixWithValue:
TEST(SetMatrixWithValue, ExampleOne) {
  Matrix a(3, 3);
  Matrix b(3, 3);
  a.SetMatrixWithValue(3);

  b(0, 0) = 3;
  b(0, 1) = 4;
  b(0, 2) = 5;

  b(1, 0) = 6;
  b(1, 1) = 7;
  b(1, 2) = 8;

  b(2, 0) = 9;
  b(2, 1) = 10;
  b(2, 2) = 11;

  bool expect = a == b;
  EXPECT_EQ(expect, true);
}

// SetMatrixWithOneValue:
TEST(SetMatrixWithOneValue, ExampleOne) {
  Matrix a(3, 3);
  Matrix b(3, 3);
  a.SetMatrixWithOneValue(3);

  b(0, 0) = 3;
  b(0, 1) = 3;
  b(0, 2) = 3;

  b(1, 0) = 3;
  b(1, 1) = 3;
  b(1, 2) = 3;

  b(2, 0) = 3;
  b(2, 1) = 3;
  b(2, 2) = 3;

  bool expect = a == b;
  EXPECT_EQ(expect, true);
}

// --------------------------------------------------Getters-------------------------------------------------------------------
// GetRows:
TEST(GetRowsTest, ExampleOne) {
  Matrix a(4, 3);
  EXPECT_EQ(a.GetRows(), 4);
}

// GetCols:
TEST(GetColsTest, ExampleOne) {
  Matrix a(3, 6);
  EXPECT_EQ(a.GetCols(), 6);
}

// --------------------------------------------------MainFunctions-----------------------------------------
//  EqMatrix:
TEST(EqMatrixTest, ZeroMatrixEqual) {
  Matrix a(3, 3);
  Matrix b(3, 3);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, true);
}

TEST(EqMatrixTest, SameSizeDifferentValue) {
  Matrix a(3, 3);
  Matrix b(3, 3);
  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 6
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 7
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, false);
}

TEST(EqMatrixTest, DifferentSize) {
  Matrix a(4, 3);
  Matrix b(3, 5);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, false);
}

TEST(EqMatrixTest, EqualMatrix) {
  Matrix a(5, 4);
  Matrix b(5, 4);
  a.SetMatrixWithValue(10);
  b.SetMatrixWithValue(10);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, true);
}

// SumMatrix:
TEST(SumMatrixTest, ZeroMatrix) {
  Matrix a(4, 4);
  Matrix b(4, 4);
  a.SumMatrix(b);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, true);
}

TEST(SumMatrixTest, RandomMatrices) {
  Matrix a(4, 4);
  Matrix b(4, 4);
  Matrix result(4, 4);

  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 16
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 17

  a.SumMatrix(b);

  result(0, 0) = 3;
  result(0, 1) = 5;
  result(0, 2) = 7;
  result(0, 3) = 9;

  result(1, 0) = 11;
  result(1, 1) = 13;
  result(1, 2) = 15;
  result(1, 3) = 17;

  result(2, 0) = 19;
  result(2, 1) = 21;
  result(2, 2) = 23;
  result(2, 3) = 25;

  result(3, 0) = 27;
  result(3, 1) = 29;
  result(3, 2) = 31;
  result(3, 3) = 33;

  bool res = a.EqMatrix(result);
  EXPECT_EQ(res, true);
}

TEST(SubMatrixTest, ZeroMatrix) {
  Matrix a(4, 4);
  Matrix b(4, 4);
  a.SubMatrix(b);
  bool res = a.EqMatrix(b);
  EXPECT_EQ(res, true);
}

TEST(SubmatrixTest, RandomMatrices) {
  Matrix a(4, 4);
  Matrix b(4, 4);
  Matrix result(4, 4);

  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 16
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 17

  a.SubMatrix(b);

  result.SetMatrixWithOneValue(-1);

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// MulNumber:
TEST(MulNumberTest, ExampleOne) {
  Matrix a(2, 3);
  a.SetMatrixWithValue(3);

  Matrix result(2, 3);

  result(0, 0) = 9;
  result(0, 1) = 12;
  result(0, 2) = 15;

  result(1, 0) = 18;
  result(1, 1) = 21;
  result(1, 2) = 24;

  a.MulNumber(3);
  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// MulMatrix:
TEST(MulMatrixTest, SquareMatrices) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(1);

  Matrix b(3, 3);
  b.SetMatrixWithValue(2);

  Matrix result(3, 3);
  result(0, 0) = 36;
  result(0, 1) = 42;
  result(0, 2) = 48;

  result(1, 0) = 81;
  result(1, 1) = 96;
  result(1, 2) = 111;

  result(2, 0) = 126;
  result(2, 1) = 150;
  result(2, 2) = 174;

  a.MulMatrix(b);

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

TEST(MulMatrixTest, RowsEqualToCols) {
  Matrix a(4, 3);
  a.SetMatrixWithValue(1);

  Matrix b(3, 4);
  b.SetMatrixWithValue(2);

  Matrix result(4, 4);
  result(0, 0) = 44;
  result(0, 1) = 50;
  result(0, 2) = 56;
  result(0, 3) = 62;

  result(1, 0) = 98;
  result(1, 1) = 113;
  result(1, 2) = 128;
  result(1, 3) = 143;

  result(2, 0) = 152;
  result(2, 1) = 176;
  result(2, 2) = 200;
  result(2, 3) = 224;

  result(3, 0) = 206;
  result(3, 1) = 239;
  result(3, 2) = 272;
  result(3, 3) = 305;

  a.MulMatrix(b);

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Transpose:
TEST(TransposeTest, SquareMatrix) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(1);
  a = a.Transpose();

  Matrix result(3, 3);
  result(0, 0) = 1;
  result(0, 1) = 4;
  result(0, 2) = 7;

  result(1, 0) = 2;
  result(1, 1) = 5;
  result(1, 2) = 8;

  result(2, 0) = 3;
  result(2, 1) = 6;
  result(2, 2) = 9;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

TEST(TransposeTest, NotSquareMatrix) {
  Matrix a(5, 3);
  a.SetMatrixWithValue(1);
  a = a.Transpose();

  Matrix result(3, 5);
  result(0, 0) = 1;
  result(0, 1) = 4;
  result(0, 2) = 7;
  result(0, 3) = 10;
  result(0, 4) = 13;

  result(1, 0) = 2;
  result(1, 1) = 5;
  result(1, 2) = 8;
  result(1, 3) = 11;
  result(1, 4) = 14;

  result(2, 0) = 3;
  result(2, 1) = 6;
  result(2, 2) = 9;
  result(2, 3) = 12;
  result(2, 4) = 15;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// CalcComplements:
TEST(CalcComplementsTest, ExampleOne) {
  Matrix a(3, 3);
  a(0, 0) = 12;
  a(0, 1) = 7;
  a(0, 2) = 25;

  a(1, 0) = 2;
  a(1, 1) = 5;
  a(1, 2) = 8;

  a(2, 0) = 3;
  a(2, 1) = 6;
  a(2, 2) = 9;

  a = a.CalcComplements();

  Matrix result(3, 3);
  result(0, 0) = -3;
  result(0, 1) = 6;
  result(0, 2) = -3;

  result(1, 0) = 87;
  result(1, 1) = 33;
  result(1, 2) = -51;

  result(2, 0) = -69;
  result(2, 1) = -46;
  result(2, 2) = 46;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

TEST(CalcComplementsTest, ExampleTwo) {
  Matrix a(3, 3);

  a(0, 0) = 1;
  a(0, 1) = 2;
  a(0, 2) = 3;

  a(1, 0) = 0;
  a(1, 1) = 4;
  a(1, 2) = 2;

  a(2, 0) = 5;
  a(2, 1) = 2;
  a(2, 2) = 1;

  a = a.CalcComplements();

  Matrix result(3, 3);
  result(0, 0) = 0;
  result(0, 1) = 10;
  result(0, 2) = -20;

  result(1, 0) = 4;
  result(1, 1) = -14;
  result(1, 2) = 8;

  result(2, 0) = -8;
  result(2, 1) = -2;
  result(2, 2) = 4;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Determinant:
TEST(DeterminantTest, ExampleOne) {
  Matrix a(3, 3);
  a(0, 0) = 12;
  a(0, 1) = 7;
  a(0, 2) = 25;

  a(1, 0) = 2;
  a(1, 1) = 5;
  a(1, 2) = 8;

  a(2, 0) = 3;
  a(2, 1) = 6;
  a(2, 2) = 9;

  double determinant = a.Determinant();
  double result = -69;

  EXPECT_EQ(determinant, result);
}

TEST(DeterminantTest, IdentityMatrix) {
  Matrix a(3, 3);
  a(0, 0) = 1;
  a(0, 1) = 0;
  a(0, 2) = 0;

  a(1, 0) = 0;
  a(1, 1) = 1;
  a(1, 2) = 0;

  a(2, 0) = 0;
  a(2, 1) = 0;
  a(2, 2) = 1;

  double determinant = a.Determinant();
  double result = 1;

  EXPECT_EQ(determinant, result);
}

TEST(DeterminantTest, SingletonMatrix) {
  Matrix a(1, 1);
  a.SetMatrixWithValue(46);

  double determinant = a.Determinant();
  double result = 46;

  EXPECT_EQ(determinant, result);
}

TEST(DeterminantTest, ZeroDeterminant) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(1);

  double determinant = a.Determinant();
  double result = 0.00;

  EXPECT_EQ(determinant, result);
}

TEST(DeterminantTest, SquareMatrixTwoRows) {
  Matrix a(2, 2);
  a(0, 0) = 12;
  a(0, 1) = 7;

  a(1, 0) = 2;
  a(1, 1) = 5;

  double determinant = a.Determinant();
  double result = 46;

  EXPECT_EQ(determinant, result);
}

// InverseMatrix:
TEST(InverseMatrixTest, SquareMatrixOne) {
  Matrix a(3, 3);
  a(0, 0) = 1.0;
  a(0, 1) = 2.0;
  a(0, 2) = 3.0;

  a(1, 0) = 0.0;
  a(1, 1) = 4.0;
  a(1, 2) = 2.0;

  a(2, 0) = 5.0;
  a(2, 1) = 2.0;
  a(2, 2) = 1.0;

  a = a.InverseMatrix();

  Matrix result(3, 3);
  result(0, 0) = 0.0;
  result(0, 1) = -0.1;
  result(0, 2) = 0.2;

  result(1, 0) = -0.25;
  result(1, 1) = 0.35;
  result(1, 2) = 0.05;

  result(2, 0) = 0.5;
  result(2, 1) = -0.2;
  result(2, 2) = -0.1;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

TEST(InverseMatrixTest, SquareMatrixTwo) {
  Matrix a(3, 3);
  a(0, 0) = 2;
  a(0, 1) = 5;
  a(0, 2) = 10;

  a(1, 0) = 3;
  a(1, 1) = 7;
  a(1, 2) = 25;

  a(2, 0) = 9;
  a(2, 1) = 34;
  a(2, 2) = 20;

  a = a.InverseMatrix();

  Matrix result(3, 3);
  result(0, 0) = 3.46341463415;
  result(0, 1) = -1.17073170732;
  result(0, 2) = -0.26829268292;

  result(1, 0) = -0.80487804878;
  result(1, 1) = 0.24390243902;
  result(1, 2) = 0.0975609756;

  result(2, 0) = -0.19024390243;
  result(2, 1) = 0.11219512195;
  result(2, 2) = 0.00487804878;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// --------------------------------------------------Operators-------------------------------------------------------------------
// Operator+:
TEST(OperatorPlusTest, RandomMatrices) {
  Matrix a(4, 4);
  Matrix b(4, 4);

  Matrix c(4, 4);
  Matrix result(4, 4);

  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 16
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 17

  c = a + b;

  result(0, 0) = 3;
  result(0, 1) = 5;
  result(0, 2) = 7;
  result(0, 3) = 9;

  result(1, 0) = 11;
  result(1, 1) = 13;
  result(1, 2) = 15;
  result(1, 3) = 17;

  result(2, 0) = 19;
  result(2, 1) = 21;
  result(2, 2) = 23;
  result(2, 3) = 25;

  result(3, 0) = 27;
  result(3, 1) = 29;
  result(3, 2) = 31;
  result(3, 3) = 33;

  bool res = c.EqMatrix(result);
  EXPECT_EQ(res, true);
}

// Operator-:
TEST(OperatorMinusTest, RandomMatrices) {
  Matrix a(4, 4);
  Matrix b(4, 4);
  Matrix result(4, 4);

  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 16
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 17

  result = a - b;

  result.SetMatrixWithOneValue(-1);

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Operator*Number:
TEST(OperatorMulNumberTest, ExampleOne) {
  Matrix a(2, 3);
  a.SetMatrixWithValue(3);

  Matrix result(2, 3);

  result(0, 0) = 9;
  result(0, 1) = 12;
  result(0, 2) = 15;

  result(1, 0) = 18;
  result(1, 1) = 21;
  result(1, 2) = 24;

  a * 3;
  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);

  3 * a;
  expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Operator*Matrix:
TEST(OperatorMulMatrixTest, SquareMatrices) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(1);

  Matrix b(3, 3);
  b.SetMatrixWithValue(2);

  Matrix result(3, 3);
  result(0, 0) = 36;
  result(0, 1) = 42;
  result(0, 2) = 48;

  result(1, 0) = 81;
  result(1, 1) = 96;
  result(1, 2) = 111;

  result(2, 0) = 126;
  result(2, 1) = 150;
  result(2, 2) = 174;

  a *b;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Operator==Matrix:
TEST(OperatorEqMatrixTest, SameSizeDifferentValue) {
  Matrix a(3, 3);
  Matrix b(3, 3);
  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 6
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 7
  bool res = a == b;
  EXPECT_EQ(res, false);
}

// Operator=Matrix:
TEST(OperatorAssignmentTest, SquareMatrices) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(1);

  Matrix b(3, 3);
  a = b;

  bool expect = a.EqMatrix(b);
  EXPECT_EQ(expect, true);
}

TEST(OperatorAssignmentTest, ThreeMatrices) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(1);

  Matrix b(4, 3);
  Matrix c = b = a;

  bool expect = a.EqMatrix(c);
  EXPECT_EQ(expect, true);

  expect = c.EqMatrix(b);
  EXPECT_EQ(expect, true);
}

// Operator+=:
TEST(OperatorPlusEqualTest, RandomMatrices) {
  Matrix a(4, 4);
  Matrix b(4, 4);
  Matrix result(4, 4);

  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 16
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 17

  a += b;

  result(0, 0) = 3;
  result(0, 1) = 5;
  result(0, 2) = 7;
  result(0, 3) = 9;

  result(1, 0) = 11;
  result(1, 1) = 13;
  result(1, 2) = 15;
  result(1, 3) = 17;

  result(2, 0) = 19;
  result(2, 1) = 21;
  result(2, 2) = 23;
  result(2, 3) = 25;

  result(3, 0) = 27;
  result(3, 1) = 29;
  result(3, 2) = 31;
  result(3, 3) = 33;

  bool res = a.EqMatrix(result);
  EXPECT_EQ(res, true);
}

// Operator-=:
TEST(OperatorMinusEqualTest, RandomMatrices) {
  Matrix a(4, 4);
  Matrix b(4, 4);
  Matrix result(4, 4);

  a.SetMatrixWithValue(1);  // fill matrix with numbers from 1 to 16
  b.SetMatrixWithValue(2);  // fill matrix with numbers from 2 to 17

  a -= b;

  result.SetMatrixWithOneValue(-1);

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Operator*=Number:
TEST(OperatorMulEqualNumberTest, ExampleOne) {
  Matrix a(2, 3);
  a.SetMatrixWithValue(3);

  Matrix result(2, 3);

  result(0, 0) = 9;
  result(0, 1) = 12;
  result(0, 2) = 15;

  result(1, 0) = 18;
  result(1, 1) = 21;
  result(1, 2) = 24;

  a *= 3;
  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Operator*=Matrix:
TEST(OperatorMulEqualMatrixTest, SquareMatrices) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(1);

  Matrix b(3, 3);
  b.SetMatrixWithValue(2);

  Matrix result(3, 3);
  result(0, 0) = 36;
  result(0, 1) = 42;
  result(0, 2) = 48;

  result(1, 0) = 81;
  result(1, 1) = 96;
  result(1, 2) = 111;

  result(2, 0) = 126;
  result(2, 1) = 150;
  result(2, 2) = 174;

  a *= b;

  bool expect = a.EqMatrix(result);
  EXPECT_EQ(expect, true);
}

// Operator():
TEST(OperatorIndexTest, SquareMatrix) {
  Matrix a(3, 3);
  a.SetMatrixWithValue(10);

  double res = a(0, 0);
  double expect = 10;
  EXPECT_EQ(expect, res);

  res = a(0, 1);
  expect = 11;
  EXPECT_EQ(expect, res);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
