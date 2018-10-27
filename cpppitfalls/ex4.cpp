
#include <iostream>
const int SIZE=5;

class X
{
public:
	void foo(){std::cout<<SIZE<<"\n";};
	enum{SIZE =3};
};

int main()
{
	X x;
	x.foo();
	return 0;

}


