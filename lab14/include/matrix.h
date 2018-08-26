#pragma once
#include <cstdio>
#include <cstddef>
#include <cstring>
#include <algorithm>
#include <iostream>

class Matrix {
public:
  Matrix(std::size_t const r, std::size_t const c);
  Matrix(const Matrix& m);
  Matrix();
  ~Matrix();

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t const i, std::size_t const j, int const val);
  int get(int i, int j) const;
  void print() const;
  void swap(Matrix& m);
  void load(std::ifstream& in);
  
  Matrix operator+(const Matrix& m) const;
  Matrix operator-(const Matrix& m) const;
  Matrix operator*(const Matrix& m) const;
  
  Matrix& operator=(Matrix m);
  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

  bool operator==(const Matrix& m) const;
  bool operator!=(const Matrix& m) const;

private:
  std::size_t _rows;
  std::size_t _cols;
  int **_data;
};

class MatrixException {
public:
    MatrixException(const char* exception);
    char* get_exception() {
        return _exception;
    }
    ~MatrixException() {
        delete [] _exception;
    }
private:
    char* _exception;
};
