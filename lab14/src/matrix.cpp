#include "matrix.h"
#include <fstream>

Matrix::Matrix(std::size_t const rows, std::size_t const cols) {
    _rows = rows;
    _cols = cols;
    _data = new int*[_rows];
    if (_data == NULL) {
        throw MatrixException("load: problems with memory");
    }
    for (std::size_t i = 0; i < _rows; i++)
        _data[i] = new int[_cols];
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] = 0;
}

Matrix::Matrix():
    _rows(0), _cols(0), _data(NULL)
{}

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
    if ((m.get_rows() != _rows) || (m.get_cols() != _cols)) {
        throw MatrixException("ADD: dimensions do not match.");
    }
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t j = 0; j < _cols; j++)
            _data[i][j] += m._data[i][j];
    return *this; 
}

Matrix Matrix::operator+(const Matrix& m) const {
    return Matrix(*this) += m;
}

Matrix Matrix::operator*(const Matrix& m) const{
    if (_cols != m.get_rows()) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    Matrix tmp(_rows, m._cols);
    for (std::size_t i = 0; i < _rows; i++)
        for (std::size_t k = 0; k < _cols; k++)
            for (std::size_t j = 0; j < m._cols; j++)
                tmp._data[i][j] += _data[i][k] * m._data[k][j];
    return tmp;
}

Matrix& Matrix::operator*=(const Matrix& m) {
    try {
        Matrix tmp((*this) * m);
        tmp.swap(*this);
    } catch(MatrixException &e) {
        throw;
    }
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
    if (_rows != m.get_rows() || _cols != m.get_cols())
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

int Matrix::get(int x, int y) const {
    if (x < 0 || y < 0 || x >= int(_rows) || y >= int(_cols)) {
        throw MatrixException("ACCESS: bad index.");
    }
    return _data[x][y];
}

void Matrix::print() const {
    for (std::size_t i = 0; i < _rows; i++) {
        for (std::size_t j = 0; j < _cols; j++)
            std::cout << _data[i][j] << ' ';
        std::cout << "\n";
    }
}

void Matrix::load(std::ifstream& in) {
    std::size_t rows = 0, cols = 0;
    int val = 0;
    in >> rows >> cols;
    Matrix tmp(rows, cols);
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            in >> val;
            tmp.set(i, j, val);
        }
    }
    tmp.swap(*this);
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

MatrixException::MatrixException(const char* exception) {
    _exception = new char[strlen(exception) + 1];
    strcpy(_exception, exception);
}
