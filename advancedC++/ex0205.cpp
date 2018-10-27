
#include <iostream>
#include <algorithm>

using std::cout;

struct PrintInt
{
	void operator()(int _i) { cout<<_i<<" ";}
};

class Sum
{
	int m_sum;
public:
	Sum(): m_sum(0) {}
	void operator()(int _i) {m_sum+=_i;}
	operator int() {return m_sum;}
};

int main()
{
	int ar[] = {5,4,3,2,1};
	
	int sum = (std::for_each(ar,ar+sizeof(ar)/sizeof(*ar),Sum()));
	
	cout<<"the sum is :"<<sum<<std::endl;
	
	return 0;
}



