// #pragma once

#include <iostream>
#include <iterator>
using namespace std;

template <typename T>
class ForkVector {
public:
  static int init_capacity_num;  // initial capacity of the vector (default = 1)

private:
  T *data      = nullptr;            // pointer to the data
  int size     = 0;                  // num of effective elements => effective
  int capacity = init_capacity_num;  // num of allocated elements => allocated
  int current  = 0;                  // current position

public:
  ForkVector();                             // constructor
  ~ForkVector();                            // destructor
  ForkVector(const ForkVector &other);      // copy constructor
  ForkVector(ForkVector &&other) noexcept;  // move constructor

  static void set_initial_capacity(const int &num);  // set init_capacity_num

  void preAlloc(const int &n);                        // pre_allocate_capacity
  void push_back(const T &value);                     // push_back
  void pop_back();                                    // pop_back
  void clear(const int &index);                       // clear [data_only]
  void clear();                                       // clear [data_only]
  void erase(const int &index);                       // erase [data & capacity]
  void erase();                                       // erase [data & capacity]
  void shrink_to_fit();                               // shrink_to_fit
  [[nodiscard]] int GetSize() const;                  // get_size
  [[nodiscard]] int GetCapacity() const;              // get_capacity
  T *GetPtr() const;                                  // get the original ptr
  T &GetElement(const int &index);                    // get_element
  void SetElement(const int &index, const T &value);  // set_element
  int GetIndex(const T &value) const;                 // get_index
  void ResetAll(const T &value);                      // reset all elements

  T &operator[](const int &index);                     // operator []
  ForkVector &operator=(const ForkVector &other);      // copy assignment
  ForkVector &operator=(ForkVector &&other) noexcept;  // move assignment
  bool operator==(const ForkVector &other) const;
  bool operator!=(const ForkVector &other) const;

  void echo() const;  // print the vector
};
// init_capacity_num
template <typename T>
int ForkVector<T>::init_capacity_num = 1;

// set_initial_capacity
template <typename T>
void ForkVector<T>::set_initial_capacity(const int &num) {
  init_capacity_num = num;
}

// constructor
template <typename T>
ForkVector<T>::ForkVector() {
  data = new T[capacity];
}
// destructor
template <typename T>
ForkVector<T>::~ForkVector() {
  delete[] data;
}
// move constructor
template <typename T>
ForkVector<T>::ForkVector(ForkVector &&other) noexcept {
  data           = other.data;
  size           = other.size;
  capacity       = other.capacity;
  other.data     = nullptr;
  other.size     = 0;
  other.capacity = 0;
}
// copy constructor
template <typename T>
ForkVector<T>::ForkVector(const ForkVector &other) {
  if (other.capacity > capacity) {
    capacity = other.capacity;
    data     = new T[capacity];
  }
}

