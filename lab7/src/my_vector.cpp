#include <cstring>
#include "my_vector.h"


MyVector::MyVector() :
    sz(0),
    cp(2),
    data(new int[2])
{}

MyVector::MyVector(std::size_t init_capacity) :
    sz(0),
    cp(init_capacity),
    data(new int[init_capacity])
{}

MyVector::~MyVector() {
    delete [] data;
}

void MyVector::set(std::size_t index, int value) {
    data[index] = value;
}

int MyVector::get(std::size_t index) {
    return data[index];
}

std::size_t MyVector::size() {
    return sz;
}

std::size_t MyVector::capacity() {
    return cp;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= cp)
        return;
    int* tmp = new int[new_capacity];
    memcpy(tmp, data, sz * sizeof(int));
    delete [] data;
    data = tmp;
    tmp = NULL;
    cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
    if (new_size > 2 * cp)
        reserve(new_size);
    else if (new_size > cp)
        reserve(2 * cp);
    for (std::size_t i = sz; i < new_size; i++) {
        data[i] = 0;
    } 
    sz = new_size;
}

void MyVector::push_back(int value) {
    if (sz == cp) {
        reserve(2 * cp);
    }
    data[sz++] = value;
}

void MyVector::erase(std::size_t index) {
    for (std::size_t i = index; i < sz - 1; i++)
        data[i] = data[i + 1];
    sz--;
}

void MyVector::insert(std::size_t index, int value) {
    if (sz == cp) {
        reserve(2 * cp);
    }
    for (std::size_t i = sz; i > index; i--)
        data[i] = data[i - 1];
    data[index] = value;
    sz++;
}
