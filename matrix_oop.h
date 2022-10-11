#pragma once
#include <cmath>
#include <stdexcept>

class Matrix {
 public:
  // --------------------------------------------------Constructors-------------------------------------------------------------------
  Matrix();
  Matrix(int rows, int cols);

  // destructor
  ~Matrix();

  // copy and move:
  Matrix(const Matrix &other);
  Matrix(Matrix &&other);

  // --------------------------------------------------Setters-------------------------------------------------------------------
  void SetRows(int value_rows);
  void SetCols(int value_cols);
  void SetMatrix();
  void SetMatrixWithValue(int value_start);
  void SetMatrixWithOneValue(int value);
  // --------------------------------------------------Getters-------------------------------------------------------------------
  double GetRows();
  double GetCols();

  // --------------------------------------------------MainFunctions-----------------------------------------------------------
  bool EqMatrix(const Matrix &other);
  void SumMatrix(const Matrix &other);
  void SubMatrix(const Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const Matrix &other);
  Matrix Transpose();
  Matrix CalcComplements();
  double Determinant();
  Matrix InverseMatrix();

  // --------------------------------------------------Operators-------------------------------------------------------------------
  Matrix operator+(const Matrix &other);
  Matrix operator-(const Matrix &other);
  Matrix operator*(const Matrix &other);
  Matrix operator*(double num);
  friend Matrix operator*(double num, const Matrix &other);
  bool operator==(const Matrix other);
  Matrix &operator=(const Matrix &other);
  Matrix &operator+=(const Matrix &other);
  Matrix &operator-=(const Matrix &other);
  Matrix &operator*=(const Matrix &other);
  Matrix &operator*=(double num);
  double &operator()(int i, int j);

 private:
  int rows_;
  int cols_;
  double **matrix_;

  // --------------------------------------------------Subfunctions-------------------------------------------------------------------
  void AllocateMemory();
  void DeallocateMemory();
  bool IsEqSize(const Matrix &other);
  Matrix MinorMatrix();
  void CopyMatrix(const Matrix &other);
  void CropMatrix(int index_i, int index_j);
};
