

#include "DLinkList.h"
#include "../mu_test.h"


/** 
 *  @file DLinkListTest.c
 *  @brief Tests for API for the double linked list (data == ints)
 *	
 *  @details  See the tests names.
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug No known bugs! 
 */

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

UNIT(ListCreateTest)

	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	ListDestroy(newList);
	
	/*double destroy test*/
	ListDestroy(newList);

END_UNIT


UNIT(ListPushHeadTestParams)

	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	ASSERT_THAT(ListPushHead(NULL,5)==ERR_NOT_INITIALIZED);
	
	ListDestroy(newList);

END_UNIT

UNIT(ListPushHeadTestsNormal)

	int i,data;
	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListPushHead(newList,i)==ERR_OK);		
	}
	/*
	ListPrint(newList);
	*/
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((ListPopHead(newList,&data)==ERR_OK)&&(data==i));		
	}

	ListDestroy(newList);

END_UNIT

UNIT(ListPushTailTestParams)

	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	ASSERT_THAT(ListPushTail(NULL,5)==ERR_NOT_INITIALIZED);
	
	ListDestroy(newList);

END_UNIT

UNIT(ListPushTailTestsNormal)

	int i,data;
	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListPushTail(newList,i)==ERR_OK);		
	}
	/*
	ListPrint(newList);
	*/
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((ListPopTail(newList,&data)==ERR_OK)&&(data==i));		
	}

	ListDestroy(newList);

END_UNIT


UNIT(ListIsEmptyTestParams)

	ASSERT_THAT(ListIsEmpty(NULL));
	
END_UNIT

UNIT(ListIsEmptyTestNormal)	

	int i,data;
	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	ASSERT_THAT(ListIsEmpty(newList));

	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListPushHead(newList,i)==ERR_OK);
	}
	ASSERT_THAT(!ListIsEmpty(newList));
	
	for (i=10; i>=1 ; --i)
	{
		ASSERT_THAT(ListPopHead(newList,&data)==ERR_OK);
	}
	ASSERT_THAT(ListIsEmpty(newList));
	
	ListDestroy(newList);

END_UNIT

UNIT(ListCountItemsTestParams)

	ASSERT_THAT( ListCountItems(NULL)==0);
	
END_UNIT

UNIT(ListCountItemsTestNormal)	

	int i,data;
	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	ASSERT_THAT( ListCountItems(newList)==0);

	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListPushHead(newList,i)==ERR_OK);
		ASSERT_THAT(ListCountItems(newList)==i);
	}
	
	
	for (i=10; i>=1 ; --i)
	{
		ASSERT_THAT(ListPopHead(newList,&data)==ERR_OK);
		ASSERT_THAT(ListCountItems(newList)==i-1);
	}
	ASSERT_THAT( ListCountItems(newList)==0);
	
	ListDestroy(newList);

END_UNIT

UNIT(ListPopHeadTestParams)

	int data;
	List* newList;
	
	ASSERT_THAT((newList=ListCreate())!=NULL);

	ASSERT_THAT(ListPopHead(NULL,&data)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT(ListPushHead(newList,5)==ERR_OK);

	ASSERT_THAT(ListPopHead(newList,NULL)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((ListPopHead(newList,&data)==ERR_OK)&&(5==data));

	ListDestroy(newList);

END_UNIT

UNIT(ListPopHeadTestNormal)

	int i,data;
	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListPushTail(newList,i)==ERR_OK);		
	}
	/*
	ListPrint(newList);
	*/
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT((ListPopHead(newList,&data)==ERR_OK)&&(data==i));		
	}
	
	ASSERT_THAT(ListPopHead(newList,&data)==ERR_UNDERFLOW);

	ListDestroy(newList);

END_UNIT

UNIT(ListPopTailTestParams)

	int data;
	List* newList;
	
	ASSERT_THAT((newList=ListCreate())!=NULL);

	ASSERT_THAT(ListPopTail(NULL,&data)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT(ListPushHead(newList,5)==ERR_OK);

	ASSERT_THAT(ListPopTail(newList,NULL)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((ListPopTail(newList,&data)==ERR_OK)&&(5==data));

	ListDestroy(newList);

END_UNIT

UNIT(ListPopTailTestNormal)

	int i,data;
	List* newList;

	ASSERT_THAT((newList=ListCreate())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListPushTail(newList,i)==ERR_OK);		
	}
	/*
	ListPrint(newList);
	*/
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((ListPopTail(newList,&data)==ERR_OK)&&(data==i));		
	}

	ASSERT_THAT(ListPopTail(newList,&data)==ERR_UNDERFLOW);

	ListDestroy(newList);

END_UNIT




TEST_SUITE(Linked list Tests)

	TEST(ListCreateTest)
	
	TEST(ListPushHeadTestParams)
	TEST(ListPushHeadTestsNormal)
	
	TEST(ListPushTailTestParams)
	TEST(ListPushTailTestsNormal)
	
	TEST(ListIsEmptyTestParams)
	TEST(ListIsEmptyTestNormal)	
	
	TEST(ListCountItemsTestParams)
	TEST(ListCountItemsTestNormal)	
	
	TEST(ListPopHeadTestParams)
	TEST(ListPopHeadTestNormal)
	
	TEST(ListPopTailTestParams)
	TEST(ListPopTailTestNormal)

END_SUITE



 
 


