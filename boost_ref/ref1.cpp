//
// Created by liyanan on 5/6/19.
// reference: [boost------ref的使用(Boost程序库完全开发指南)读书笔记](https://blog.csdn.net/zengraoli/article/details/9663057) and [boost::ref](https://www.jianshu.com/p/ecba9cabd850)
#include <iostream>
#include <assert.h>
#include <string>

//#include "stdafx.h"
//#include "boost/utility/result_of.hpp"
//#include "boost/typeof/typeof.hpp"
//#include "boost/assign.hpp"
#include "boost/ref.hpp"

int main() {
    int x = 10;
    boost::reference_wrapper<int> rw(x);
    assert(x == rw);
    (int &)rw = 100;
    assert(x == 100);

    boost::reference_wrapper<int> rw2(rw);
    assert(rw.get() == 100);

    std::string str;
    boost::reference_wrapper<std::string> rws(str);
    *rws.get_pointer() = "hello";
    std::cout << rws.get().size() << std::endl;

    return 0;
}

