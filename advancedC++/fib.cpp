

#include <iostream>

template <unsigned long N>
struct Fibonacci
{
static const unsigned long FIB = Fibonacci<N-1>::FIB + Fibonacci<N-2>::FIB;

private:
	Fibonacci();
};

template <>
struct Fibonacci<0>
{
static const unsigned long FIB = 1;

private:
	Fibonacci();
};

template <>
struct Fibonacci<1>
{
static const unsigned long FIB = 1;

private:
	Fibonacci();
};







int main()
{

	std::cout<<"Fib("<<900<<")="<<Fibonacci<900>::FIB<<"\n";	


	return 0;
}