// pre_allocate_capacity
template <typename T>
void ForkVector<T>::preAlloc(const int &n) {
  int input = n;
  if (input < size) {
    std::cout << "Input Capacity {" << n << "} is smaller than original size {"
              << size << "}, but has been automatically reset to that "
              << "in order to avoid discarding data." << std::endl;
    input = size;
  }
  if (input > capacity) {
    capacity = input;
    T *temp  = new T[capacity];
    for (int i = 0; i < size; i++) {
      temp[i] = data[i];
    }
    delete[] data;
    data = temp;
  }
}
// push_back
template <typename T>
void ForkVector<T>::push_back(const T &value) {
  if (size == capacity) {
    preAlloc(capacity * 2);
    // preAlloc(capacity * 2) is more likely to be efficient
    // than preAlloc(capacity + 1)
    //
    // if you preAlloc(capacity + 1), then you have to preAlloc that again
    // each time you push_back
    //
    // but things will be aparently different if you preAlloc(const * capacity)
    //
    // if the const = 2, then it means you only need to preAlloc that
    // after push_back n times
  }
  data[size] = value;
  ++size;
}
// pop_back
template <typename T>
void ForkVector<T>::pop_back() {
  if (size > 0) {
    --size;
  }
}
// shrink_to_fit
template <typename T>
void ForkVector<T>::shrink_to_fit() {
  if (size < capacity) {
    capacity = size;
    T *temp  = new T[capacity];
    for (int i = 0; i < size; i++) {
      temp[i] = data[i];
    }
    delete[] data;
    data = temp;
  }
}
// get_size
template <typename T>
int ForkVector<T>::GetSize() const {
  return size;
}
// get_capacity
template <typename T>
int ForkVector<T>::GetCapacity() const {
  return capacity;
}
// get the original ptr
template <typename T>
T *ForkVector<T>::GetPtr() const {
  return data;
}
// clear [index]
template <typename T>
void ForkVector<T>::clear(const int &index) {
  if (index < 0 || index >= size) {
    return;
  }
  for (int i = index; i < size - 1; i++) {
    data[i] = data[i + 1];
  }
  --size;
}
// clear all
template <typename T>
void ForkVector<T>::clear() {
  size = 0;
}
// erase [index]
template <typename T>
void ForkVector<T>::erase(const int &index) {
  if (index < 0 || index >= size) {
    return;
  }
  for (int i = index; i < size - 1; i++) {
    data[i] = data[i + 1];
  }
  --size;
  shrink_to_fit();
}
// erase all
template <typename T>
void ForkVector<T>::erase() {
  size = 0;
  shrink_to_fit();
}
// get_element
template <typename T>
T &ForkVector<T>::GetElement(const int &index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");  // throw exception
  }
  return data[index];
}
// set_element
template <typename T>
void ForkVector<T>::SetElement(const int &index, const T &value) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");  // throw exception
  }
  data[index] = value;
}
// get_index
template <typename T>
int ForkVector<T>::GetIndex(const T &value) const {
  bool if_found = false;
  for (int i = 0; i < size; i++) {
    if (data[i] == value) {
      if_found = true;
      return i;
    }
  }
  return -1;
}
// ResetAll (with parameter)
template <typename T>
void ForkVector<T>::ResetAll(const T &value) {
  for (int i = 0; i < size; i++) {
    data[i] = value;
  }
}

// operator []
template <typename T>
T &ForkVector<T>::operator[](const int &index) {
  if (index < 0 || index >= size) {
    throw std::out_of_range("index out of range");  // throw exception
  }
  return data[index];
}
// copy assignment
template <typename T>
ForkVector<T> &ForkVector<T>::operator=(const ForkVector &other) {
  if (this == &other) {
    return *this;
  }
  if (other.capacity > capacity) {
    capacity = other.capacity;
    data     = new T[capacity];
  }
  size = other.size;
  for (int i = 0; i < size; i++) {
    data[i] = other.data[i];
  }
  return *this;
}
// move assignment
template <typename T>
ForkVector<T> &ForkVector<T>::operator=(ForkVector &&other) noexcept {
  if (this == &other) {
    return *this;
  }
  data           = other.data;
  size           = other.size;
  capacity       = other.capacity;
  other.data     = nullptr;
  other.size     = 0;
  other.capacity = 0;
  return *this;
}
// operator ==
template <typename T>
bool ForkVector<T>::operator==(const ForkVector &other) const {
  if (size != other.size) {
    return false;
  }
  for (int i = 0; i < size; i++) {
    if (data[i] != other.data[i]) {
      return false;
    }
  }
  return true;
}
// operator !=
template <typename T>
bool ForkVector<T>::operator!=(const ForkVector &other) const {
  if (size != other.size) {
    return true;
  }
  for (int i = 0; i < size; i++) {
    if (data[i] != other.data[i]) {
      return true;
    }
  }
  return false;
}

// echo
template <typename T>
void ForkVector<T>::echo() const {
  cout << "current vector: ";
  for (int i = 0; i < size; i++) {
    cout << data[i] << ", ";
  }
  cout << "\b\b  \b\b" << endl;
  cout << endl;
}
