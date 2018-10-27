/** 
 *  @file stack_test.c
 *  @brief Unit tests for the generic stack (over list)
 *	
 *  @details  see incode comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */
 
#include "stack.h"
#include "../mu_test.h"


UNIT(StackCreateTest)
	
	Stack *st;
	
	ASSERT_THAT((st=Stack_Create())!=NULL);
	
	Stack_Destroy(st,NULL);
	Stack_Destroy(st,NULL);

END_UNIT

UNIT(StackPushTest_Params)
	
	Stack *st;
	
	ASSERT_THAT((st=Stack_Create())!=NULL);
	
	ASSERT_THAT(Stack_Push(NULL,(void*)1)==STACK_NOT_INITIALIZED);

	ASSERT_THAT(Stack_Push(st,NULL)==STACK_NULL_ELEMENT_ERROR);
	
	Stack_Destroy(st,NULL);
	Stack_Destroy(st,NULL);

END_UNIT

UNIT(StackPushTest_Normal)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};	
	
	ASSERT_THAT((st=Stack_Create())!=NULL);	
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_Push(st,data+i)==STACK_OK);		
	}
	
	Stack_Destroy(st,NULL);

END_UNIT

UNIT(StackIsEmptyTest)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	void *item;

	ASSERT_THAT((st=Stack_Create())!=NULL);
	
	ASSERT_THAT(Stack_IsEmpty(NULL)!=0);

	ASSERT_THAT(Stack_IsEmpty(st)!=0);

	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_Push(st,data+i)==STACK_OK);
	}
	ASSERT_THAT(Stack_IsEmpty(st)==0);
	
	
	for (i=10; i>0 ; --i)
	{
		ASSERT_THAT(Stack_Pop(st,&item)==STACK_OK);
	}
	ASSERT_THAT(Stack_IsEmpty(st)!=0);
	
	Stack_Destroy(st,NULL);

END_UNIT

UNIT(StackTopTest)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	void *item;

	ASSERT_THAT(Stack_Top(NULL,&item)==STACK_NOT_INITIALIZED);

	ASSERT_THAT((st=Stack_Create())!=NULL);
	
	ASSERT_THAT(Stack_Top(st,NULL)==STACK_NOT_INITIALIZED);
	
	ASSERT_THAT(Stack_Top(st,&item)==STACK_UNDERFLOW);

	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_Push(st,data+i)==STACK_OK);
		ASSERT_THAT((Stack_Top(st,&item)==STACK_OK) && *(int*)item == i+1);
	}
	
	Stack_Destroy(st,NULL);

END_UNIT

UNIT(StackPopTest)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	void *item;
	
	ASSERT_THAT(Stack_Pop(NULL,&item)==STACK_NOT_INITIALIZED);
	
	ASSERT_THAT((st=Stack_Create())!=NULL);

	ASSERT_THAT(Stack_Pop(st,NULL)==STACK_NOT_INITIALIZED);
	
	ASSERT_THAT(Stack_Pop(st,&item)==STACK_UNDERFLOW);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_Push(st,data+i)==STACK_OK);

	}
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((Stack_Pop(st,&item)==STACK_OK) && *(int*)item == i);

	}

	Stack_Destroy(st,NULL);

END_UNIT


TEST_SUITE(Stack Tests)

	TEST(StackCreateTest)
	
	TEST(StackPushTest_Params)
	TEST(StackPushTest_Normal)
	
	TEST(StackIsEmptyTest)
	
	TEST(StackTopTest)
	
	TEST(StackPopTest)

END_SUITE











