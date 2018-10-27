

#include "tException_t.h"

#include <iostream>


using namespace std;


void foo() 
{
	THROW(int,5,"The exception description");
}


int main()
{


	try
	{
		foo();
	}
	catch (TException_t<int> &_ex)
	{
		cout<<"The object is :"<<_ex.GetExObj()<<",\n";
		cout<<"The description is :"<<_ex.GetDesc()<<",\n";
		cout<<"The file name is :"<<_ex.GetFilename()<<",\n";
		cout<<"The line number is :"<<_ex.GetLine()<<endl;
	
	}

	return 0;
}














