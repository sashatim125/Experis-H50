

class X
{
public:
	operator int() {return 1;}
	int operator ()() {return 2;}
	operator ()(int){return 3;}





};


int main()
{
	return 0;
}
