// #pragma once

#include <iostream>
#include <iterator>

using namespace std;

template <typename T>
class ForkList {
private:
  class Node {
  public:
    T data;
    Node *next = nullptr;
    Node *prev = nullptr;
  };
  [[maybe_unused]] Node *head  = nullptr;  // head of the list
  [[maybe_unused]] Node *tail  = nullptr;  // tail of the list
  int size                     = 0;        // size of the list
  [[maybe_unused]] int current = 0;        // current position in the list

public:
  ForkList() = default;                 // constructor
  ~ForkList();                          // destructor
  ForkList(const ForkList &other);      // copy constructor
  ForkList(ForkList &&other) noexcept;  // move constructor

  void push_back(const T &value);                     // push_back
  void pop_back();                                    // pop_back
  void push_front(const T &value);                    // push_front
  void pop_front();                                   // pop_front
  void erase();                                       // erase all
  void erase(const int &index);                       // erase index
  void clear();                                       // clear all
  void clear(const int &index);                       // clear index
  void ResetAll(const T &value);                      // reset all
  void echo() const;                                  // print the list
  void GetElement(const int &index);                  // get_element
  void SetElement(const int &index, const T &value);  // set_element
  auto data_head() -> decltype(head);                 // get the head_ptr
  auto data_tail() -> decltype(tail);                 // get the tail_ptr
  auto data_at(const int &index) -> decltype(head);   // get the data_at
  [[nodiscard]] int GetIndex(const T &value) const;   // get_index
  [[nodiscard]] int GetSize() const;                  // get_size

  T &operator[](const int &index);                 // operator []
  ForkList &operator=(const ForkList &other);      // copy assignment
  ForkList &operator=(ForkList &&other) noexcept;  // move assignment
  bool operator==(const ForkList &other) const;
  bool operator!=(const ForkList &other) const;
};

template <typename T>
ForkList<T>::~ForkList() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr;
    curr       = curr->next;
    delete temp;
  }
}
template <typename T>
ForkList<T>::ForkList(const ForkList &other) {
  Node *curr = other.head;
  while (curr != nullptr) {
    push_back(curr->data);
    curr = curr->next;
  }
}
template <typename T>
ForkList<T>::ForkList(ForkList &&other) noexcept {
  head          = other.head;
  tail          = other.tail;
  size          = other.size;
  current       = other.current;
  other.head    = nullptr;
  other.tail    = nullptr;
  other.size    = 0;
  other.current = 0;
}

