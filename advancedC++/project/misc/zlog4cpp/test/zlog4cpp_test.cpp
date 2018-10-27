
/** 
 * @brief Simple tester for zlog4cpp.
 * 
 * @author Alexander Timoshenko sashatim125@gmail.com
 * 
 * @bug Are your serious ??? 
 */ 

#include<iostream>
#include "zlog4cpp.h"

IniFileParser parser("config.txt");
const std::map<std::string, IniFileSection>& sections =
		parser.GetIniSections();

LogConfig lc((sections.find("default"))->second);

Zlog *log = new Zlog(lc);

void* MyFunc(void*)
{
	ZLOG(*log,"MyFunc",Zlog::LOG_INFO,"Hello!");
}

void* MyFunc2(void*)
{
	ZLOG(*log,"MyFunc2",Zlog::LOG_INFO,"Hello again!");
}


int main()
{

	pthread_t t1,t2, threads[100];
	
	log->Clear();

	ZLOG(*log,"Test",Zlog::LOG_INFO,"It's a test");
	
	pthread_create(&t1,0,MyFunc,0);
	pthread_create(&t2,0,MyFunc2,0);
	
	for(int i=0 ; i<100; ++i)
	{
		pthread_create(threads+i,0,MyFunc,0);
	}
	
	sleep(1);
	
	ZLOG(*log,"Test",Zlog::LOG_INFO,"It's a TEST");
	
	pthread_join(t1,0);
	pthread_join(t2,0);
	for(int i=0 ; i<100; ++i)
	{
		pthread_join(threads[i],0);
	}

	delete log;

	return 0;
}











