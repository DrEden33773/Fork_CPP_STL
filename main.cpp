#include <cstdio>
#include <iostream>

#include "ForkList.hpp"
#include "ForkQueue.hpp"
#include "ForkStack.hpp"
#include "ForkVector.hpp"

using namespace std;

void TestForkVector() {
  cout << "Test ForkVector >> " << endl;
  cout << "================================" << endl;
  ForkVector<int> forkVec;
  forkVec.push_back(1);
  forkVec.push_back(2);
  forkVec.push_back(3);
  forkVec.echo();
  cout << "size: " << forkVec.GetSize() << endl;
  cout << "capacity: " << forkVec.GetCapacity() << endl;
  forkVec.shrink_to_fit();
  cout << endl << "called shrink_to_fit" << endl;
  cout << endl;
  cout << "size: " << forkVec.GetSize() << endl;
  cout << "capacity: " << forkVec.GetCapacity() << endl;
  cout << "================================" << endl;
  cout << endl;
}

void TestForkList() {
  cout << "Test ForkList >> " << endl;
  cout << "================================" << endl;
  ForkList<int> forkList;
  forkList.push_back(1);
  forkList.push_back(2);
  forkList.push_back(3);
  forkList.echo();
  forkList.pop_back();
  forkList.pop_front();
  forkList.push_front(0);
  forkList.push_back(4);
  forkList.echo();
  cout << "================================" << endl;
  cout << endl;
}

void TestForkQueue() {
  cout << "Test ForkQueue >> " << endl;
  cout << "================================" << endl;
  ForkQueue<int> forkQueue;
  forkQueue.push(1);
  forkQueue.push(2);
  forkQueue.push(3);
  forkQueue.echo();
  forkQueue.quit_head();
  forkQueue.quit_tail();
  forkQueue.push(4);
  forkQueue.push(5);
  forkQueue.echo();
  cout << "================================" << endl;
  cout << endl;
}

void TestForkStack() {
  cout << "Test ForkStack >> " << endl;
  cout << "================================" << endl;
  ForkStack<int> forkStack;
  forkStack.push(1);
  forkStack.push(2);
  forkStack.push(3);
  forkStack.echo();
  forkStack.pop_without_return();
  forkStack.pop_without_return();
  forkStack.push(4);
  forkStack.push(5);
  forkStack.echo();
  cout << "================================" << endl;
  cout << endl;
}

// test in main() function
int main() {
  // test ForkVector
  TestForkVector();
  // test ForkList
  TestForkList();
  // test ForkQueue
  TestForkQueue();
  // test ForkStack
  TestForkStack();
  cout << "End of program, press enter to exit ... " << endl;
  getchar_unlocked();
}
