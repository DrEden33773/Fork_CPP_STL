// those who joined the queue earlier will be fetched first
// those who joined the queue later will be fetched later

#pragma once

#include <iostream>
#include <iterator>
using namespace std;

template <typename T>
class ForkQueue {
private:
  class Node {
  public:
    T data      = NULL;
    Node *front = nullptr;
    Node *back  = nullptr;
    explicit Node(const T &data) { this->data = data; }
  };
  Node *head = nullptr;
  Node *tail = nullptr;
  int size   = 0;

public:
  // constructor and destructor
  ForkQueue() = default;
  ~ForkQueue();
  ForkQueue(const ForkQueue &other);
  ForkQueue(ForkQueue &&other) noexcept;

  // functions
  void join(const T &data);  // join a node into the queue
  void quit_head();          // quit head node from the queue
  void quit_tail();          // quit tail node from the queue
  T &fetch_head();           // fetch head node from the queue
  T &fetch_tail();           // fetch tail node from the queue
  void erase();
  void clear();
  T &get_element(const int &index);                   // index counted from head
  void set_element(const int &index, const T &data);  // index counted from head
  auto data_head() -> decltype(head);                 // get the head_ptr
  auto data_tail() -> decltype(tail);                 // get the tail_ptr
  auto data_at(const int &index) -> decltype(head);   // get the data_at
  [[nodiscard]] int get_index(const T &value) const;  // get_index
  [[nodiscard]] int get_size() const;                 // get_size

  // iterator
  class iterator {
  private:
    Node *node;
    friend class ForkQueue;

  public:
    explicit iterator(Node *node) : node(node) {}
    T &operator*() { return node->data; }
    iterator &operator++() {
      node = node->front;
      return *this;
    }
    iterator &operator--() {
      node = node->back;
      return *this;
    }
    bool operator==(const iterator &other) const { return node == other.node; }
    bool operator!=(const iterator &other) const { return node != other.node; }
  };
  iterator begin() { return iterator(head); }
  const iterator &begin() const { return iterator(head); }
  iterator end() { return iterator(nullptr); }
  const iterator &end() const { return iterator(nullptr); }
  iterator &operator[](const int &index);
  const iterator &operator[](const int &index) const;
  iterator &operator=(const iterator &other);
  const iterator &operator=(const iterator &other) const;
  bool operator==(const iterator &other) const;
  bool operator!=(const iterator &other) const;

  // operator overloading
  ForkQueue &operator=(const ForkQueue &other);
  ForkQueue &operator=(ForkQueue &&other) noexcept;
  bool operator==(const ForkQueue &other) const;
  bool operator!=(const ForkQueue &other) const;

  // echo
  void echo() const;
};

// constructor and destructor
template <typename T>
ForkQueue<T>::ForkQueue(const ForkQueue &other) {
  Node *curr = other.head;
  while (curr != nullptr) {
    Node *temp = new Node(curr->data);
    if (head == nullptr) {
      head = temp;
    } else {
      tail->front = temp;
    }
    tail = temp;
    curr = curr->front;
  }
  size = other.size;
}
template <typename T>
ForkQueue<T>::~ForkQueue() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr;
    curr       = curr->front;
    delete temp;
  }
}
template <typename T>
ForkQueue<T>::ForkQueue(ForkQueue &&other) noexcept {
  head       = other.head;
  tail       = other.tail;
  size       = other.size;
  other.head = nullptr;
  other.tail = nullptr;
  other.size = 0;
}

