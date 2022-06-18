#include <cstdio>
#include <iostream>

#include "ForkList.hpp"
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

int main() {
  // to test ForkVector
  TestForkVector();
  // to test ForkList
  TestForkList();
  cout << "End of program, press enter to exit ... " << endl;
  getchar_unlocked();
}
