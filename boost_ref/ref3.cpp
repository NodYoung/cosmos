//
// Created by liyanan on 5/6/19.
//

#include <iostream>
#include <assert.h>
#include <string>
#include <cmath>
#include <vector>
#include <set>
#include <cxxabi.h>

#include "boost/ref.hpp"
#include "boost/typeof/typeof.hpp"

int main() {
    std::vector<int> v(10, 2);
    auto rw = boost::cref(v);
    assert(!boost::is_reference_wrapper<BOOST_TYPEOF(v)>::value);

    std::string str;
    auto rws = boost::ref(str);
    std::cout << abi::__cxa_demangle(typeid(boost::unwrap_reference<BOOST_TYPEOF(rws)>::type).name(), nullptr, nullptr, nullptr) << std::endl;
    std::cout << abi::__cxa_demangle(typeid(boost::unwrap_reference<BOOST_TYPEOF(str)>::type).name(), nullptr, nullptr, nullptr) << std::endl;

    std::set<int> st;
    auto rs = boost::ref(st);
    boost::unwrap_ref(rs).insert(12);

    std::string strr("hello");
    auto rst = boost::cref(strr);
    std::cout << abi::__cxa_demangle(typeid(boost::unwrap_ref(rst)).name(), nullptr, nullptr, nullptr) << std::endl;

    return 0;
}