// functions
template <typename T>
void ForkQueue<T>::join(const T &data) {
  Node *curr = new Node(data);
  if (head == nullptr) {
    head = curr;
  } else {
    tail->front = curr;
  }
  tail = curr;
  ++size;
}
template <typename T>
void ForkQueue<T>::quit_head() {
  if (size == 0) {
    return;
  }
  Node *curr  = head;
  head        = head->back;
  head->front = nullptr;
  delete curr;
  --size;
}
template <typename T>
void ForkQueue<T>::quit_tail() {
  if (size == 0) {
    return;
  }
  Node *curr = tail;
  tail       = tail->front;
  tail->back = nullptr;
  delete curr;
  --size;
}
template <typename T>
T &ForkQueue<T>::fetch_head() {
  T data = head->data;
  quit_head();
  return data;
}
template <typename T>
T &ForkQueue<T>::fetch_tail() {
  T data = tail->data;
  quit_tail();
  return data;
}
template <typename T>
void ForkQueue<T>::erase() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr;
    curr       = curr->front;
    delete temp;
  }
  head = nullptr;
  tail = nullptr;
  size = 0;
}
template <typename T>
void ForkQueue<T>::clear() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr;
    curr       = curr->front;
    delete temp;
  }
  head = nullptr;
  tail = nullptr;
  size = 0;
}
template <typename T>
T &ForkQueue<T>::get_element(const int &index) {
  if (index < 0 || index >= size) {
    return head->data;
  }
  Node *curr = head;
  for (int i = 0; i < index; ++i) {
    curr = curr->front;
  }
  return curr->data;
}
template <typename T>
void ForkQueue<T>::set_element(const int &index, const T &data) {
  if (index < 0 || index >= size) {
    return;
  }
  Node *curr = head;
  for (int i = 0; i < index; ++i) {
    curr = curr->front;
  }
  curr->data = data;
}
template <typename T>
auto ForkQueue<T>::data_head() -> decltype(head) {
  return head;
}
template <typename T>
auto ForkQueue<T>::data_tail() -> decltype(tail) {
  return tail;
}
template <typename T>
auto ForkQueue<T>::data_at(const int &index) -> decltype(head) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = head;
  for (int i = 0; i < index; ++i) {
    curr = curr->front;
  }
  return curr;
}
template <typename T>
int ForkQueue<T>::get_index(const T &value) const {
  Node *curr = head;
  int index  = 0;
  while (curr != nullptr) {
    if (curr->data == value) {
      return index;
    }
    curr = curr->front;
    ++index;
  }
  return -1;
}
template <typename T>
int ForkQueue<T>::get_size() const {
  return size;
}

// iterator
template <typename T>
auto ForkQueue<T>::operator[](const int &index) -> ForkQueue<T>::iterator & {
  return iterator(data_at(index));
}
template <typename T>
auto ForkQueue<T>::operator[](const int &index) const
    -> const ForkQueue<T>::iterator & {
  return iterator(data_at(index));
}
template <typename T>
auto ForkQueue<T>::operator=(const ForkQueue::iterator &other)
    -> ForkQueue<T>::iterator & {
  head = other.head;
  tail = other.tail;
  size = other.size;
  return *this;
}
template <typename T>
auto ForkQueue<T>::operator=(const ForkQueue::iterator &other) const
    -> const ForkQueue<T>::iterator & {
  head = other.head;
  tail = other.tail;
  size = other.size;
  return *this;
}
template <typename T>
bool ForkQueue<T>::operator==(const ForkQueue::iterator &other) const {
  return head == other.head;
}
template <typename T>
bool ForkQueue<T>::operator!=(const ForkQueue::iterator &other) const {
  return head != other.head;
}
template <typename T>
auto ForkQueue<T>::operator=(const ForkQueue &other) -> ForkQueue<T> & {
  head = other.head;
  tail = other.tail;
  size = other.size;
  return *this;
}
template <typename T>
auto ForkQueue<T>::operator=(ForkQueue &&other) noexcept -> ForkQueue<T> & {
  head       = other.head;
  tail       = other.tail;
  size       = other.size;
  other.head = nullptr;
  other.tail = nullptr;
  other.size = 0;
  return *this;
}
template <typename T>
bool ForkQueue<T>::operator==(const ForkQueue &other) const {
  return head == other.head;
}
template <typename T>
bool ForkQueue<T>::operator!=(const ForkQueue &other) const {
  return head != other.head;
}
template <typename T>
void ForkQueue<T>::echo() const {
  Node *curr = head;
  while (curr != nullptr) {
    std::cout << curr->data << ", ";
    curr = curr->front;
  }
  std::cout << "\b\b  \b\b" << std::endl;
  std::cout << std::endl;
}