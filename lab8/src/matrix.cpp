#include <cstring>
#include <cstdio>
#include <algorithm>
#include "matrix.h"

Matrix::Matrix(std::size_t const rows, std::size_t const cols) {
    _rows = rows;
    _cols = cols;
    _data = new int*[_rows];
    for (std::size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols];
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] = 0;
}

Matrix::Matrix(const Matrix &other) :
    Matrix(other._rows, other._cols)
{
    for (std::size_t i = 0; i < _rows; i++)
        memcpy(_data[i], other._data[i], _cols * sizeof(int));
}

void Matrix::swap(Matrix& m) {
    std::swap(_rows, m._rows);
    std::swap(_cols, m._cols);
    std::swap(_data, m._data);
}

Matrix& Matrix::operator=(Matrix m) {
    m.swap(*this);
    return *this;
}

Matrix& Matrix::operator+=(const Matrix& m) {
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] += m._data[i][j];
    return *this; 
}

Matrix Matrix::operator+(const Matrix& m) const {
    return Matrix(*this) += m;
}

Matrix Matrix::operator*(const Matrix& m) const{
    Matrix tmp(_rows, m._cols);
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t k = 0; k < _cols; k++)
            for (std::size_t j = 0; j < m._cols; j++)
                tmp._data[i][j] += _data[i][k] * m._data[k][j];
    return tmp;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    Matrix tmp((*this) * m);
    swap(tmp);
    return (*this);
}

Matrix& Matrix::operator-=(const Matrix& m) {
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] -= m._data[i][j];
    return *this; 
}

 Matrix Matrix::operator-(const Matrix& m) const {
    return Matrix(*this) -= m;
 }
 
bool Matrix::operator!=(const Matrix& m) const {
    if (_rows != m._rows || _cols != m._cols)
        return true;
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            if (_data[i][j] != m._data[i][j])
                return true;
    return false;
}

bool Matrix::operator==(const Matrix& m) const {
    return !(*this != m);
}

void Matrix::set(std::size_t const x, std::size_t const y, int const value) {
    _data[x][y] = value;
}

int Matrix::get(std::size_t const x, std::size_t const y) const {
    return _data[x][y];
}

void Matrix::print(FILE* f) const {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++)
            fprintf(f, "%d ", _data[i][j]);
        fprintf(f, "\n");
    }
}

std::size_t Matrix::get_rows() const {
    return _rows;
}

std::size_t Matrix::get_cols() const {
    return _cols;
}

Matrix::~Matrix() {
    for (std::size_t i = 0; i < _rows; i++) 
        delete [] _data[i];
    delete [] _data;
}
