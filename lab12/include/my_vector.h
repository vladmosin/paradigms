#pragma once

//#include "my_vector_impl.h"
#include <cstddef>
#include <iostream>

template <class T>
class my_vector {
public: // methods
  my_vector();
  my_vector(std::size_t init_capacity);
  my_vector(const my_vector<T>& other);
  my_vector<T>& operator=(my_vector<T> other);
  ~my_vector();

  std::size_t size() const { return _size; };
  std::size_t capacity() const { return _capacity; };
  bool empty() const { return _size == 0; };

  void reserve(std::size_t new_capacity);
  void resize(std::size_t new_size);
  
  T& operator[](std::size_t index);
  const T& operator[](std::size_t index) const;
  friend std::ostream& operator<<(std::ostream& out, my_vector<T>& mv) {
    for (std::size_t i = 0; i < mv.size(); i++) {
        out << mv._array[i] << ' ';
    }
    return out;
  };  
  void push_back(const T& t);
  void pop_back();
  void clear();
private: // fields
  std::size_t _size, _capacity;
  T *_array;
};

static std::size_t two_pow(std::size_t n) {
    std::size_t res = 1;
    while (res < n)
        res *= 2;
    return res;
} 

template <class T>
my_vector<T>::my_vector() :
    _size(0),
    _capacity(2)
{
    _array = reinterpret_cast<T*> (new uint8_t[2 * sizeof(T)]);
}

template <class T>
my_vector<T>::my_vector(std::size_t init_size) :
    _size(0),
    _capacity(two_pow(init_size))
{
    _array = reinterpret_cast<T*> (new uint8_t[_capacity * sizeof(T)]);
    resize(init_size);
}

template <class T>
my_vector<T>::my_vector(const my_vector<T>& other)  :
    _size(0),
    _capacity(other.capacity())
{
    _array = reinterpret_cast<T*> (new uint8_t[other._capacity * sizeof(T)]);
    for (std::size_t i = 0; i < other.size(); i++) {
        push_back(other._array[i]);
    }
} 

template <class T>
my_vector<T>& my_vector<T>::operator=(my_vector<T> other) {
    std::swap(_array, other._array);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    return *this;
}

template <class T>
my_vector<T>::~my_vector<T>() {
    for (std::size_t i = 0; i < _size; i++)
        _array[i].~T();
    delete [] reinterpret_cast<uint8_t*> (_array);
}

template <class T>
void my_vector<T>::reserve(std::size_t new_capacity) {
    if (new_capacity <= _capacity)
        return;
    T* tmp = reinterpret_cast<T*> (new uint8_t[two_pow(new_capacity) * sizeof(T)]);
    for (std::size_t i = 0; i < _size; i++) {
        new(&tmp[i]) T(_array[i]);
    }
    int size = _size;
    clear();
    delete [] reinterpret_cast<uint8_t*> (_array);
    _array = tmp;
    tmp = NULL;
    _capacity = two_pow(new_capacity);
    _size = size;
}

template <class T>
void my_vector<T>::resize(std::size_t new_size) {
    if (new_size > _capacity)
        reserve(new_size);
    for (std::size_t i = _size; i > new_size; i--) {
        pop_back();
    }
    for (std::size_t i = _size; i < new_size; i++) {
        new(&_array[i]) T();
    }
    _size = new_size;
}

template <class T>
T& my_vector<T>::operator[](std::size_t index) {
    return _array[index];
}

template <class T>
const T& my_vector<T>::operator[](std::size_t index) const {
    return _array[index];
}

template <class T>
void my_vector<T>::push_back(const T& t) {
    if (_size == _capacity) {
        reserve(2 * _size);
    }
    new(&_array[_size++]) T(t);
}

template <class T>
void my_vector<T>::pop_back() {
    _size--;
    _array[_size].~T();
}

template <class T>
void my_vector<T>::clear() {
    while (!empty())
        pop_back();
}
