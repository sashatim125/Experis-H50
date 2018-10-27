
#include <iostream>


unsigned int Factorial_f(unsigned int _num)
{
	unsigned int res =1;

	for(; _num; res*=(_num--))
	{}

	return res;
}

template <unsigned long N>
struct Factorial
{
static const unsigned long s_value = N * Factorial<N-1>::s_value;

private:
	Factorial();
	~Factorial();
};

template <>
struct Factorial<0>
{
static const unsigned long s_value = 1;

private:
	Factorial();
	~Factorial();
};









int main()
{
	std::cout<<"Enter number :";
	
	unsigned int n;
	
	std::cin>>n;
	
	std::cout<<"factorial of "<<n<<" is "<<Factorial_f(n)<<std::endl;
	
	
	






	return 0;
}

