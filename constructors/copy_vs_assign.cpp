//
// Created by liyanan on 7/28/20.
//

#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

struct A
{
    int n;
    std::string s1;
    A() : n(0), s1("") {
      std::cout << "constructor" << std::endl;
    }
    A(const A& a) : n(a.n), s1(a.s1) {
      std::cout << "copy" << std::endl;
    }
    // user-defined copy assignment, copy-and-swap form
    A& operator=(A other)
    {
      std::cout << "assignment" << std::endl;
      std::swap(n, other.n);
      std::swap(s1, other.s1);
      return *this;
    }
};

int main() {
  A b;
  b = A();
  return 0;
}