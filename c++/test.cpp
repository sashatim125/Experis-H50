
#include <iostream>
#include <iomanip>
using namespace std;

class X
{
	public:
	X() : val() {}
	X(int i):val(i){}
	
	private:
	int val;
};



class Y
{
	public:
	
	int y1;
	static int y2;
	double y3;
};


int main()
{/*
	int& i[] = new int&[50];
	
	int j;
	
	int*& k = &j;
*/

	X x;
	
	Y y={1,2.3};
	
	cout<<setw(5)<<left<<y.y1/*<<Y::y2*/<<y.y3<<endl;

	return 0;
}
