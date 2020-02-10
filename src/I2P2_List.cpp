#include "../header/I2P2_List.h"

namespace I2P2 {
List::List() : tail_(new Node), size_(0) { head_ = tail_; }
List::List(const List &rhs) : tail_(new Node), size_(0) {
  head_ = tail_;
  if (rhs.empty()) return;
  for (const_iterator it = rhs.end() - 1; ; --it) {
    push_front(*it);
    if (it == rhs.begin()) break;
  }
}
reference List::back() { return *tail_->prev->p_data; }
const_reference List::back() const { return *tail_->prev->p_data; }
iterator List::begin() { return iterator(new list_iterator(head_)); }
const_iterator List::begin() const { return const_iterator(new list_iterator(head_)); }
void List::clear() { while (!empty()) pop_back(); }
bool List::empty() const { return tail_ == head_; }
iterator List::end() { return iterator(new list_iterator(tail_)); }
const_iterator List::end() const { return const_iterator(new list_iterator(tail_)); }
void List::erase(const_iterator pos) { erase(pos, pos + 1); }
void List::erase(const_iterator begin, const_iterator end) {
  Node *b = begin.get_p_node(), *e = end.get_p_node();
  if (b == head_) {
    head_ = e;
    head_->prev = nullptr;
  } else {
    b->prev->next = e;
    e->prev = b->prev;
  }
  for (Node *t = b; t != e; ) {
    Node *q = t->next;
    delete t;
    t = q;
    --size_;
  }
}
reference List::front() { return *head_->p_data; }
const_reference List::front() const { return *head_->p_data; }
void List::insert(const_iterator pos, size_type count, const_reference val) {
  Node *t = pos.get_p_node();
  for (size_type i = 0; i < count; ++i) {
    Node *nd = new Node(new value_type(val));
    nd->prev = t->prev;
    nd->next = t;
    if (nd->prev) nd->prev->next = nd;
    nd->next->prev = nd;
    t = nd;
  }
  if (!t->prev) head_ = t;
  size_ += count;
}
void List::insert(const_iterator pos, const_iterator begin, const_iterator end) {
  size_type count = end - begin;
  if (count == 0) return;
  value_type **c = new pointer[count];
  size_type ct = 0;
  for (const_iterator it = begin; it != end; ++it) {
    c[ct++] = new value_type(*it);
  }
  Node *t = pos.get_p_node();
  for ( ; ct; --ct) {
    Node *nd = new Node(c[ct - 1]);
    nd->prev = t->prev;
    nd->next = t;
    if (nd->prev) nd->prev->next = nd;
    nd->next->prev = nd;
    t = nd;
  }
  if (!t->prev) head_ = t;
  size_ += count;
  delete[] c;
}
void List::pop_back() { erase(const_iterator(new list_iterator(tail_)) - 1); }
void List::pop_front() { erase(const_iterator(new list_iterator(head_))); }
void List::push_back(const_reference val) { insert(const_iterator(new list_iterator(tail_)), 1, val); }
void List::push_front(const_reference val) { insert(const_iterator(new list_iterator(head_)), 1, val); }
size_type List::size() const { return size_; }
List &List::operator=(const List &rhs) {
  if (this != &rhs) {
    List li(rhs);
    std::swap(head_, li.head_);
    std::swap(tail_, li.tail_);
    std::swap(size_, li.size_);
  }
  return *this;
}
List::~List() {
  for (Node *t = head_; t; ) {
    Node *q = t->next;
    delete t;
    t = q;
    q = nullptr;
  }
}
}  // namespace I2P2
