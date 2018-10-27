

#define _POSIX_C_SOURCE 199309L

#include "PeriodicExecutor.h"

#include <time.h>

#include <stdio.h>

#include "../mu_test.h"

#include "zlog4c.h"

static int userfunc1(void* _param)
{
	static int i=0;
	printf("I am uf1  and param is %d and I run %d times\n",*(int*)_param,++i);

	return 0;
}

static int userfunc2(void* _param)
{
	static int i=0;
	printf("I am uf2  and param is %d and I run %d times\n",*(int*)_param,++i);

	return 0;
}

static int userfunc3(void* _param)
{
	static int i=0;
	printf("I am uf3  and param is %d and I run %d times\n",*(int*)_param,++i);

	return 0;
}

static int pausefunc(void* _param)
{
	printf("I am pause\n");
	
	PeriodicExecutor_Pause((PeriodicExecutor*)_param);

	return 1;
}


UNIT(Start_Logger)

	ZlogInit("config.txt");

END_UNIT



UNIT(PeriodicExecutor_CreateNormal)

	PeriodicExecutor* pe;
	
	ASSERT_THAT(NULL!=(pe=PeriodicExecutor_Create("test",CLOCK_MONOTONIC)));
	
	PeriodicExecutor_Destroy(pe);
	PeriodicExecutor_Destroy(pe);
	PeriodicExecutor_Destroy(pe);

END_UNIT


UNIT(PeriodicExecutor_AddParams)

	PeriodicExecutor* pe;
	int data[]={1,2,3};
	
	ASSERT_THAT(NULL!=(pe=PeriodicExecutor_Create("test",CLOCK_MONOTONIC)));
	
	ASSERT_THAT(0!=PeriodicExecutor_Add(NULL,userfunc1,\
			data,1000));
	ASSERT_THAT(0!=PeriodicExecutor_Add(pe,NULL,\
			data,1000));
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc1,\
			NULL,1000));
	ASSERT_THAT(0!=PeriodicExecutor_Add(pe,userfunc1,\
			data,0));
	
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc1,\
			data,1000));
	
	PeriodicExecutor_Destroy(pe);

END_UNIT

UNIT(PeriodicExecutor_AddNormal)

	PeriodicExecutor* pe;
	int data[]={1,2,3};
	
	ASSERT_THAT(NULL!=(pe=PeriodicExecutor_Create("test",CLOCK_MONOTONIC)));
	
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc1,\
			data,1000));
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc2,\
			data+1,2000));
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc3,\
			data+2,3500));
	
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,pausefunc,\
			data,10000));
	
	PeriodicExecutor_Destroy(pe);

END_UNIT

UNIT(PeriodicExecutor_RunNormal)

	PeriodicExecutor* pe;
	int data[]={1,2,3};
	
	ASSERT_THAT(NULL!=(pe=PeriodicExecutor_Create("test",CLOCK_MONOTONIC)));
	
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc1,\
			data,500));
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc2,\
			data+1,1000));
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,userfunc3,\
			data+2,2000));
			
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,pausefunc,\
			pe,2100));
			
	ASSERT_THAT(0==PeriodicExecutor_Run(NULL));
	
	ASSERT_THAT(3==PeriodicExecutor_Run(pe));
	
	ASSERT_THAT(0==PeriodicExecutor_Add(pe,pausefunc,\
			pe,2000));
	
	ASSERT_THAT(3==PeriodicExecutor_Run(pe));
	
	PeriodicExecutor_Destroy(pe);

END_UNIT

TEST_SUITE(PeriodicExecutorTests)

	TEST(Start_Logger)

	TEST(PeriodicExecutor_CreateNormal)

	TEST(PeriodicExecutor_AddParams)
	TEST(PeriodicExecutor_AddNormal)

	TEST(PeriodicExecutor_RunNormal)


END_SUITE











