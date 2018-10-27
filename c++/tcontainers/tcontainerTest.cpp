


#include <iostream>
#include <vector>
#include <list>

//#include "tcontainer1.h"
#include "tcontainer2.h"

using namespace std; 

int main()
{
//	TContainer_t<int,vector> arr;	
//	TContainer_t<signed char,list> lst;

	TContainer_t<int,vector<int*> > arr;	
	TContainer_t<signed char,list<signed char*> > lst;
	
	int* nPtr;
	
	nPtr = new int;
	*nPtr = 5;
	arr.Insert(nPtr);
	
	nPtr = new int;
	*nPtr = 10;
	arr.Insert(nPtr);
	
	cout<<"first is "<<*(arr.GetFirst()) << " last is "<<*(arr.GetLast())<<endl;
	
	cout<<"arr[0] is "<<*(arr[0]) << "and arr[1] is "<<*(arr[1])<<endl;
	
	signed char* cPtr;

	cPtr = new signed char;
	*cPtr = 25;
	lst.Insert(cPtr);
	
	cPtr = new signed char;
	*cPtr = 45;
	lst.Insert(cPtr);
	
	cout<<"first is "<<(int)*(lst.GetFirst()) << " last is "<<(int)*(lst.GetLast())<<endl;
	
	cout<<"list[0] is "<<(int)*(lst[0]) << " and list[1] is "<<(int)*(lst[1])<<endl;







	return 0;
}








