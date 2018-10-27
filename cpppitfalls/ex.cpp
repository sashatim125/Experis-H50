
#include <iostream>

struct Foo
{
	Foo(){std::cout<<"Hello ";}

	~Foo(){std::cout<<" Bye!!!\n";}

};


Foo foo;


int main()
{

std::cout<<"World";



}
