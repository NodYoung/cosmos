//
// Created by liyanan on 5/6/19.
//
#include <iostream>
#include <assert.h>
#include <string>
#include <cmath>
#include <cxxabi.h>

#include "boost/ref.hpp"

int main() {
    double x = 1.9999l;
    auto rw = boost::cref(x);
    std::cout << abi::__cxa_demangle(typeid(rw).name(), nullptr, nullptr, nullptr) << std::endl;

    auto rw2 = boost::ref(x);
    std::cout << abi::__cxa_demangle(typeid(rw2).name(), nullptr, nullptr, nullptr) << std::endl;

    std::cout << std::sqrt(boost::ref(x)) << std::endl;

    return 0;
}

