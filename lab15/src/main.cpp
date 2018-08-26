
#include "linq.h"
#include <math.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <iostream>

void example1() {
  int xs[] = { 1, 2, 3, 4, 5 };
  
  std::vector<int> res =
    from(xs, xs + 5)  // Взять элементы xs
    .select([](int x) { return x * x; })  // Возвести в квадрат
    .where_neq(25)    // Оставить только значения != 25
    .where([](int x) { return x > 3; })   // Оставить только значения > 3
    .drop(2)          // Убрать два элемента из начала
    .to_vector();     // Преобразовать результат в вектор
  std::vector<int> expected = { 16 };
  assert(res == expected);
}

void example2() {
  std::stringstream ss("1 2 3 -1 4");
  std::istream_iterator<int> in(ss), eof;
  
  std::vector<int> res =
    from(in, eof)  // Взять числа из входного потока
    .take(4)       // Не более четырёх чисел
    .until_eq(-1)  // Перестать читать после прочтения -1
    .to_vector();  // Получить список считанных чисел
  
  std::vector<int> expected = { 1, 2, 3 };
  assert(expected == res);

  int remaining;
  assert(ss >> remaining);
  assert(remaining == 4);
}

void example3() {
  int xs[] = { 1, 2, 3, 4, 5 };
  
  std::vector<double> res =
    from(xs, xs + 5)  // Взять элементы xs
    .select<double>([](int x) { return sqrt(x); })  // Извлечь корень
    .to_vector();     // Преобразовать результат в вектор
  
  assert(res.size() == 5);
  for (std::size_t i = 0; i < res.size(); i++) {
    assert(fabs(res[i] - sqrt(xs[i])) < 1e-9);
  }
}

void example4() {
  std::stringstream iss("4 16");
  std::stringstream oss;
  std::istream_iterator<int> in(iss), eof;
  std::ostream_iterator<double> out(oss, "\n");

  from(in, eof)    // Взять числа из входного потока
  .select([](int x) { return static_cast<int>(sqrt(x) + 1e-6); })  // Извлечь из каждого корень
  .copy_to(out);  // Вывести на экран
  
  assert(oss.str() == "2\n4\n");
}

class Number {
public:
  Number(int x) : x_(x) {};
  Number() : x_(0) {};
  int get() const { return x_; };
  Number(const Number& a) { x_ = a.get(); };
  Number operator=(Number a) {
    x_ = a.get(); 
    return *this;
  };
  
  int mul(int x) const { return x * x_; };
  int add(int x) const { return x + x_; };
  double db() const { return 1.5 * x_; };
private:
  int x_;
};

int foo(Number a) {
  return a.mul(3);
}

void example5() {
  Number a(2);
  std::vector<Number> xs = { Number(3), Number(7), Number(11), Number(5), Number(18), Number(13) };
  std::vector<double> res = 
    from(xs.begin(), xs.end())
    .select<int>(foo)
    .until([](int x) { return x % 2 == 0; })
    .where_neq(15)
    .select<Number>([](int x) { return Number(x * 4); })
    .where([](const Number& a) { return a.get() % 7 > 1; })
    .select<double>([](Number a) { return a.db(); })
    .to_vector();
  for (double i : res) 
    std::cout << i << '\n';
}

int main() {
  example1();
  example2();
  example3();
  example4();
  example5();
  std::cout << "SUCCESS\n";
  return 0;
}
