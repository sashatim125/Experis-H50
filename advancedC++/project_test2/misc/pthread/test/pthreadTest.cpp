
#include "pthread_class.h"

#include <iostream>
#include <unistd.h>

class Test1
:	public Runnable
{
public:
	void Run()
	{
		for (int i=0;i<5;++i)
		{
			std::cout<<"Hello World from Test1!"<<std::endl;
			sleep(1);
		}
	}
};

class Test2
:	public Runnable
{
public:
	void Run()
	{
		for (int i=0;i<5;++i)
		{
			std::cout<<"Hello World from Test2!"<<std::endl;
			sleep(1);
		}
	}
};





int main()
{

	Test1* test1 = new Test1;
	Test2* test2 = new Test2;
	
	
	PThread thread1(Runnable_sp(test1),"test1");
	PThread thread2(Runnable_sp(test2),"test2");


	thread1.Start();
	sleep(2);
	thread2.Start();
	sleep(2);
	
	std::cout<<thread1.GetName()<<std::endl;
	std::cout<<thread2.GetName()<<std::endl;
	
	thread2.Cancel();
	sleep(2);
	thread2.Start();
	
	thread1.Join();
	thread2.Join();




	return 0;
}



