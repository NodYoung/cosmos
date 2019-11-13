#include <iostream>
#include <type_traits>
#include <functional>

int fn(int){ return int(); }
typedef int(&fn_ref)(int);
typedef int(*fn_ptr)(int);
struct fn_class
{
	int operator()(int i)
	{
		return i;
	}
};

template <typename Function>
typename std::result_of<Function()>::type call_function(Function&& f)
{
	return std::forward<Function>(f)();
}

template <typename Function, typename... Args>
typename std::result_of<Function(Args...)>::type call_function(Function&& f, Args&&... args)
{
	return std::forward<Function>(f)(std::forward<Args>(args)...);
}

int main(void)
{
	typedef std::result_of<decltype(fn)&(int)>::type A;  //int
	typedef std::result_of<fn_ref(int)>::type B;         //int
	typedef std::result_of<fn_ptr(int)>::type C;         //int
	typedef std::result_of<fn_class(int)>::type D;       //int

	std::cout << std::boolalpha;
	std::cout << "typedefs of int:" << std::endl;

	std::cout << "A: " << std::is_same<int, A>::value << std::endl;
	std::cout << "B: " << std::is_same<int, B>::value << std::endl;
	std::cout << "C: " << std::is_same<int, C>::value << std::endl;
	std::cout << "D: " << std::is_same<int, D>::value << std::endl;

	std::function<void()> f = []{std::cout << "ok0" << std::endl;};
	call_function(f);
	std::function<void(std::string)> f1 = [](std::string a){std::cout << a << std::endl;};
	call_function(f1, "f1");

  //system("pause");
	return 0;
}
