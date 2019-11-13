//
// Created by liyanan on 8/16/19.
//

#include <iostream>
#include <string>
#include <cxxabi.h>
#include "function_traits.hpp"

using namespace std;

template<typename T>
void PrintType() {
    std::cout << abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, nullptr) << std::endl;
}

float (*castfunc)(std::string, int);

float free_function(const std::string& a, int b) {
    return (float)a.size()/b;
}

struct AA {
    int f(int a, int b) volatile {
        return a+b;
    }
    int operator()(int) const {
        return 0;
    }
};

template<typename F>
void Visit(F&& f)
{
    using T = typename function_traits<F>::arg0_type;
}

void TestFunctionTraits() {
    std::function<int(int)> f = [](int a){return a;};
    PrintType<function_traits<std::function<int(int)> >::function_type> ();
    //PrintType<function_traits<std::function<int(int)> >::arg_type<0>> ();
    PrintType<function_traits<std::function<int(int)> >::args<0>::type> ();
    PrintType<function_traits<decltype(f)>::function_type> ();
    PrintType<function_traits<decltype(free_function)>::function_type> ();
    PrintType<function_traits<decltype(castfunc)>::function_type >();
    PrintType<function_traits<AA>::function_type >();
    using T = decltype(&AA::f);
    PrintType<T>();
    PrintType<function_traits<decltype(&AA::f)>::function_type >();
    static_assert(std::is_same<function_traits<decltype(f)>::return_type, int>::value, "");
}

int main() {
    TestFunctionTraits();
    return 0;
}