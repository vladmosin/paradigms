#include "circle.h"
#include <cstring>
#include <cstdio>

Circle::Circle(int id, int x, int y, int radius, const char* label) :
    Figure(id, x, y), radius_(radius)
{
    label_ = new char[std::strlen(label) + 1];
    std::memcpy(label_, label, std::strlen(label) + 1);
}

Circle::~Circle() {
    delete [] label_;
}

void Circle::print() const {
    printf("Circle %d: x = %d y = %d radius = %d label = %s\n", id_, x_, y_, radius_, label_);
}

bool Circle::is_inside(int x, int y) const {
    return (x_ - x) * (x_ - x) + (y_ - y) * (y_ - y) <= radius_ * radius_; 
}

void Circle::zoom(int factor) {
    radius_ *= factor;
}
