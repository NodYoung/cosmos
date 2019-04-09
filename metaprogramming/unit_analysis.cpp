//
// Created by liyanan12 on 19-4-8.
// reference: [C++模板元编程--量纲分析](https://zhuanlan.zhihu.com/p/24680151)
//
#include <iostream>
#include <typeinfo>
#include <cxxabi.h>

using namespace std;

namespace tymeta {
    template <class T, T ...Args>
    struct tyVector{
        typedef tyVector<T, Args...> type;
    };

    typedef tyVector<int, 1, 0, 0, 0, 0, 0, 0> mass;
    typedef tyVector<int, 0, 1, 0, 0, 0, 0, 0> length;
    typedef tyVector<int, 0, 0, 1, 0, 0, 0, 0> time;
    typedef tyVector<int, 0, 0, 0, 1, 0, 0, 0> charge;
    typedef tyVector<int, 0, 0, 0, 0, 1, 0, 0> temperature;
    typedef tyVector<int, 0, 0, 0, 0, 0, 1, 0> intensity;
    typedef tyVector<int, 0, 0, 0, 0, 0, 0, 1> amount_of_substance;

    template <class T1, class T2, class bop>
    struct tyTransform {};

    template <
            template <class Tv, Tv ...Args1> class T1,
            template <class Tv, Tv ...Args2> class T2,
            class Tv,
            Tv ...Args1,
            Tv ...Args2,
            class bop>
    struct tyTransform<T1<Tv, Args1...>, T2<Tv, Args2...>, bop> {
        typedef tyVector<Tv, bop::template apply<Tv, Args1, Args2>::value...> type;
    };

    template <class Tv, Tv v1, Tv v2>
    struct tyPlus_impl {
        typedef tyPlus_impl<Tv, v1, v2> type;
        const static Tv value = v1 + v2;
    };
    struct tyPlus {
        template <class Tv, Tv v1, Tv v2>
        struct apply : tyPlus_impl<Tv, v1, v2> {};
    };

    template <class Tv, Tv v1, Tv v2>
    struct tyMinus_impl {
        typedef tyPlus_impl<Tv, v1, v2> type;
        const static Tv value = v1 - v2;
    };
    struct tyMinus {
        template <class Tv, Tv v1, Tv v2>
        struct apply : tyMinus_impl<Tv, v1, v2> {};
    };

    template <class T, class Dimensions>
    struct quantity {
        explicit quantity(T x) : m_value(x) {}
        T value() const {return m_value;}
    private:
        T m_value;
    };

    template <class T, class D>
    quantity<T, D> operator+(const quantity<T, D>& x, const quantity<T, D>& y) {
        return quantity<T, D>(x.value() + y.value());
    };

    template <class T, class D>
    quantity<T, D> operator-(const quantity<T, D>& x, const quantity<T, D>& y) {
        return quantity<T, D>(x.value() - y.value());
    };

    template <class T, class D1, class D2>
    quantity<T, typename tyTransform<D1, D2, tyPlus>::type> operator* (const quantity<T, D1>& x, const quantity<T, D2>& y) {
        typedef typename tyTransform<D1, D2, tyPlus>::type dim;
        return quantity<T, dim>(x.value() * y.value());
    };

    template<class T, class D1, class D2>
    quantity<T, typename tyTransform<D1, D2, tyMinus>::type> operator/ (const quantity<T, D1>& x, const quantity<T, D2>& y) {
        typedef typename tyTransform<D1, D2, tyMinus>::type dim;
        return quantity<T, dim>(x.value() / y.value());
    };
}

int main() {
    tymeta::quantity<float, tymeta::length> len1(10.23);
    tymeta::quantity<float, tymeta::length> len2(5);
    cout << (len1 + len2).value() << endl;

    tymeta::quantity<float, tymeta::length> len3(10.23);
    tymeta::quantity<float, tymeta::mass> len4(5);
    //cout << (len3 + len4).value() << endl;     // error

    tymeta::quantity<float, tymeta::length> len5(10.23);
    tymeta::quantity<float, tymeta::time> tm(5);
    cout << (len1 / tm).value() << endl
         << abi::__cxa_demangle(typeid(len1 / tm).name(), nullptr, nullptr, nullptr) << endl;  //abi::__cxa_demangle is used for readability of typeid

    tymeta::quantity<float, tymeta::time> tm2(5);
    tymeta::quantity<float, tymeta::time> tm3(10);
    auto speed = len1 / tm2;
    auto a_speed = speed / tm2; //加速度
    auto speed2 = a_speed * tm3;
    cout << (speed + speed2).value() << endl;
    auto scalar = tm3 / tm2;
    cout << typeid(scalar).name() << endl;

    return 0;
}