template <typename T>
void ForkList<T>::push_back(const T &value) {
  Node *curr = new Node;
  curr->data = value;
  if (!head) {
    head = curr;
    tail = curr;
  } else {
    tail->next = curr;
    curr->prev = tail;
    tail       = curr;
  }
  ++size;
}
template <typename T>
void ForkList<T>::pop_back() {
  if (size == 0) {
    return;
  }
  Node *curr = tail;
  tail       = tail->prev;
  tail->next = nullptr;
  delete curr;
  --size;
}
template <typename T>
void ForkList<T>::push_front(const T &value) {
  Node *curr = new Node;
  curr->data = value;
  curr->next = head;
  curr->prev = nullptr;
  if (head != nullptr) {
    head->prev = curr;
  }
  head = curr;
  if (tail == nullptr) {
    tail = head;
  }
  ++size;
}
template <typename T>
void ForkList<T>::pop_front() {
  if (size == 0) {
    return;
  }
  Node *curr = head;
  head       = head->next;
  head->prev = nullptr;
  delete curr;
  --size;
}
template <typename T>
int ForkList<T>::GetSize() const {
  return size;
}
template <typename T>
void ForkList<T>::erase() {
  Node *curr = head;
  while (curr != nullptr) {
    Node *temp = curr;
    curr       = curr->next;
    delete temp;
  }
  head = nullptr;
  tail = nullptr;
  size = 0;
}
template <typename T>
void ForkList<T>::erase(const int &index) {
  if (index < 0 || index >= size) {
    return;
  }
  if (index == 0) {
    pop_front();
    return;
  }
  if (index == size - 1) {
    pop_back();
    return;
  }
  Node *curr = head;
  for (int i = 0; i < index - 1; ++i) {
    curr = curr->next;
  }
  Node *temp       = curr->next;
  curr->next       = curr->next->next;
  curr->next->prev = curr;
  delete temp;
  --size;
}
template <typename T>
void ForkList<T>::clear() {
  erase();
}
template <typename T>
void ForkList<T>::clear(const int &index) {
  erase(index);
}
template <typename T>
void ForkList<T>::ResetAll(const T &value) {
  Node *curr = head;
  while (curr != nullptr) {
    curr->data = value;
    curr       = curr->next;
  }
}
template <typename T>
void ForkList<T>::echo() const {
  cout << "current list: ";
  Node *curr = head;
  while (curr != nullptr) {
    cout << curr->data << ", ";
    curr = curr->next;
  }
  cout << "\b\b  \b\b" << endl;
  cout << endl;
}
template <typename T>
[[maybe_unused]] void ForkList<T>::GetElement(const int &index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = head;
  for (int i = 0; i < index; ++i) {
    curr = curr->next;
  }
  cout << "element " << index << ": " << curr->data << endl;
}
template <typename T>
void ForkList<T>::SetElement(const int &index, const T &value) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = head;
  for (int i = 0; i < index; ++i) {
    curr = curr->next;
  }
  curr->data = value;
}
template <typename T>
int ForkList<T>::GetIndex(const T &value) const {
  Node *curr = head;
  int index  = 0;
  while (curr != nullptr) {
    if (curr->data == value) {
      return index;
    }
    curr = curr->next;
    ++index;
  }
  return -1;
}
template <typename T>
auto ForkList<T>::data_head() -> decltype(head) {
  if (head == nullptr) {
    return nullptr;
  }
  return head;
}
template <typename T>
auto ForkList<T>::data_tail() -> decltype(tail) {
  if (tail == nullptr) {
    return nullptr;
  }
  return tail;
}
template <typename T>
auto ForkList<T>::data_at(const int &index) -> decltype(head) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = head;
  for (int i = 0; i < index; ++i) {
    curr = curr->next;
  }
  return curr;
}

template <typename T>
T &ForkList<T>::operator[](const int &index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");
  }
  Node *curr = head;
  for (int i = 0; i < index; ++i) {
    curr = curr->next;
  }
  return curr->data;
}
template <typename T>
ForkList<T> &ForkList<T>::operator=(const ForkList &other) {
  if (this == &other) {
    return *this;
  }
  erase();
  Node *curr = other.head;
  while (curr != nullptr) {
    push_back(curr->data);
    curr = curr->next;
  }
  return *this;
}
template <typename T>
ForkList<T> &ForkList<T>::operator=(ForkList &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  erase();
  head          = other.head;
  tail          = other.tail;
  size          = other.size;
  current       = other.current;
  other.head    = nullptr;
  other.tail    = nullptr;
  other.size    = 0;
  other.current = 0;
  return *this;
}
template <typename T>
bool ForkList<T>::operator==(const ForkList &other) const {
  if (size != other.size) {
    return false;
  }
  Node *curr       = head;
  Node *other_curr = other.head;
  while (curr != nullptr) {
    if (curr->data != other_curr->data) {
      return false;
    }
    curr       = curr->next;
    other_curr = other_curr->next;
  }
  return true;
}
template <typename T>
bool ForkList<T>::operator!=(const ForkList &other) const {
  if (size != other.size) {
    return false;
  }
  Node *curr       = head;
  Node *other_curr = other.head;
  while (curr != nullptr) {
    if (curr->data != other_curr->data) {
      return true;
    }
    curr       = curr->next;
    other_curr = other_curr->next;
  }
  return false;
}
