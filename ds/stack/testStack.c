/*This file contains the main=test for stack.h API.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#include "stack.h"
#include "../mu_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

UNIT(StackCreateTest)
	
	Stack *st;
	
	ASSERT_THAT((st=StackCreate(10,10))!=NULL);
	StackDestroy(st);
	
	ASSERT_THAT((st=StackCreate(0,0))==NULL);
	
	ASSERT_THAT((st=StackCreate(1,0))!=NULL);
	StackDestroy(st);
	
	ASSERT_THAT((st=StackCreate(0,1))!=NULL);
	StackDestroy(st);
	
	ASSERT_THAT((st=StackCreate(ULONG_MAX,1))==NULL);
		
END_UNIT

UNIT(StackPushTest_Params)
	
	Stack *st;

	ASSERT_THAT(StackPush(NULL,1)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((st=StackCreate(0,ULONG_MAX))!=NULL);
	ASSERT_THAT(StackPush(st,1)==ERR_REALLOCATION_FAILED);
	
	StackDestroy(st);	
	
	ASSERT_THAT((st=StackCreate(1,0))!=NULL);
	ASSERT_THAT((StackPush(st,1)==ERR_OK)&&(StackPush(st,2)==ERR_OVERFLOW));
	
	StackDestroy(st);

END_UNIT

UNIT(StackPushTest_Normal)
	
	Stack *st;
	int i;	
	
	ASSERT_THAT((st=StackCreate(1,1))!=NULL);
	
	ASSERT_THAT(StackPush(st,5)==ERR_OK);
	
	ASSERT_THAT(StackPush(st,10)!=ERR_REALLOCATION_FAILED);	
	
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(StackPush(st,i)!=ERR_REALLOCATION_FAILED);		
	}
	StackDestroy(st);
END_UNIT


UNIT(StackIsEmptyTest)
	
	Stack *st;
	int i,k;

	ASSERT_THAT((st=StackCreate(10,1))!=NULL);
	
	ASSERT_THAT(StackIsEmpty(NULL)==1);
	
	ASSERT_THAT(StackIsEmpty(st)==1);

	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(StackPush(st,i)==ERR_OK);
	}
	ASSERT_THAT(StackIsEmpty(st)==0);
	
	
	for (i=10; i>0 ; --i)
	{
		ASSERT_THAT(StackPop(st,&k)==ERR_OK);
	}
	ASSERT_THAT(StackIsEmpty(st)==1);
	
	StackDestroy(st);
END_UNIT

UNIT(StackTopTest)
	
	Stack *st;
	int i, item;

	ASSERT_THAT(StackTop(NULL,&item)==ERR_NOT_INITIALIZED);

	ASSERT_THAT((st=StackCreate(10,1))!=NULL);
	
	ASSERT_THAT(StackTop(st,NULL)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT(StackTop(st,&item)==ERR_UNDERFLOW);

	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(StackPush(st,i)==ERR_OK);
		ASSERT_THAT((StackTop(st,&item)==ERR_OK)&&item==i);

	}
	
	StackDestroy(st);
END_UNIT

UNIT(StackPopTest)
	
	Stack *st;
	int i,item;

	ASSERT_THAT(StackPop(NULL,&item)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((st=StackCreate(10,1))!=NULL);

	ASSERT_THAT(StackPop(st,NULL)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT(StackPop(st,&item)==ERR_UNDERFLOW);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(StackPush(st,i)==ERR_OK);

	}
	for (i=9 ; i>0 ; --i)
	{
		ASSERT_THAT((StackPop(st,&item)==ERR_OK)&&(item==i));

	}

	StackDestroy(st);
END_UNIT


TEST_SUITE(Vector Tests)

	TEST(StackCreateTest)
	TEST(StackPushTest_Params)
	TEST(StackPushTest_Normal)
	TEST(StackIsEmptyTest)
	TEST(StackTopTest)
	TEST(StackPopTest)

END_SUITE




