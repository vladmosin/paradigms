#include "shared_ptr.h"
#include <algorithm>


shared_ptr::Storage::Storage(Matrix* mtx) :
    ref_count_(1)
{
    data_ = mtx;
}

Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ref_count_++;
}

void shared_ptr::Storage::decr() {
    ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}

bool shared_ptr::isNull() const {
    return storage_ == nullptr;
}

shared_ptr::shared_ptr(Matrix* obj) {
    if (obj)
        storage_ = new Storage(obj);
    else
        storage_ = nullptr;
}

void shared_ptr::swap(shared_ptr& other) {
    std::swap(storage_, other.storage_);
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    storage_ = other.storage_;
    if (!isNull())
        storage_->incr();
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    swap(other);
    return *this;
}

shared_ptr::~shared_ptr() {
    if (!isNull()) {
        if (storage_->getCounter() == 1)
            delete storage_;
        else
            storage_->decr();
    }
}

Matrix* shared_ptr::ptr() const {
    if (!isNull())
        return storage_->getObject();
    return 0;
}

void shared_ptr::reset(Matrix* obj) {
    *this = shared_ptr(obj);
}

Matrix* shared_ptr::operator->() const {
    return storage_->getObject();
}

Matrix& shared_ptr::operator*() const {
    return *storage_->getObject();
}
