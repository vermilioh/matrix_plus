#include "matrix_oop.h"

// --------------------------------------------------Constructors-------------------------------------------------------------------
Matrix::Matrix() : rows_(0), cols_(0), matrix_(nullptr) {}

Matrix::Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  AllocateMemory();
}

// copy:
Matrix::Matrix(const Matrix &other) : Matrix(other.rows_, other.cols_) {
  CopyMatrix(other);
}

// move:
Matrix::Matrix(Matrix &&other) {
  rows_ = other.rows_;
  cols_ = other.cols_;
  matrix_ = other.matrix_;

  other.matrix_ = nullptr;
  other.cols_ = 0;
  other.rows_ = 0;
}

// destructor:
Matrix::~Matrix() {
  if (matrix_ != nullptr) {
    DeallocateMemory();
    rows_ = 0;
    cols_ = 0;
  }
}

// --------------------------------------------------Setters-------------------------------------------------------------------

// change rows num: if up - set new cells  with 0, if down - destroy wasted
void Matrix::SetRows(int value_rows) {
  Matrix tmp_matrix(value_rows, cols_);
  tmp_matrix.CopyMatrix(*this);
  DeallocateMemory();
  rows_ = value_rows;
  AllocateMemory();
  *this = tmp_matrix;
}

// change cols num: if up - set new cells  with 0, if down - destroy wasted
void Matrix::SetCols(int value_cols) {
  Matrix tmp_matrix(rows_, value_cols);
  tmp_matrix.CopyMatrix(*this);
  DeallocateMemory();
  cols_ = value_cols;
  AllocateMemory();
  *this = tmp_matrix;
}

// set whole matrix with 0
void Matrix::SetMatrix() {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] = 0.00;
    }
  }
}

// set whole matrix starting with value_start, each matrix cell +=1
void Matrix::SetMatrixWithValue(int value_start) {
  value_start -= 1;
  if (rows_ > 0 && cols_ > 0) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = value_start += 1;
      }
    }
  }
}

// equal value for each cell of matrix
void Matrix::SetMatrixWithOneValue(int value) {
  if (rows_ > 0 && cols_ > 0) {
    for (int i = 0; i < rows_; ++i) {
      for (int j = 0; j < cols_; ++j) {
        matrix_[i][j] = value;
      }
    }
  }
}

// --------------------------------------------------Getters-------------------------------------------------------------------

double Matrix::GetRows() { return rows_; }

double Matrix::GetCols() { return cols_; }

// --------------------------------------------------MainFunctions----------------------------------------------------

bool Matrix::EqMatrix(const Matrix &other) {
  const double epsilon = 1e-7;
  bool res = false;
  if (IsEqSize(other)) {
    res = true;
    for (int i = 0; (i < rows_) && (res != false); ++i) {
      for (int j = 0; (j < cols_) && (res != false); ++j) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > epsilon) {
          res = false;
        }
      }
    }
  }
  return res;
}

void Matrix::SumMatrix(const Matrix &other) {
  if (!IsEqSize(other)) {
    throw std::out_of_range("Matrices have different size!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void Matrix::SubMatrix(const Matrix &other) {
  if (!IsEqSize(other)) {
    throw std::out_of_range("Matrices have different size!");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      matrix_[i][j] *= num;
    }
  }
}

void Matrix::MulMatrix(const Matrix &other) {
  if (cols_ != other.rows_) {
    throw std::out_of_range("COLS in first matrix should = to ROWS insecond");
  }

  Matrix res(rows_, other.cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < res.cols_; ++j) {
      for (int k = 0; k < cols_; ++k) {
        res.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = res;
}

Matrix Matrix::Transpose() {
  Matrix transposed(cols_, rows_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      transposed.matrix_[j][i] = matrix_[i][j];
    }
  }
  return transposed;
}

Matrix Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::out_of_range("Use only square matrix");
  }
  Matrix res(rows_, cols_);
  res = this->MinorMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      res.matrix_[i][j] *= pow(-1, (i + j));
    }
  }
  return res;
}

double Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::out_of_range("Use only square matrix");
  }

  double det = 0.00;
  if (rows_ == 1) {
    det = matrix_[0][0];
  } else if (rows_ == 2) {
    det = matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    int degree = 1;
    for (int i = 0; i < cols_; ++i) {
      Matrix tmp(*this);
      tmp.CropMatrix(0, i);
      det += degree * matrix_[0][i] * tmp.Determinant();
      degree *= -1;
    }
  }

  return det;
}

Matrix Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::out_of_range("Use only square matrix");
  }
  double determinant = this->Determinant();
  if (determinant == 0.0) {
    throw std::out_of_range("Determinant = 0, there is no inversed matrix.");
  }

  Matrix res(rows_, cols_);
  res = this->CalcComplements().Transpose();
  res *= (1 / determinant);
  return res;
}

// --------------------------------------------------Operators-------------------------------------------------------------------

Matrix Matrix::operator+(const Matrix &other) {
  SumMatrix(other);
  Matrix res = *this;
  return res;
}

Matrix Matrix::operator-(const Matrix &other) {
  SubMatrix(other);
  Matrix res = *this;
  return res;
}

Matrix Matrix::operator*(const Matrix &other) {
  MulMatrix(other);
  Matrix res = *this;
  return res;
}

Matrix Matrix::operator*(double num) {
  MulNumber(num);
  Matrix res = *this;
  return res;
}

Matrix operator*(double num, const Matrix &other) {
  Matrix res;
  res = other;
  res.MulNumber(num);
  return res;
}

bool Matrix::operator==(const Matrix other) { return EqMatrix(other); }

Matrix &Matrix::operator=(const Matrix &other) {
  if (matrix_ != nullptr) {
    DeallocateMemory();
  }
  this->rows_ = other.rows_;
  this->cols_ = other.cols_;

  AllocateMemory();
  CopyMatrix(other);

  return *this;
}

Matrix &Matrix::operator+=(const Matrix &other) {
  SumMatrix(other);
  return *this;
}

Matrix &Matrix::operator-=(const Matrix &other) {
  SubMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(const Matrix &other) {
  MulMatrix(other);
  return *this;
}

Matrix &Matrix::operator*=(double num) {
  MulNumber(num);
  return *this;
}

double &Matrix::operator()(int i, int j) {
  if (i >= 0 && rows_ > i && j >= 0 && cols_ > j) {
    return matrix_[i][j];
  } else {
    throw std::out_of_range("Index is out of range!");
  }
}

// --------------------------------------------------SubFunctions----------------------------------------------------

void Matrix::CopyMatrix(const Matrix &other) {
  int stop_rows = std::min(rows_, other.rows_);
  int stop_cols = std::min(cols_, other.cols_);

  for (int i = 0; i < stop_rows; ++i) {
    for (int j = 0; j < stop_cols; ++j) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

bool Matrix::IsEqSize(const Matrix &other) {
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    return true;
  } else {
    return false;
  }
}

void Matrix::AllocateMemory() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Value of rows and cols must be more than 0");
  }
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; ++i) {
    matrix_[i] = new double[cols_]{};
  }
}

void Matrix::DeallocateMemory() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
  matrix_ = nullptr;
}

Matrix Matrix::MinorMatrix() {
  if (rows_ != cols_) {
    throw std::out_of_range("Use only square matrix");
  }
  Matrix res(rows_, cols_);
  for (int i = 0; i < rows_; ++i) {
    for (int j = 0; j < cols_; ++j) {
      Matrix tmp(*this);
      tmp.CropMatrix(i, j);
      res.matrix_[i][j] = tmp.Determinant();
    }
  }
  return res;
}

void Matrix::CropMatrix(int index_i, int index_j) {
  Matrix tmp(rows_ - 1, cols_ - 1);
  int jump_row = 0;
  int jump_col = 0;
  for (int i = 0; i < rows_ - 1; ++i) {
    if (i == index_i) {
      jump_row = 1;
    }
    jump_col = 0;
    for (int j = 0; j < cols_ - 1; ++j) {
      if (j == index_j) {
        jump_col = 1;
      }
      tmp.matrix_[i][j] = matrix_[i + jump_row][j + jump_col];
    }
  }
  *this = tmp;
}
