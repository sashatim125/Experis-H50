
#include "sharedPtr.h"
#include <iostream>
#include <vector>


using namespace advcpp;

struct MyClass
{
	int m_num;
	
	MyClass() {std::cout<<"MyClass ctor called \n";}
	
	virtual void Print() {std::cout<<"MyClass "<<m_num;}
	
	virtual ~MyClass() {std::cout<<"MyClass dtor called \n";}

};

struct MyNextClass: public MyClass
{
	
	MyNextClass() {std::cout<<"MyNextClass ctor called \n";}
	
	virtual void Print() {std::cout<<"MyNextClass "<<m_num;}
	
	virtual ~MyNextClass() {std::cout<<"MyNextClass dtor called \n";}

};

int main()
{

	SharedPtr<MyClass> sp1( new MyClass);
	
	
	if(sp1)
	{
		std::cout<<"sp1 isn't null\n";
	}
	
	SharedPtr<MyClass> sp5;
	
	if(!sp5)
	{
		std::cout<<"sp5 is null\n";
	}
	
	std::cout<<"Ref count = "<<sp1.GetRefCount()<<"\n";
	
	sp1->m_num  = 5;

	sp1->Print();
	std::cout<<" "<<sp1->m_num<<"\n";
	
	(*sp1).Print();
	std::cout<<" "<<(*sp1).m_num<<"\n";
	
	std::cout<<std::endl;
	{	
		SharedPtr<MyClass> sp2 = sp1;
		std::cout<<"Ref count = "<<sp1.GetRefCount()<<"\n";
		std::cout<<"Ref count = "<<sp2.GetRefCount()<<"\n";
		
		std::cout<< (sp1 == sp2 ? "OK" :"NOT OK")<<"\n";
		
		sp1->Print();
		std::cout<<std::endl;
		
	}
	std::cout<<"Ref count = "<<sp1.GetRefCount()<<"\n";
	
	std::vector<SharedPtr<MyClass>* > v;
	
	for(size_t i = 0; i<150; ++i)
	{
		v.push_back(new SharedPtr<MyClass>(sp1));
		std::cout<<"Ref count = "<<sp1.GetRefCount()<<"\n";
	}
	
	
	for(size_t i = 0; i<150; ++i)
	{
		delete v[i];
		std::cout<<"Ref count = "<<sp1.GetRefCount()<<"\n";
	}

	std::cout<<"Ref count = "<<sp1.GetRefCount()<<"\n";
	{
		SharedPtr<MyClass> sp2 (new MyNextClass());
		sp2->Print();
		std::cout<<"\n";
	}
/*	{
		SharedPtr<MyClass> sp3 (new int);
		sp3->Print();
		std::cout<<"\n";
	}
*/
	{
		SharedPtr<MyNextClass> sp3(new MyNextClass());
		SharedPtr<MyClass> sp4(sp3);
		
		sp4->Print();
		std::cout<<"\n";
	}
	
	{
		SharedPtr<MyNextClass> sp3(new MyNextClass());
		SharedPtr<MyClass> sp4;
		sp4 = sp3;
		
		sp4->Print();
		std::cout<<"\n";
	}
	


	return 0;
}
