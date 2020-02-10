#ifndef I2P2_ITERATOR_H
#define I2P2_ITERATOR_H
#include <iterator>
#include "I2P2_def.h"

namespace I2P2 {
struct Node {
  Node *prev, *next;
  value_type *p_data;
  ~Node() { if (p_data) delete p_data; }
  Node() : prev(nullptr), next(nullptr), p_data(nullptr) {}
  Node(value_type *pd) : prev(nullptr), next(nullptr), p_data(pd) {}
};

struct iterator_impl_base {
  virtual iterator_impl_base *clone() = 0;
  virtual reference operator*() const = 0;
  virtual reference operator[](difference_type offset) const = 0;
  virtual pointer operator->() const = 0;
  virtual difference_type operator-(const iterator_impl_base &rhs) const = 0;
  virtual iterator_impl_base &operator++() = 0;
  virtual iterator_impl_base &operator--() = 0;
  virtual iterator_impl_base &operator+=(difference_type offset) = 0;
  virtual iterator_impl_base &operator-=(difference_type offset) = 0;
  virtual bool operator==(const iterator_impl_base &rhs) const = 0;
  virtual bool operator!=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>(const iterator_impl_base &rhs) const = 0;
  virtual bool operator<=(const iterator_impl_base &rhs) const = 0;
  virtual bool operator>=(const iterator_impl_base &rhs) const = 0;
  virtual ~iterator_impl_base() = 0;

  virtual value_type **get_pp_data() const;
  virtual Node *get_p_node() const;
};

class vector_iterator : public iterator_impl_base {
 protected:
  value_type **pp_data;

 public:
  vector_iterator();
  vector_iterator(value_type **ppd);
  iterator_impl_base *clone();
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;

  value_type **get_pp_data() const;
};

class list_iterator : public iterator_impl_base {
 protected:
  Node *p_node;

 public:
  list_iterator();
  list_iterator(Node *pnd);
  iterator_impl_base *clone();
  iterator_impl_base &operator++();
  iterator_impl_base &operator--();
  iterator_impl_base &operator+=(difference_type offset);
  iterator_impl_base &operator-=(difference_type offset);
  bool operator==(const iterator_impl_base &rhs) const;
  bool operator!=(const iterator_impl_base &rhs) const;
  bool operator<(const iterator_impl_base &rhs) const;
  bool operator>(const iterator_impl_base &rhs) const;
  bool operator<=(const iterator_impl_base &rhs) const;
  bool operator>=(const iterator_impl_base &rhs) const;
  difference_type operator-(const iterator_impl_base &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;

  Node *get_p_node() const;
};

class const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::const_pointer;
  using reference = I2P2::const_reference;
  using iterator_category = std::random_access_iterator_tag;

 protected:
  iterator_impl_base *p_;

 public:
  ~const_iterator();
  const_iterator();
  const_iterator(const const_iterator &rhs);
  const_iterator(iterator_impl_base *p);
  const_iterator &operator=(const const_iterator &rhs);
  const_iterator &operator++();
  const_iterator operator++(int);
  const_iterator &operator--();
  const_iterator operator--(int);
  const_iterator &operator+=(difference_type offset);
  const_iterator operator+(difference_type offset) const;
  const_iterator &operator-=(difference_type offset);
  const_iterator operator-(difference_type offset) const;
  difference_type operator-(const const_iterator &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
  bool operator==(const const_iterator &rhs) const;
  bool operator!=(const const_iterator &rhs) const;
  bool operator<(const const_iterator &rhs) const;
  bool operator>(const const_iterator &rhs) const;
  bool operator<=(const const_iterator &rhs) const;
  bool operator>=(const const_iterator &rhs) const;
  Node *get_p_node() const;
  value_type **get_pp_data() const;
};

class iterator : public const_iterator {
 public:
  using difference_type = I2P2::difference_type;
  using value_type = I2P2::value_type;
  using pointer = I2P2::pointer;
  using reference = I2P2::reference;
  using iterator_category = std::random_access_iterator_tag;

 public:
  iterator();
  iterator(iterator_impl_base *p);
  iterator(const iterator &rhs);
  iterator &operator++();
  iterator operator++(int);
  iterator &operator--();
  iterator operator--(int);
  iterator &operator+=(difference_type offset);
  iterator operator+(difference_type offset) const;
  iterator &operator-=(difference_type offset);
  iterator operator-(difference_type offset) const;
  difference_type operator-(const iterator &rhs) const;
  pointer operator->() const;
  reference operator*() const;
  reference operator[](difference_type offset) const;
};
}  // namespace I2P2

#endif

