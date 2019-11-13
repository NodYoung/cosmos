//
// Created by liyanan on 8/19/19.
//

#include <iostream>
#include <string>
#include <cxxabi.h>
#include <Variant.hpp>



void TestVariant() {
    typedef Variant<int, double, std::string, int> cv;
    cv v = 10;
    std::cout << abi::__cxa_demangle(typeid(cv::IndexType<1>).name(), nullptr, nullptr, nullptr) << std::endl;

    int i = v.indexOf<std::string>();
}


int main() {
    TestVariant();
    return 0;
}
