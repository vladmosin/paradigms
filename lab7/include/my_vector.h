#pragma once

#include <cstddef>

class MyVector {
public: // methods
  MyVector();
  MyVector(std::size_t init_capacity);
  ~MyVector();

  void set(std::size_t index, int value);
  int get(std::size_t index);

  std::size_t size();
  std::size_t capacity();

  void reserve(std::size_t new_capacity);
  void resize(std::size_t new_size);
  
  void push_back(int value);
  void insert(std::size_t index, int value);
  void erase(std::size_t index);
private: // fields
  std::size_t sz, cp;
  int *data;
};
