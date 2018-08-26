#include <iostream>

#include "my_vector.h"
#include <cstring>

class Product {
public:
    friend std::ostream& operator<<(std::ostream& out, Product& pr) {
        out << pr._name << ' ' << pr._quantity << ' ' << pr._price;
        return out;
    };
    Product();
    Product(const char* name, int quantity, double price);
    int quantity() const { return _quantity; };
    double price() const { return _price; };
    char* name() const {return _name; };
    Product(const Product& other);
    Product& operator=(Product other) {
        delete [] _name;
        _name = new char[strlen(other._name) + 1];
        strcpy(_name, other._name);
        std::swap(_quantity, other._quantity);
        std::swap(_price, other._price);
        return *this;
    };
    ~Product() { delete [] _name; };
    
private:
    char *_name;
    int _quantity;
    double _price;
};

Product::Product():
    _quantity(0),
    _price(0)
{
    _name = new char[7];
    strcpy(_name, "noname");
}

Product::Product(const char* name, int quantity, double price):
    _quantity(quantity),
    _price(price)
{
    _name = new char[strlen(name) + 1];
    strcpy(_name, name);
}

Product::Product(const Product& other):
    _quantity(other.quantity()),
    _price(other.price())
{
    _name = new char[strlen(other.name()) + 1];
    strcpy(_name, other.name());
}

template <class T>
void test_my_vector() {
    my_vector<T> vec;
    my_vector<T> vec1(vec);
    T t, u;
    vec.push_back(t);
    if (vec.size() != 1)
        std::cout << "error push_back\n";
    vec.push_back(u);
    if (vec.size() != 2)
        std::cout << "error push_back\n";
    vec.pop_back();
    if (vec.size() != 1)
        std::cout << "error pop_back\n";
    vec.clear();
    if (vec.size() != 0)
        std::cout << "error clear\n";
    vec.resize(5);
    if (vec.size() != 5)
        std::cout << "error resize\n";
    vec.reserve(10);
    if (vec.capacity() != 16)
        std::cout << "error reserve\n";
}

int main() {
    test_my_vector<int>();
    test_my_vector<Product>();
    my_vector<Product> vec;
    vec.push_back(Product("milk", 20, 37.5));
    vec.push_back(Product("lemon", 4, 72.53));
    vec.push_back(Product("cake", 123, 538.35));
    std::cout << vec;
}
