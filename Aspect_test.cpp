#include <iostream>
#include <Aspect.hpp>
#include <Timer.hpp>
using namespace std;

struct TimeElapsedAspect
{
	void Before(int i)
	{
		m_lastTime = m_t.elapsed_micro();
	}

	void After(int i)
	{
		cout <<"time elapsed: "<< m_t.elapsed_micro() - m_lastTime << " ms" << endl;
	}

private:
	double m_lastTime;
	Timer m_t;
};

struct LoggingAspect
{
	void Before(int i)
	{
		std::cout <<"entering"<< std::endl;
	}

	void After(int i)
	{
		std::cout <<"leaving"<< std::endl;
	}
};

void foo(int a)
{
	cout <<"real HT function: "<<a<< endl;
}

int main()
{
	Invoke<LoggingAspect, TimeElapsedAspect>(&foo, 1); //织入方法
cout <<"-----------------------"<< endl;
	Invoke<TimeElapsedAspect, LoggingAspect>(&foo, 1);

	return 0;
}

