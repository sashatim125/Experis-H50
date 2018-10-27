/*This file contains the main=test for llist.h API.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 16.12.2017
 */
 
#include "llist.h"
#include "../mu_test.h"


static Person g_personsList[]={{1,"A",10,NULL},
       			               {2,"B",11,NULL},
                		       {3,"C",12,NULL},
                        	   {4,"D",13,NULL},
	                           {5,"E",14,NULL},
       		                   {6,"F",15,NULL},
              		           {7,"G",16,NULL},
                     		   {8,"H",17,NULL},
		                       {9,"I",18,NULL},
        		              {10,"J",19,NULL}};

UNIT(ListInsertHead_Params)

	ASSERT_THAT(ListInsertHead(NULL,&g_personsList[0])==&g_personsList[0]);
		
	ASSERT_THAT(ListInsertHead(&g_personsList[0],NULL)==&g_personsList[0]);

END_UNIT

UNIT(ListInsertHead_Normal)

	int i;
	Person *lList=NULL;
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT((lList=ListInsertHead(lList,&g_personsList[i]))==&g_personsList[i]);		
	}
/*
	PrintList(lList);
*/
END_UNIT

UNIT(ListRemoveHead_Params)

	Person *personPtr;

	ASSERT_THAT(ListRemoveHead(NULL,&personPtr)==NULL);

	ASSERT_THAT(ListInsertHead(NULL,&g_personsList[0])==&g_personsList[0]);
	ASSERT_THAT(ListRemoveHead(&g_personsList[0],NULL)==&g_personsList[0]);

END_UNIT

UNIT(ListInsert_RemoveHead_Normal)

	int i;
	Person *personPtr,*lList=NULL;

	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT((lList=ListInsertHead(lList,&g_personsList[i]))==&g_personsList[i]);		
	}
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((lList=ListRemoveHead(lList,&personPtr))||1);
		ASSERT_THAT(personPtr->m_id==i);
	}

END_UNIT

UNIT(ListInsertByKey_Params)

	ASSERT_THAT(ListInsertByKey(NULL,1,&g_personsList[0])==&g_personsList[0]);
		
	ASSERT_THAT(ListInsertByKey(&g_personsList[0],1,NULL)==&g_personsList[0]);

END_UNIT

UNIT(ListInsertByKey_Normal)

	int i;
	Person *lList=NULL, *personPtr;
	
	for (i=9 ; i>=0 ; --i)
	{
		ASSERT_THAT((lList=ListInsertByKey(lList,i+1,&g_personsList[i]))!=NULL);		
	}
/*
	PrintList(lList);
*/
	ASSERT_THAT((lList=ListInsertByKey(lList,1,&g_personsList[0]))!=NULL);
/*
	PrintList(lList);
*/
	
	for (i=0 ; i<10 ; ++i)
	{
		lList=ListRemoveHead(lList,&personPtr);
		ASSERT_THAT(personPtr->m_id==i+1);
	}
END_UNIT

UNIT(ListInsertByKeyRec_Params)

	ASSERT_THAT(ListInsertByKeyRec(NULL,1,&g_personsList[0])==&g_personsList[0]);
		
	ASSERT_THAT(ListInsertByKeyRec(&g_personsList[0],1,NULL)==&g_personsList[0]);

END_UNIT

UNIT(ListInsertByKeyRec_Normal)

	int i;
	Person *lList=NULL, *personPtr;
	
	for (i=9 ; i>=0 ; --i)
	{
		ASSERT_THAT((lList=ListInsertByKeyRec(lList,i+1,&g_personsList[i]))!=NULL);		
	}
/*
	PrintList(lList);
*/
	ASSERT_THAT((lList=ListInsertByKey(lList,1,&g_personsList[0]))!=NULL);
/*
	PrintList(lList);
*/
	for (i=0 ; i<10 ; ++i)
	{
		lList=ListRemoveHead(lList,&personPtr);
		ASSERT_THAT(personPtr->m_id==i+1);
	}
	

END_UNIT

UNIT(ListRemoveByKey_Params)

	Person *personPtr;

	ASSERT_THAT(ListRemoveByKey(NULL,1,&personPtr)==NULL);

	ASSERT_THAT(ListInsertHead(NULL,&g_personsList[0])==&g_personsList[0]);
	ASSERT_THAT(ListRemoveByKey(&g_personsList[0],1,NULL)==&g_personsList[0]);

END_UNIT

UNIT(ListRemoveByKey_Normal)

	int i;
	Person *lList=NULL, *personPtr;
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT((lList=ListInsertByKey(lList,i+1,&g_personsList[i]))!=NULL);		
	}	
/*	
	PrintList(lList);
*/
	for (i=5; i<=10 ; ++i)
	{
		lList=ListRemoveByKey(lList,i,&personPtr);
		ASSERT_THAT(personPtr->m_id==i);
	}
/*	
	PrintList(lList);
*/
	for (i=4; i>=1; --i)
	{
		lList=ListRemoveByKey(lList,i,&personPtr);
		ASSERT_THAT(personPtr->m_id==i);
	}
/*	
	PrintList(lList);
*/
END_UNIT

UNIT(ListRemoveByKeyRec_Params)

	Person *personPtr;

	ASSERT_THAT(ListRemoveByKeyRec(NULL,1,&personPtr)==NULL);

	ASSERT_THAT(ListInsertHead(NULL,&g_personsList[0])==&g_personsList[0]);
	ASSERT_THAT(ListRemoveByKeyRec(&g_personsList[0],1,NULL)==&g_personsList[0]);

END_UNIT

UNIT(ListRemoveByKeyRec_Normal)

	int i;
	Person *lList=NULL, *personPtr;
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT((lList=ListInsertByKeyRec(lList,i+1,&g_personsList[i]))!=NULL);		
	}	
/*	
	PrintList(lList);
*/
	for (i=5; i<=10 ; ++i)
	{
		lList=ListRemoveByKeyRec(lList,i,&personPtr);
		ASSERT_THAT(personPtr->m_id==i);
	}
/*	
	PrintList(lList);
*/
	for (i=4; i>=1; --i)
	{
		lList=ListRemoveByKeyRec(lList,i,&personPtr);
		ASSERT_THAT(personPtr->m_id==i);
	}
/*	
	PrintList(lList);
*/
END_UNIT


TEST_SUITE(Linked list Tests)

	TEST(ListInsertHead_Params)
	TEST(ListInsertHead_Normal)
	
	TEST(ListRemoveHead_Params)
	TEST(ListInsert_RemoveHead_Normal)
	
	TEST(ListInsertByKey_Params)
	TEST(ListInsertByKey_Normal)
	
	TEST(ListInsertByKeyRec_Params)
	TEST(ListInsertByKeyRec_Normal)
	
	TEST(ListRemoveByKey_Params)
	
	
	TEST(ListRemoveByKey_Normal)
	
	TEST(ListRemoveByKeyRec_Params)
	TEST(ListRemoveByKeyRec_Normal)	
	

END_SUITE




