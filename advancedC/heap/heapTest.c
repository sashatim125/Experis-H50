
#include "heap.h"
#include "../mu_test.h"

#include <stdio.h>


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

static int LessInt(void* _left, void* _right)
{
	return (*(int*)_left < *(int*)_right);
}

static int	PrintInt(void *_element, size_t _index, void *_context)
{
	printf(" %d ",*(int*)_element);

	return 1;
}

UNIT(HeapBuildParams)

	ASSERT_THAT(HeapBuild(NULL,LessInt)==NULL);
	
END_UNIT

UNIT(HeapBuildNormal)

	Heap* newHeap;
	Vector* vec;
	int i;
	int data[10] = {1,2,3,4,5,6,7,8,9,10};

	ASSERT_THAT((vec=Vector_Create(10,10))!=NULL);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,data+i)==VECTOR_SUCCESS);		
	}
/*	
	Vector_ForEach(vec,PrintInt,NULL);
	printf("\n");
	fflush(stdout);
*/
	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);
/*	
	Vector_ForEach(vec,PrintInt,NULL);
	printf("\n");
	fflush(stdout);
*/	
	ASSERT_THAT(IsHeapOK(newHeap));
	
	
	HeapDestroy(newHeap);
	HeapDestroy(newHeap);

	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(HeapInsertParams)

	Heap* newHeap;
	Vector* vec;
	
	ASSERT_THAT((vec=Vector_Create(1,0))!=NULL);

	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);
	
	ASSERT_THAT(HeapInsert(NULL,(void*)5)==HEAP_UNINITIALIZED_ERROR);
	
	ASSERT_THAT(HeapInsert(newHeap,(void*)5)==HEAP_SUCCESS);
	ASSERT_THAT(HeapInsert(newHeap,(void*)5)==HEAP_OVERFLOW_ERROR);
	
	HeapDestroy(newHeap);
	Vector_Destroy(&vec,NULL);
	
END_UNIT

UNIT(HeapInsertNormal)

	Heap* newHeap;
	Vector* vec;
	int i;
	int data[10] = {1,2,3,4,5,6,7,8,9,10};
	void *d;

	ASSERT_THAT((vec=Vector_Create(10,10))!=NULL);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,data+i)==VECTOR_SUCCESS);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);
/*
	Vector_ForEach(vec,PrintInt,NULL);
	printf("\n");
	fflush(stdout);
*/	
	ASSERT_THAT(IsHeapOK(newHeap));
	
	
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapExtractMax(newHeap,&d)==HEAP_SUCCESS)&&(*(int*)d==i));		
		ASSERT_THAT(IsHeapOK(newHeap));
	/*	
		Vector_ForEach(vec,PrintInt,NULL);
		printf("\n");
		fflush(stdout);
	*/
	}
	
	HeapDestroy(newHeap);
	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(HeapItemsNumParams)

	ASSERT_THAT(HeapItemsNum(NULL)==0);
	
END_UNIT

UNIT(HeapItemsNumNormal)	

Heap* newHeap;
	Vector* vec;
	int i;
	int data[10] = {1,2,3,4,5,6,7,8,9,10};
	void *d;

	ASSERT_THAT((vec=Vector_Create(10,10))!=NULL);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,data+i)==VECTOR_SUCCESS);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);
	
	ASSERT_THAT(HeapItemsNum(newHeap)==10);
	
	ASSERT_THAT(IsHeapOK(newHeap));

	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapExtractMax(newHeap,&d)==HEAP_SUCCESS)&&(*(int*)d==i));		
	}

	ASSERT_THAT(HeapItemsNum(newHeap)==0);
	
	HeapDestroy(newHeap);
	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(HeapMaxParams)

	Heap* newHeap;
	Vector* vec;
	void *data;
	
	ASSERT_THAT((vec=Vector_Create(1,0))!=NULL);

	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);

	ASSERT_THAT(HeapMax(NULL,&data)==HEAP_UNINITIALIZED_ERROR);
	ASSERT_THAT(HeapMax(newHeap,NULL)==HEAP_UNINITIALIZED_ERROR);

	ASSERT_THAT(HeapMax(newHeap,&data)==HEAP_UNDERFLOW_ERROR);

	Vector_Destroy(&vec,NULL);
	HeapDestroy(newHeap);
END_UNIT

UNIT(HeapMaxNormal)	

	Heap* newHeap;
	Vector* vec;
	int i;
	int data[10] = {1,2,3,4,5,6,7,8,9,10};
	void *d;

	ASSERT_THAT((vec=Vector_Create(10,10))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,data+i-1)==VECTOR_SUCCESS);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);
	
	ASSERT_THAT((HeapMax(newHeap,&d)==HEAP_SUCCESS)&&(*(int*)d==10));

	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapMax(newHeap,&d)==HEAP_SUCCESS)&&(*(int*)d==i));
		ASSERT_THAT(HeapExtractMax(newHeap,&d)==HEAP_SUCCESS);		
	}
	ASSERT_THAT(HeapMax(newHeap,&d)==HEAP_UNDERFLOW_ERROR);
	
	HeapDestroy(newHeap);
	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(HeapExtractMaxParams)

	Heap* newHeap;
	Vector* vec;
	void *data;
	
	ASSERT_THAT((vec=Vector_Create(1,0))!=NULL);

	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);

	ASSERT_THAT(HeapExtractMax(NULL,&data)==HEAP_UNINITIALIZED_ERROR);
	ASSERT_THAT(HeapExtractMax(newHeap,NULL)==HEAP_UNINITIALIZED_ERROR);

	ASSERT_THAT(HeapExtractMax(newHeap,&data)==HEAP_UNDERFLOW_ERROR);

	HeapDestroy(newHeap);
	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(HeapExtractMaxNormal)

	Heap* newHeap;
	Vector* vec;
	int i;
	int data[10] = {1,2,3,4,5,6,7,8,9,10};
	void *d;
	
	ASSERT_THAT((vec=Vector_Create(10,10))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,data+i-1)==VECTOR_SUCCESS);		
	}

	ASSERT_THAT((newHeap=HeapBuild(vec,LessInt))!=NULL);

	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((HeapExtractMax(newHeap,&d)==HEAP_SUCCESS)&&(*(int*)d==i));
		
		ASSERT_THAT(IsHeapOK(newHeap)); 
	}

	ASSERT_THAT(IsHeapOK(newHeap));

	HeapDestroy(newHeap);
	Vector_Destroy(&vec,NULL);
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



