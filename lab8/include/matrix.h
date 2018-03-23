#pragma once
#include <cstdio>
#include <cstddef>

class Matrix {
public:
  Matrix(std::size_t const r, std::size_t const c);
  Matrix(const Matrix& m);
  ~Matrix();

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t const i, std::size_t const j, int const val);
  int get(std::size_t const i, std::size_t const j) const;
  void print(FILE *f) const;
  void swap(Matrix& m);
  
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
