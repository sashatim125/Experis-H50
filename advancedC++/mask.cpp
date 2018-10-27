

#include <iostream>
#include <iomanip>

template <class T, unsigned long N>
struct Mask
{
static const T MASK = static_cast<T>((Mask<T,N-1>::MASK << 1) | static_cast<T>(1));

private:
	Mask();
};

template <class T>
struct Mask<T,0>
{
static const T MASK = 0;

private:
	Mask();
};







int main()
{

	std::cout<<Mask<unsigned short,5>::MASK <<"\n";


	return 0;
}


