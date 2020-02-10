#include "../header/I2P2_Vector.h"

namespace I2P2 {
Vector::Vector() : arr_(new pointer[1]), size_(0), cap_(0) {}
Vector::Vector(const Vector &rhs) : arr_(nullptr), size_(0), cap_(0) {
  arr_ = new pointer[(size_ = cap_ = rhs.size()) + 1];
  for (size_type i = 0; i < size_; ++i) arr_[i] = new value_type(rhs[i]);
}
reference Vector::back() { return *arr_[size_ - 1]; }
const_reference Vector::back() const { return *arr_[size_ - 1]; }
iterator Vector::begin() { return iterator(new vector_iterator(arr_)); }
const_iterator Vector::begin() const { return const_iterator(new vector_iterator(arr_)); }
size_type Vector::capacity() const { return cap_; }
void Vector::clear() { while (!empty()) pop_back(); }
bool Vector::empty() const { return size_ == 0; }
iterator Vector::end() { return iterator(new vector_iterator(arr_ + size_)); }
const_iterator Vector::end() const { return const_iterator(new vector_iterator(arr_ + size_)); }
void Vector::erase(const_iterator pos) { erase(pos, pos + 1); }
void Vector::erase(const_iterator begin, const_iterator end) {
  size_type b = begin - const_iterator(new vector_iterator(arr_));
  size_type e = end - const_iterator(new vector_iterator(arr_));
  for (size_type i = b; i != e; ++i) delete arr_[i];
  for (size_type i = b; i + e - b != size_; ++i) arr_[i] = arr_[i + e - b];
  size_ -= e - b;
}
reference Vector::front() { return *arr_[0]; }
const_reference Vector::front() const { return *arr_[0]; }
void Vector::insert(const_iterator pos, size_type count, const_reference val) {
  if (count == 0) return;
  difference_type x = pos - this->begin();
  if (size_ + count > cap_) reserve(std::max(cap_ + cap_ / 2, cap_ + count));
  for (difference_type i = count + size_ - 1; i >= count + x; --i) arr_[i] = arr_[i - count];
  for (size_type i = 0; i < count; ++i) arr_[x + i] = new value_type(val);
  size_ += count;
}
void Vector::insert(const_iterator pos, const_iterator begin, const_iterator end) {
  size_type count = end - begin;
  if (count == 0) return;
  difference_type x = pos - this->begin();
  value_type **t = new pointer[count + 1];
  for (size_type i = 0; i < count; ++i) t[i] = new value_type(*(begin + i));
  if (size_ + count > cap_) reserve(std::max(cap_ + cap_ / 2, cap_ + count));
  for (difference_type i = count + size_ - 1; i >= count + x; --i) arr_[i] = arr_[i - count];
  for (size_type i = 0; i < count; ++i) arr_[x + i] = t[i];
  delete[] t;
  size_ += count;
}
void Vector::pop_back() { erase(const_iterator(new vector_iterator(arr_ + size_ - 1))); }
void Vector::pop_front() { erase(const_iterator(new vector_iterator(arr_))); }
void Vector::push_back(const_reference val) {
  if (size_ == cap_) reserve(std::max(cap_ * 2, cap_ + 1));
  arr_[size_++] = new value_type(val);
}
void Vector::push_front(const_reference val) {
  if (size_ == cap_) reserve(std::max(cap_ * 2, cap_ + 1));
  insert(const_iterator(new vector_iterator(arr_)), 1, val);
}
void Vector::reserve(size_type new_capacity) {
  if (cap_ >= new_capacity) return;
  value_type **t = new pointer[(cap_ = new_capacity) + 1];
  for (size_type i = 0; i < size_; ++i) t[i] = arr_[i];
  delete[] arr_;
  arr_ = t;
}
void Vector::shrink_to_fit() {
  value_type **t = new pointer[(cap_ = size_) + 1];
  for (size_type i = 0; i < size_; ++i) t[i] = arr_[i];
  delete[] arr_;
  arr_ = t;
}
size_type Vector::size() const { return size_; }
Vector &Vector::operator=(const Vector &rhs) {
  if (this != &rhs) {
    Vector t(rhs);
    std::swap(arr_, t.arr_);
    std::swap(size_, t.size_);
    std::swap(cap_, t.cap_);
  }
  return *this;
}
reference Vector::operator[](size_type pos) { return *arr_[pos]; }
const_reference Vector::operator[](size_type pos) const { return *arr_[pos]; }
Vector::~Vector() {
  for (size_type i = 0; i < size_; ++i) delete arr_[i];
  delete[] arr_;
}
}  // namespace I2P2

