#include "../header/I2P2_iterator.h"

namespace I2P2 {
value_type **iterator_impl_base::get_pp_data() const { return nullptr; }
Node *iterator_impl_base::get_p_node() const { return nullptr; }
vector_iterator::vector_iterator() : pp_data(nullptr) {}
vector_iterator::vector_iterator(value_type **ppd) : pp_data(ppd) {}
iterator_impl_base *vector_iterator::clone() { return new vector_iterator(pp_data); }
reference vector_iterator::operator*() const { return **pp_data; }
pointer vector_iterator::operator->() const { return *pp_data; }
iterator_impl_base &vector_iterator::operator++() { return ++pp_data, *this; }
iterator_impl_base &vector_iterator::operator--() { return --pp_data, *this; }
iterator_impl_base &vector_iterator::operator+=(difference_type offset) { return pp_data += offset, *this; }
iterator_impl_base &vector_iterator::operator-=(difference_type offset) { return pp_data -= offset, *this; }
difference_type vector_iterator::operator-(const iterator_impl_base &rhs) const { return pp_data - rhs.get_pp_data(); }
reference vector_iterator::operator[](difference_type offset) const { return *pp_data[offset]; }
bool vector_iterator::operator==(const iterator_impl_base &rhs) const { return pp_data == rhs.get_pp_data(); }
bool vector_iterator::operator!=(const iterator_impl_base &rhs) const { return pp_data != rhs.get_pp_data(); }
bool vector_iterator::operator<(const iterator_impl_base &rhs) const { return pp_data < rhs.get_pp_data(); }
bool vector_iterator::operator>(const iterator_impl_base &rhs) const { return pp_data > rhs.get_pp_data(); }
bool vector_iterator::operator<=(const iterator_impl_base &rhs) const { return pp_data <= rhs.get_pp_data(); }
bool vector_iterator::operator>=(const iterator_impl_base &rhs) const { return pp_data >= rhs.get_pp_data(); }
value_type **vector_iterator::get_pp_data() const { return pp_data; }
list_iterator::list_iterator() : p_node(nullptr) {}
list_iterator::list_iterator(Node *pnd) : p_node(pnd) {}
iterator_impl_base *list_iterator::clone() { return new list_iterator(p_node); }
reference list_iterator::operator*() const { return *p_node->p_data; }
pointer list_iterator::operator->() const { return p_node->p_data; }
iterator_impl_base &list_iterator::operator++() { return p_node = p_node->next, *this; }
iterator_impl_base &list_iterator::operator--() { return p_node = p_node->prev, *this; }
iterator_impl_base &list_iterator::operator+=(difference_type offset) {
  for (difference_type i = 0; i < std::abs(offset); ++i) p_node = offset < 0 ? p_node->prev : p_node->next;
  return *this;
}
iterator_impl_base &list_iterator::operator-=(difference_type offset) { return operator+=(-offset); }
difference_type list_iterator::operator-(const iterator_impl_base &rhs) const {
  Node *t = p_node, *s = rhs.get_p_node();
  difference_type res = 0;
  Node *q = s;
  while (q && q != t) q = q->next, ++res;
  if (q) return res;
  res = 0;
  q = t;
  while (q && q != s) q = q->next, --res;
  return res;
}
reference list_iterator::operator[](difference_type offset) const { list_iterator lit(p_node); lit += offset; return *lit; }
bool list_iterator::operator==(const iterator_impl_base &rhs) const { return p_node == rhs.get_p_node(); }
bool list_iterator::operator!=(const iterator_impl_base &rhs) const { return p_node != rhs.get_p_node(); }
bool list_iterator::operator<(const iterator_impl_base &rhs) const {
  Node *s = p_node, *t = rhs.get_p_node();
  if (s == t) return false;
  while (s && s != t) s = s->next;
  return s == t;
}
bool list_iterator::operator>(const iterator_impl_base &rhs) const {
  Node *s = p_node, *t = rhs.get_p_node();
  if (s == t) return false;
  while (s && s != t) s = s->prev;
  return s == t;
}
bool list_iterator::operator<=(const iterator_impl_base &rhs) const {
  Node *s = p_node, *t = rhs.get_p_node();
  while (s && s != t) s = s->next;
  return s == t;
}
bool list_iterator::operator>=(const iterator_impl_base &rhs) const {
  Node *s = p_node, *t = rhs.get_p_node();
  while (s && s != t) s = s->prev;
  return s == t;
}
Node *list_iterator::get_p_node() const { return p_node; }
Node *const_iterator::get_p_node() const { return p_->get_p_node(); }
const_iterator::const_iterator() : p_(nullptr) {}
const_iterator::const_iterator(const const_iterator &rhs) : p_(rhs.p_->clone()) {}
const_iterator::const_iterator(iterator_impl_base *p) : p_(p) {}
const_iterator &const_iterator::operator=(const const_iterator &rhs) {
  if (this != &rhs) { const_iterator t(rhs); std::swap(p_, t.p_); }
  return *this;
}
const_reference const_iterator::operator*() const { return **p_; }
const_pointer const_iterator::operator->() const { return (*p_).operator->(); }
const_iterator &const_iterator::operator++() { return ++*p_, *this; }
const_iterator const_iterator::operator++(int) { const_iterator t(*this); ++*p_; return t; }
const_iterator &const_iterator::operator--() { return --*p_, *this; }
const_iterator const_iterator::operator--(int) { const_iterator t(*this); --*p_; return t; }
const_iterator &const_iterator::operator+=(difference_type offset) { return *p_ += offset, *this; }
const_iterator const_iterator::operator+(difference_type offset) const { const_iterator t(*this); *t.p_ += offset; return t; }
const_iterator &const_iterator::operator-=(difference_type offset) { return *p_ -= offset, *this; }
const_iterator const_iterator::operator-(difference_type offset) const { const_iterator t(*this); *t.p_ -= offset; return t; }
difference_type const_iterator::operator-(const const_iterator &rhs) const { return *p_ - *rhs.p_; }
const_reference const_iterator::operator[](difference_type offset) const { return (*p_)[offset]; }
bool const_iterator::operator==(const const_iterator &rhs) const { return *p_ == *rhs.p_; }
bool const_iterator::operator!=(const const_iterator &rhs) const { return *p_ != *rhs.p_; }
bool const_iterator::operator<(const const_iterator &rhs) const { return *p_ < *rhs.p_; }
bool const_iterator::operator>(const const_iterator &rhs) const { return *p_ > *rhs.p_; }
bool const_iterator::operator<=(const const_iterator &rhs) const { return *p_ <= *rhs.p_; }
bool const_iterator::operator>=(const const_iterator &rhs) const { return *p_ >= *rhs.p_; }
const_iterator::~const_iterator() { if (p_) delete p_; } iterator::iterator() {}
iterator::iterator(iterator_impl_base *p) : const_iterator(p) {}
iterator::iterator(const iterator &rhs) : const_iterator(rhs) {}
reference iterator::operator*() const { return **p_; }
pointer iterator::operator->() const { return (*p_).operator->(); }
iterator &iterator::operator++() { return ++*p_, *this; }
iterator iterator::operator++(int) { iterator t(*this); ++*p_; return t; }
iterator &iterator::operator--() { return --*p_, *this; }
iterator iterator::operator--(int) { iterator t(*this); --*p_; return t; }
iterator &iterator::operator+=(difference_type offset) { return *p_ += offset, *this; }
iterator iterator::operator+(difference_type offset) const { iterator t(*this); *t.p_ += offset; return t; }
iterator &iterator::operator-=(difference_type offset) { return *p_ -= offset, *this; }
iterator iterator::operator-(difference_type offset) const { iterator t(*this); *t.p_ -= offset; return t; }
difference_type iterator::operator-(const iterator &rhs) const { return *p_ - *rhs.p_; }
reference iterator::operator[](difference_type offset) const { return (*p_)[offset]; }
}  // namespace I2P2

