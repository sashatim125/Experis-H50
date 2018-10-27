


#include "zlog4c.h"

/** 
 * @brief Simple tester for zlog4c.
 * 
 * @author Alexander Timoshenko sashatim125@gmail.com
 * 
 * @bug Are your serious ??? 
 */ 

void MyFunc(void)
{
	ZLOG("MyFunc",LOG_INFO,"Hello!");
}

void MyFunc2(void)
{
	ZLOG("MyFunc2",LOG_INFO,"Hello again!");
}


int main()
{

	ZlogInit("config.txt");
	
	ZLOG("Test",LOG_INFO,"It's a test");
	
	MyFunc();
	
	MyFunc2();
	
	sleep(1);
	
	ZLOG("Test",LOG_INFO,"It's a %s","TEST");

	return 0;
}











