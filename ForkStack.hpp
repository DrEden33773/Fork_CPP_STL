// first in, last out
// last in, first out

/*
 *  [surface] <-(upper)- [node] -(lower)-> [bottom]
 */

// #pragma once

#include <iostream>
#include <iterator>
using namespace std;

template <typename T>
class ForkStack {
private:
  class Node {
  public:
    T data;
    Node *upper = nullptr;
    Node *lower = nullptr;
    explicit Node(const int &data) { this->data = data; }
  };
  Node *bottom  = nullptr;
  Node *surface = nullptr;
  int size      = 0;

public:
  // constructor and destructor
  ForkStack() = default;
  ~ForkStack();
  ForkStack(const ForkStack &other);
  ForkStack(ForkStack &&other) noexcept;

  // operational functions
  void push(const T &data);       // push a value into the stack
  [[nodiscard]] T &pop();         // remove the surface node then return value
  void pop_without_return();      // remove the surface node
  [[nodiscard]] T &return_top();  // show the top of the stack
  void erase();                   // empty the stack, release all nodes
  void clear();                   // = erase()
  [[nodiscard]] T &get_element(const int &index);
  void set_element(const int &index, const T &data);
  [[nodiscard]] int get_index(const T &value) const;
  [[nodiscard]] int get_size() const;
  void echo();

  // iterator
  class iterator {
  private:
    Node *node;
    friend class ForkStack;

  public:
    explicit iterator(Node *node) : node(node) {}
    T &operator*() { return node->data; }
    iterator &operator++() {
      node = node->lower;
      return *this;
    }
    iterator &operator--() {
      node = node->upper;
      return *this;
    }
  };

  // iterator functions
  iterator begin() { return iterator(surface); }
  iterator end() { return iterator(bottom); }
  iterator rbegin() { return iterator(bottom); }
  iterator rend() { return iterator(surface); }

  // operator overloading
  ForkStack &operator=(const ForkStack &other);
  ForkStack &operator=(ForkStack &&other) noexcept;
  bool operator==(const ForkStack &other) const;
  bool operator!=(const ForkStack &other) const;
  T &operator[](const int &index);
  const T &operator[](const int &index) const;
  iterator &operator      =(const iterator &other);
  const iterator &operator=(const iterator &other) const;
  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;
};

// constructor and destructor
template <typename T>
ForkStack<T>::~ForkStack() {
  Node *curr = surface;
  while (curr != nullptr) {
    Node *temp = curr;
    curr       = curr->lower;
    delete temp;
  }
}
template <typename T>
ForkStack<T>::ForkStack(const ForkStack &other) {
  Node *curr = other.surface;
  while (curr != nullptr) {
    push(curr->data);
    curr = curr->lower;
  }
}
template <typename T>
ForkStack<T>::ForkStack(ForkStack &&other) noexcept {
  surface       = other.surface;
  bottom        = other.bottom;
  size          = other.size;
  other.surface = nullptr;
  other.bottom  = nullptr;
  other.size    = 0;
}

// operational functions
template <typename T>
void ForkStack<T>::push(const T &data) {
  Node *new_node = new Node(data);
  if (surface == nullptr) {
    surface = new_node;
    bottom  = new_node;
  } else {
    new_node->lower = surface;
    surface->upper  = new_node;
    surface         = new_node;
  }
  size++;
}
template <typename T>
T &ForkStack<T>::pop() {
  if (surface == nullptr) {
    throw std::out_of_range("stack is empty");
  }
  Node *temp = surface;
  surface    = surface->lower;
  if (surface != nullptr) {
    surface->upper = nullptr;
  }
  delete temp;
  size--;
  return surface->data;
}
template <typename T>
T &ForkStack<T>::return_top() {
  if (surface == nullptr) {
    throw std::out_of_range("stack is empty");
  }
  return surface->data;
}
template <typename T>
void ForkStack<T>::erase() {
  Node *curr = surface;
  while (curr != nullptr) {
    Node *temp = curr;
    curr       = curr->lower;
    delete temp;
  }
  surface = nullptr;
  bottom  = nullptr;
  size    = 0;
}
template <typename T>
void ForkStack<T>::clear() {
  erase();
}
template <typename T>
T &ForkStack<T>::get_element(const int &index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = surface;
  for (int i = 0; i < index; i++) {
    curr = curr->lower;
  }
  return curr->data;
}
template <typename T>
void ForkStack<T>::set_element(const int &index, const T &data) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = surface;
  for (int i = 0; i < index; i++) {
    curr = curr->lower;
  }
  curr->data = data;
}
template <typename T>
int ForkStack<T>::get_index(const T &value) const {
  Node *curr = surface;
  int index  = 0;
  while (curr != nullptr) {
    if (curr->data == value) {
      return index;
    }
    curr = curr->lower;
    index++;
  }
  return -1;
}
template <typename T>
int ForkStack<T>::get_size() const {
  return size;
}

// operator overloading
template <typename T>
ForkStack<T> &ForkStack<T>::operator=(const ForkStack &other) {
  if (this == &other) {
    return *this;
  }
  erase();
  Node *curr = other.surface;
  while (curr != nullptr) {
    push(curr->data);
    curr = curr->lower;
  }
  return *this;
}
template <typename T>
ForkStack<T> &ForkStack<T>::operator=(ForkStack &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  surface       = other.surface;
  bottom        = other.bottom;
  size          = other.size;
  other.surface = nullptr;
  other.bottom  = nullptr;
  other.size    = 0;
  return *this;
}
template <typename T>
bool ForkStack<T>::operator==(const ForkStack &other) const {
  if (size != other.size) {
    return false;
  }
  Node *curr  = surface;
  Node *curr2 = other.surface;
  while (curr != nullptr) {
    if (curr->data != curr2->data) {
      return false;
    }
    curr  = curr->lower;
    curr2 = curr2->lower;
  }
  return true;
}
template <typename T>
bool ForkStack<T>::operator!=(const ForkStack &other) const {
  return !(*this == other);
}
template <typename T>
T &ForkStack<T>::operator[](const int &index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = surface;
  for (int i = 0; i < index; i++) {
    curr = curr->lower;
  }
  return curr->data;
}
template <typename T>
const T &ForkStack<T>::operator[](const int &index) const {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = surface;
  for (int i = 0; i < index; i++) {
    curr = curr->lower;
  }
  return curr->data;
}
template <typename T>
typename ForkStack<T>::iterator &ForkStack<T>::operator=(
    const ForkStack::iterator &other) {
  if (this == &other) {
    return *this;
  }
  surface = other.surface;
  return *this;
}
template <typename T>
const typename ForkStack<T>::iterator &ForkStack<T>::operator=(
    const ForkStack::iterator &other) const {
  if (this == &other) {
    return *this;
  }
  surface = other.surface;
  return *this;
}
template <typename T>
bool ForkStack<T>::operator==(const ForkStack::iterator &other) const {
  return surface == other.surface;
}
template <typename T>
bool ForkStack<T>::operator!=(const ForkStack::iterator &other) const {
  return surface != other.surface;
}
template <typename T>
void ForkStack<T>::echo() {
  Node *curr = surface;
  while (curr != nullptr) {
    std::cout << curr->data << ", ";
    curr = curr->lower;
  }
  std::cout << "\b\b  \b\b" << std::endl;
  std::cout << std::endl;
}

// added functions
template <typename T>
void ForkStack<T>::pop_without_return() {
  if (surface == nullptr) {
    throw std::out_of_range("stack is empty");
  }
  Node *temp = surface;
  surface    = surface->lower;
  delete temp;
  size--;
}
