
#include "heap.h"
#include "../mu_test.h"


/** 
 *  @file heapTest.c
 *  @brief Tests for API for the heap (data == void*)
 *	
 *  @details  See the tests names.
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug None! 
 */

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

UNIT(HeapBuildParams)

	ASSERT_THAT(HeapBuild(NULL)==NULL);
	
END_UNIT

UNIT(HeapBuildNormal)

	Heap* newHeap;
	Vector* vec;
	int i;

	ASSERT_THAT((vec=VectorCreate(10,10))!=NULL);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);
	
	ASSERT_THAT(IsHeapOK(newHeap));

	VectorDestroy(vec);
	
	HeapDestroy(newHeap);
	HeapDestroy(newHeap);

END_UNIT

UNIT(HeapInsertParams)

	Heap* newHeap;
	Vector* vec;
	
	ASSERT_THAT((vec=VectorCreate(1,0))!=NULL);

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);
	
	ASSERT_THAT(HeapInsert(NULL,5)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT(HeapInsert(newHeap,5)==ERR_OK);
	ASSERT_THAT(HeapInsert(newHeap,5)==ERR_OVERFLOW);
	
	VectorDestroy(vec);
	HeapDestroy(newHeap);
END_UNIT

UNIT(HeapInsertNormal)


	Heap* newHeap;
	Vector* vec;
	int i,data;

	ASSERT_THAT((vec=VectorCreate(10,10))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);
	
	ASSERT_THAT(IsHeapOK(newHeap));

	for (i=11 ; i<=25 ; ++i)
	{
		ASSERT_THAT(HeapInsert(newHeap,i)==ERR_OK);		
	}

	ASSERT_THAT(IsHeapOK(newHeap));

	for (i=25 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapExtractMax(newHeap,&data)==ERR_OK)&&(data==i));		
	}

	ASSERT_THAT(IsHeapOK(newHeap));
	
	VectorDestroy(vec);
	HeapDestroy(newHeap);
END_UNIT

UNIT(HeapItemsNumParams)

	ASSERT_THAT(HeapItemsNum(NULL)==0);
	
END_UNIT

UNIT(HeapItemsNumNormal)	

	Heap* newHeap;
	Vector* vec;
	int i,data;

	ASSERT_THAT((vec=VectorCreate(10,10))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);
	
	ASSERT_THAT(HeapItemsNum(newHeap)==10);

	for (i=11 ; i<=25 ; ++i)
	{
		ASSERT_THAT(HeapInsert(newHeap,i)==ERR_OK);		
	}
	
	ASSERT_THAT(HeapItemsNum(newHeap)==25);
	
	ASSERT_THAT(IsHeapOK(newHeap));

	for (i=25 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapExtractMax(newHeap,&data)==ERR_OK)&&(data==i));		
	}

	ASSERT_THAT(HeapItemsNum(newHeap)==0);
	
	VectorDestroy(vec);
	HeapDestroy(newHeap);
END_UNIT

UNIT(HeapMaxParams)

	Heap* newHeap;
	Vector* vec;
	int data;
	
	ASSERT_THAT((vec=VectorCreate(1,0))!=NULL);

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);

	ASSERT_THAT(HeapMax(NULL,&data)==ERR_NOT_INITIALIZED);
	ASSERT_THAT(HeapMax(newHeap,NULL)==ERR_NOT_INITIALIZED);

	ASSERT_THAT(HeapMax(newHeap,&data)==ERR_UNDERFLOW);

	VectorDestroy(vec);
	HeapDestroy(newHeap);
END_UNIT

UNIT(HeapMaxNormal)	

	Heap* newHeap;
	Vector* vec;
	int i,data;

	ASSERT_THAT((vec=VectorCreate(10,10))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);
	
	ASSERT_THAT((HeapMax(newHeap,&data)==ERR_OK)&&(data==10));

	for (i=11 ; i<=125 ; ++i)
	{
		ASSERT_THAT(HeapInsert(newHeap,i)==ERR_OK);		
	}
	
	ASSERT_THAT((HeapMax(newHeap,&data)==ERR_OK)&&(data==125));

	for (i=125 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapMax(newHeap,&data)==ERR_OK)&&(data==i));
		ASSERT_THAT(HeapExtractMax(newHeap,&data)==ERR_OK);		
	}
	ASSERT_THAT(HeapMax(newHeap,&data)==ERR_UNDERFLOW);
	
	VectorDestroy(vec);
	HeapDestroy(newHeap);
END_UNIT

UNIT(HeapExtractMaxParams)

	Heap* newHeap;
	Vector* vec;
	int data;
	
	ASSERT_THAT((vec=VectorCreate(1,0))!=NULL);

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);

	ASSERT_THAT(HeapExtractMax(NULL,&data)==ERR_NOT_INITIALIZED);
	ASSERT_THAT(HeapExtractMax(newHeap,NULL)==ERR_NOT_INITIALIZED);

	ASSERT_THAT(HeapExtractMax(newHeap,&data)==ERR_UNDERFLOW);

	VectorDestroy(vec);
	HeapDestroy(newHeap);
END_UNIT

UNIT(HeapExtractMaxNormal)

	Heap* newHeap;
	Vector* vec;
	int i,data;

	ASSERT_THAT((vec=VectorCreate(10,10))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(VectorAdd(vec,i)==ERR_OK);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec))!=NULL);

	for (i=11 ; i<=10025 ; ++i)
	{
		ASSERT_THAT(HeapInsert(newHeap,i)==ERR_OK);		
	}

	for (i=10025 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapExtractMax(newHeap,&data)==ERR_OK)&&(data==i));

		ASSERT_THAT(IsHeapOK(newHeap)); 
	}

	ASSERT_THAT(IsHeapOK(newHeap));

	VectorDestroy(vec);
	HeapDestroy(newHeap);
END_UNIT





TEST_SUITE(HeapTests)

	TEST(HeapBuildParams)
	TEST(HeapBuildNormal)

	TEST(HeapInsertParams)
	TEST(HeapInsertNormal)
	
	TEST(HeapItemsNumParams)
	TEST(HeapItemsNumNormal)
	
	TEST(HeapMaxParams)
	TEST(HeapMaxNormal)
	
	TEST(HeapExtractMaxParams)
	TEST(HeapExtractMaxNormal)

END_SUITE



