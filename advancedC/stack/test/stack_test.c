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
#include "mu_test.h"
#include <dlfcn.h>


static void *libHandle;

static Stack* (*Stack_CreatePtr)();

static void (*Stack_DestroyPtr)(Stack* _stack,DestroyFunc _destFunc);

static Stack_Result  (*Stack_PushPtr)(Stack* _stack, void *_item);

static Stack_Result  (*Stack_PopPtr)(Stack* _stack, void **_pItem);

static Stack_Result  (*Stack_TopPtr)(const Stack* _stack, void **_pItem);

static int (*Stack_IsEmptyPtr)(const Stack* _stack);

UNIT(Start)

	ASSERT_THAT(NULL!=(libHandle = dlopen("../../lib/libDS.so",RTLD_LAZY)));
	
	*(void**)&Stack_CreatePtr = dlsym(libHandle,"Stack_Create");
	
	*(void**)&Stack_DestroyPtr = dlsym(libHandle,"Stack_Destroy");
	
	*(void**)&Stack_PushPtr = dlsym(libHandle,"Stack_Push");
	
	*(void**)&Stack_PopPtr = dlsym(libHandle,"Stack_Pop");
	
	*(void**)&Stack_TopPtr = dlsym(libHandle,"Stack_Top");
	
	*(void**)&Stack_IsEmptyPtr = dlsym(libHandle,"Stack_IsEmpty");


END_UNIT

UNIT(StackCreateTest)
	
	Stack *st;
	
	ASSERT_THAT((st=Stack_CreatePtr())!=NULL);
	
	Stack_DestroyPtr(st,NULL);
	Stack_DestroyPtr(st,NULL);

END_UNIT

UNIT(StackPushTest_Params)
	
	Stack *st;
	
	ASSERT_THAT((st=Stack_CreatePtr())!=NULL);
	
	ASSERT_THAT(Stack_PushPtr(NULL,(void*)1)==STACK_NOT_INITIALIZED);

	ASSERT_THAT(Stack_PushPtr(st,NULL)==STACK_NULL_ELEMENT_ERROR);
	
	Stack_DestroyPtr(st,NULL);
	Stack_DestroyPtr(st,NULL);

END_UNIT

UNIT(StackPushTest_Normal)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};	
	
	ASSERT_THAT((st=Stack_CreatePtr())!=NULL);	
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_PushPtr(st,data+i)==STACK_OK);		
	}
	
	Stack_DestroyPtr(st,NULL);

END_UNIT

UNIT(StackIsEmptyTest)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	void *item;

	ASSERT_THAT((st=Stack_CreatePtr())!=NULL);
	
	ASSERT_THAT(Stack_IsEmptyPtr(NULL)!=0);

	ASSERT_THAT(Stack_IsEmptyPtr(st)!=0);

	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_PushPtr(st,data+i)==STACK_OK);
	}
	ASSERT_THAT(Stack_IsEmptyPtr(st)==0);
	
	
	for (i=10; i>0 ; --i)
	{
		ASSERT_THAT(Stack_PopPtr(st,&item)==STACK_OK);
	}
	ASSERT_THAT(Stack_IsEmptyPtr(st)!=0);
	
	Stack_DestroyPtr(st,NULL);

END_UNIT

UNIT(StackTopTest)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	void *item;

	ASSERT_THAT(Stack_TopPtr(NULL,&item)==STACK_NOT_INITIALIZED);

	ASSERT_THAT((st=Stack_CreatePtr())!=NULL);
	
	ASSERT_THAT(Stack_TopPtr(st,NULL)==STACK_NOT_INITIALIZED);
	
	ASSERT_THAT(Stack_TopPtr(st,&item)==STACK_UNDERFLOW);

	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_PushPtr(st,data+i)==STACK_OK);
		ASSERT_THAT((Stack_TopPtr(st,&item)==STACK_OK) && *(int*)item == i+1);
	}
	
	Stack_DestroyPtr(st,NULL);

END_UNIT

UNIT(StackPopTest)
	
	Stack *st;
	int i;
	int data[] = {1,2,3,4,5,6,7,8,9,10};
	void *item;
	
	ASSERT_THAT(Stack_PopPtr(NULL,&item)==STACK_NOT_INITIALIZED);
	
	ASSERT_THAT((st=Stack_CreatePtr())!=NULL);

	ASSERT_THAT(Stack_PopPtr(st,NULL)==STACK_NOT_INITIALIZED);
	
	ASSERT_THAT(Stack_PopPtr(st,&item)==STACK_UNDERFLOW);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Stack_PushPtr(st,data+i)==STACK_OK);

	}
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((Stack_PopPtr(st,&item)==STACK_OK) && *(int*)item == i);

	}

	Stack_DestroyPtr(st,NULL);

END_UNIT

UNIT(Finish)

	dlclose(libHandle);

END_UNIT


TEST_SUITE(Stack Tests)

	TEST(Start)

	TEST(StackCreateTest)
	
	TEST(StackPushTest_Params)
	TEST(StackPushTest_Normal)
	
	TEST(StackIsEmptyTest)
	
	TEST(StackTopTest)
	
	TEST(StackPopTest)
	
	TEST(Finish)

END_SUITE











