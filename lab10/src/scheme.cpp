#include "scheme.h"
#include <algorithm>

Scheme::Scheme(int capacity) :
    figures_(new Figure*[capacity])
{}

Scheme::~Scheme() {
    delete [] figures_;
}

Figure* Scheme::find_figure(int id) const{
    for (int i = 0; i < size_; i++)
        if (figures_[i]->get_id() == id)
            return figures_[i];
    return NULL;
}

void Scheme::push_back_figure(Figure *fg) {
    figures_[size_++] = fg;
}

void Scheme::remove_figure(int id) {
    int i = 0;
    bool found = false;
    while (!found and i < size_) {
        if (figures_[i]->get_id() == id) {
            delete figures_[i];
            size_--;
            found = true;
        }
    }
    for (int j = i; j < size_; j++)
        figures_[j] = figures_[j + 1];
}

void Scheme::print_all_figures() const {
    for (int i = 0; i < size_; i++)
        figures_[i]->print();
}

void Scheme::zoom_figure(int id, int factor) {
    if (find_figure(id))
        find_figure(id)->zoom(factor);
}

Figure* Scheme::is_inside_figure(int x, int y) const{
    for (int i = 0; i < size_; i++)
        if (figures_[i]->is_inside(x, y))
            return figures_[i];
    return NULL;
}

void Scheme::move(int id, int x, int y) {
    if (find_figure(id))
        find_figure(id)->move(x, y);
}
