#include "rectangle.h"
#include <cstdio>

Rectangle::Rectangle(int id, int x, int y, int width, int height) :
    Figure(id, x, y), width_(width), height_(height)
{}

Rectangle::~Rectangle() {}

void Rectangle::print() const {
    printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id_, x_, y_, width_, height_);
}

bool check_one_dimension(int from, int to, int value) {
    return (value <= to && value >= from);
}

bool Rectangle::is_inside(int x, int y) const {
    return check_one_dimension(x_ - width_ / 2, x_ + width_ / 2, x) &&
           check_one_dimension(y_ - height_ / 2, y_ + height_ / 2, y);
}

void Rectangle::zoom(int factor) {
    width_ *= factor;
    height_ *= factor;
}
