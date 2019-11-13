//
// Created by liyanan on 8/19/19.
//

#include <iostream>
#include <string>
#include <Any.hpp>

void TestAny() {
    Any n;
    auto r = n.IsNull();
    std::string s1="hello";
    n = s1;
    //n.AnyCast<int>();
    Any n1 = 1;
    std::cout << n1.Is<int>() << std::endl;
}

int main() {
    TestAny();
    return 0;
}