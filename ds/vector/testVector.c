/*This file contains the main=test for vector.h API.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#include "vector.h"
#include "../mu_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

UNIT(VectorCreateTest)
	
	Vector *vec;
	
	ASSERT_THAT((vec=VectorCreate(10,10))!=NULL);
	VectorDestroy(vec);
	
	ASSERT_THAT((vec=VectorCreate(0,0))==NULL);
	
	ASSERT_THAT((vec=VectorCreate(1,0))!=NULL);
	VectorDestroy(vec);
	
	ASSERT_THAT((vec=VectorCreate(0,1))!=NULL);
	VectorDestroy(vec);
	
	ASSERT_THAT((vec=VectorCreate(ULONG_MAX,1))==NULL);
		
END_UNIT

UNIT(VectorAddTest_Params)
	
	Vector *vec;

	ASSERT_THAT(VectorAdd(NULL,1)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((vec=VectorCreate(0,ULONG_MAX))!=NULL);
	ASSERT_THAT(VectorAdd(vec,1)==ERR_REALLOCATION_FAILED);
	
	VectorDestroy(vec);	
	
	ASSERT_THAT((vec=VectorCreate(1,0))!=NULL);
	ASSERT_THAT((VectorAdd(vec,1)==ERR_OK)&&(VectorAdd(vec,2)==ERR_OVERFLOW));
	
	VectorDestroy(vec);

END_UNIT

UNIT(VectorAddTest_Normal)
	
	Vector *vec;
	int i;	
	
	ASSERT_THAT((vec=VectorCreate(1,1))!=NULL);
	
	ASSERT_THAT(VectorAdd(vec,5)==ERR_OK);
	
	ASSERT_THAT(VectorAdd(vec,10)!=ERR_REALLOCATION_FAILED);	
	
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)!=ERR_REALLOCATION_FAILED);		
	}
	VectorDestroy(vec);
END_UNIT


UNIT(VectorItemsNumTest)
	
	Vector *vec;
	size_t numOfEl;
	int i,k;

	ASSERT_THAT((vec=VectorCreate(10,1))!=NULL);
	
	ASSERT_THAT(VectorItemsNum(NULL,&numOfEl)==ERR_NOT_INITIALIZED);

	ASSERT_THAT(VectorItemsNum(vec,NULL)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((VectorItemsNum(vec,&numOfEl)==ERR_OK)&&(numOfEl==0));

	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);
	
		ASSERT_THAT((VectorItemsNum(vec,&numOfEl)==ERR_OK)&&
			(numOfEl==i+1));
	}
	
	for (i=10; i>0 ; --i)
	{
		ASSERT_THAT(VectorDelete(vec,&k)==ERR_OK);
	
		ASSERT_THAT((VectorItemsNum(vec,&numOfEl)==ERR_OK)&&
			(numOfEl==i-1));
	}

	VectorDestroy(vec);
END_UNIT

UNIT(VectorGetTest)
	
	Vector *vec;
	int i, item;

	ASSERT_THAT(VectorGet(NULL,1,&item)==ERR_NOT_INITIALIZED);

	ASSERT_THAT((vec=VectorCreate(10,1))!=NULL);
	
	ASSERT_THAT(VectorGet(vec,1,NULL)==ERR_NOT_INITIALIZED);

	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);

	}
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT((VectorGet(vec,(size_t)i,&item)==ERR_OK)&&item==i);

	}
	
	ASSERT_THAT(VectorGet(vec,10,&item)==ERR_WRONG_INDEX);
	
	VectorDestroy(vec);
END_UNIT

UNIT(VectorSetTest)
	
	Vector *vec;
	int i, item;

	ASSERT_THAT(VectorSet(NULL,1,0)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((vec=VectorCreate(10,1))!=NULL);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,0)==ERR_OK);

	}
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(VectorSet(vec,(size_t)i,i)==ERR_OK);

	}
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT((VectorGet(vec,(size_t)i,&item)==ERR_OK)&&(item==i));

	}

	ASSERT_THAT(VectorSet(vec,10,5)==ERR_WRONG_INDEX);

	VectorDestroy(vec);
END_UNIT

UNIT(VectorDeleteTest)
	
	Vector *vec;
	int i,item;

	ASSERT_THAT(VectorDelete(NULL,&item)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((vec=VectorCreate(10,1))!=NULL);

	ASSERT_THAT(VectorDelete(vec,NULL)==ERR_NOT_INITIALIZED);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);

	}
	for (i=9 ; i>0 ; --i)
	{
		ASSERT_THAT((VectorDelete(vec,&item)==ERR_OK)&&(item==i));

	}
	ASSERT_THAT(VectorGet(vec,0,&item)==ERR_OK);
	
	ASSERT_THAT(VectorDelete(vec,&item)==ERR_OK);
	ASSERT_THAT(VectorDelete(vec,&item)==ERR_UNDERFLOW);

	VectorDestroy(vec);
END_UNIT


TEST_SUITE(Vector Tests)

TEST(VectorCreateTest)
TEST(VectorAddTest_Params)
TEST(VectorAddTest_Normal)
TEST(VectorItemsNumTest)
TEST(VectorGetTest)
TEST(VectorSetTest)
TEST(VectorDeleteTest)

END_SUITE




