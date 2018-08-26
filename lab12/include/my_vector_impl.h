#pragma once

#include "my_vector.h"
#include <cstring>
#include <stdint.h>

static std::size_t two_pow(std::size_t n) {
    std::size_t res = 1;
    while (res < n)
        res *= 2;
    return res;
} 

template <class T>
my_vector<T>::my_vector<T>() :
    _size(0),
    _capacity(2)
{
    _array = reinterpret_cast<T> (new uint8_t[2 * sizeof(T)])
}

template <class T>
my_vector<T>::my_vector<T>(std::size_t init_capacity) :
    sz(0),
    cp(init_capacity)
{
    _array = reinterpret_cast<T> (new uint8_t[init_capacity * sizeof(T)])
}

template <class T>
my_vector<T>::my_vector<T>(my_vector<T>& other)  :
    _size(other.size()),
    _capacity(other.capacity())
{
    _array = reinterpret_cast<T> (new uint8_t[two_pow(new_capacity) * sizeof(T)])
    for (int i = 0; i < _size; i++) {
        new(&_array[i]) T(other[i]);
    }
} 

template <class T>
my_vector<T>& my_vector<T>::operator=(my_vector<T> other) {
    std::swap(_array, other._array);
    std::swap(_size, m._size);
    std::swap(_capacity, m._capacity);
    return *this;
}

template <class T>
my_vector<T>::~my_vector<T>() {
    for (int i = 0; i < _size; i++)
        _array[i].~T();
    delete [] _array;
}

template <class T>
void my_vector<T>::reserve(std::size_t new_capacity) {
    if (new_capacity <= cp)
        return;
    T* tmp = reinterpret_cast<T> (new uint8_t[two_pow(new_capacity) * sizeof(T)]);
    for (int i = 0; i < _size; i++) {
        new(&tmp[i]) T(_array[i]);
    }
    
    clear();
    delete [] _array;
    _array = tmp;
    tmp = NULL;
    _capacity = two_pow(new_capacity);
}

template <class T>
void my_vector<T>::resize(std::size_t new_size) {
    if (new_size > _capacity)
        reserve(new_size);
    if (new_size < _size) {
        for (int i = new_size; i< _size; i++) {
            _array[i].~T();
        }
    }
    else {
        for (int i = _size; i < new_size; i++) {
            new(&_array[i]) T();
        }
    }
    _size = new_size;
}

template <class T>
T& my_vector<T>::operator[](std::size_t index) {
    return _array[index];
}

template <class T>
void my_vector<T>::push_back(T& t) {
    if (_size == _capacity) {
        reserve(2 * _size);
    }
    new(&_array[_size]) T();
    _array[_size++] = t;
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
    _size = 0;
}

std::ostream& operator<<(std::ostream& out, my_vector<T>& mv) {
    for (int i = 0; i < mv._size(); i++) {
        out << _array[i] << ' ';
    }
    return out;
}   
