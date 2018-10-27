
#include <iostream>

template<class Iterator, class Printer>
void PrintRange (Iterator _first, Iterator _end)
{
	for(; _first != _end; ++_first)
	{
		Printer::Print(*_first);
	}
}
/*
template<class Printer>
void PrintRange (int* _a, size_t _s)
{
	for(size_t i=0; i<_s; ++i)
	{
		Printer::Print(_a[i]);
	}
}
*/

template<typename T =int>
struct SimplePrinter
{
	static void Print(const T& _t) {std::cout<<" "<<_t;}
	
private:
	SimplePrinter();
	~SimplePrinter();
};

template<typename T =int>
struct OneLinePrinter
{
	static void Print(const T& _t) {std::cout<<_t<<"\n";}
	
private:
	OneLinePrinter();
	~OneLinePrinter();
};



int main()
{

	int arr[] = {5,4,3,2,1};
	
	PrintRange<int*, SimplePrinter<int> >(arr,arr+sizeof(arr)/sizeof(*arr));
	
	PrintRange<int*, OneLinePrinter<int> >(arr,arr+sizeof(arr)/sizeof(*arr));

//	PrintRange<SimplePrinter<int> >(arr,sizeof(arr)/sizeof(*arr));







	return 0;
}
