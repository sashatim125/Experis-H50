

/** 
 * @brief Test a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
 * 
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */
 
#include "vector.h"
#include "../mu_test.h"
#include "../../ds/DLinkList/DLinkList.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

UNIT(Vector_CreateTest)
	
	Vector *vec, *vec1;
	
	ASSERT_THAT((vec=Vector_Create(10,10))!=NULL);
	Vector_Destroy(&vec,NULL);
	
	ASSERT_THAT((vec=Vector_Create(0,0))==NULL);
	
	ASSERT_THAT((vec=Vector_Create(1,0))!=NULL);
	Vector_Destroy(&vec,NULL);
	
	ASSERT_THAT((vec=Vector_Create(0,1))!=NULL);
	Vector_Destroy(&vec,NULL);
	Vector_Destroy(&vec,NULL);
	
	ASSERT_THAT((vec=Vector_Create(ULONG_MAX,1))==NULL);
	
	vec1=vec;
	Vector_Destroy(&vec,NULL);
	Vector_Destroy(&vec1,NULL);
	
	Vector_Destroy(NULL,NULL);
		
END_UNIT

UNIT(Vector_AppendTest_Params)
	
	Vector *vec;
	int val1=1, val2=2;

	ASSERT_THAT(Vector_Append(NULL,&val1)==VECTOR_UNITIALIZED_ERROR);
	
	ASSERT_THAT((vec=Vector_Create(0,ULONG_MAX))!=NULL);
	ASSERT_THAT(Vector_Append(vec,&val1)==VECTOR_ALLOCATION_ERROR);
	
	Vector_Destroy(&vec,NULL);	
	
	ASSERT_THAT((vec=Vector_Create(1,0))!=NULL);
	ASSERT_THAT((Vector_Append(vec,&val1)==VECTOR_SUCCESS)&&(Vector_Append(vec,&val2)==VECTOR_OVERFLOW));
	
	Vector_Destroy(&vec,NULL);

END_UNIT

static void myPrintNum(void *_num)
{
	printf("num = %d\n",*(int*)_num);
}

static int myPrintInt(void* _num, size_t _index, void* _sum)
{
	*(int*)_sum += *(int*)_num;
	
	printf("I am %d, my index is %lu and the sum until me is %d.\n",
		*(int*)_num, _index, *(int*)_sum);
		
	return 1;
}

UNIT(Vector_AppendTest_Normal)
	
	Vector *vec;
	int i , *numbers[5] , sum;	
	int n1=1, n2=2, n3=3, n4=4, n5=5;
	
	numbers[0]=&n1;
	numbers[1]=&n2;
	numbers[2]=&n3;
	numbers[3]=&n4;
	numbers[4]=&n5;
	
	ASSERT_THAT((vec=Vector_Create(5,5))!=NULL);
	
	for (i=0 ; i<5 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,numbers[i])==VECTOR_SUCCESS);		
	}
	
	Vector_ForEach(vec,myPrintInt,&sum);
	
	Vector_Destroy(&vec,myPrintNum);
END_UNIT


static void DllDestroy(void *_dllist)
{
	ListDestroy((List*)_dllist);
}

UNIT(Vector_DestroyTest)
	
	Vector *vec, *vec1;
	int i , *numbers[5] ;	
	int n1=1, n2=2, n3=3, n4=4, n5=5;
	struct Person
	{
		int m_id;
		char m_name[10];
	} *persons[5];
	
	List *myLists[100];
	
	numbers[0]=&n1;
	numbers[1]=&n2;
	numbers[2]=&n3;
	numbers[3]=&n4;
	numbers[4]=&n5;
	
	ASSERT_THAT((vec=Vector_Create(5,5))!=NULL);
	
	for (i=0 ; i<5 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,numbers[i])==VECTOR_SUCCESS);		
	}	
	
	Vector_Destroy(&vec,myPrintNum);
	
	
	for(i=0 ; i<5 ; ++i)
	{
		persons[i]=(struct Person*)malloc(sizeof(struct Person));
	}
	
	ASSERT_THAT((vec=Vector_Create(5,5))!=NULL);
	
	for(i=0 ; i<5 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,persons[i])==VECTOR_SUCCESS);		
	}	
	
	Vector_Destroy(&vec,free);
	
	ASSERT_THAT((vec=Vector_Create(20,5))!=NULL);
	
	for(i=0 ; i<100 ; ++i)
	{
		myLists[i]=ListCreate();
		ListPushHead(myLists[i],i);
		ASSERT_THAT(Vector_Append(vec,myLists[i])==VECTOR_SUCCESS);		
	}
	vec1=vec;
	Vector_Destroy(&vec,DllDestroy);
	ASSERT_THAT(vec == NULL);
	Vector_Destroy(&vec1,DllDestroy);
		
END_UNIT


UNIT(Vector_SizeTest)
	
	Vector *vec;
	int i ,*k, *numbers[5] ;	
	int n1=1, n2=2, n3=3, n4=4, n5=5;
	
	numbers[0]=&n1;
	numbers[1]=&n2;
	numbers[2]=&n3;
	numbers[3]=&n4;
	numbers[4]=&n5;

	ASSERT_THAT((vec=Vector_Create(1,1))!=NULL);
	
	ASSERT_THAT(Vector_Size(NULL)==0);
	
	ASSERT_THAT(Vector_Size(vec)==0);


	for (i=0 ; i<5 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,numbers[i])==VECTOR_SUCCESS);		
		ASSERT_THAT(Vector_Size(vec)==i+1);
	}
	
		ASSERT_THAT(Vector_Capacity(vec)==5);
	
	for (i=5; i>0 ; --i)
	{
		ASSERT_THAT(Vector_Remove(vec,(void**)&k)==VECTOR_SUCCESS);
	
		ASSERT_THAT(Vector_Size(vec)==i-1);
	}
	
	ASSERT_THAT(Vector_Capacity(vec)==2);

	Vector_Destroy(&vec,NULL);
END_UNIT


UNIT(VectorGetTest)
	
	Vector *vec;
	int  *item;
	int i , *numbers[5] ;	
	int n1=1, n2=2, n3=3, n4=4, n5=5;
	
	numbers[0]=&n1;
	numbers[1]=&n2;
	numbers[2]=&n3;
	numbers[3]=&n4;
	numbers[4]=&n5;
	
	ASSERT_THAT(Vector_Get(NULL,1,(void**)&item)==VECTOR_UNITIALIZED_ERROR);

	ASSERT_THAT((vec=Vector_Create(5,1))!=NULL);
	
	ASSERT_THAT(Vector_Get(vec,1,NULL)==VECTOR_UNITIALIZED_ERROR);
	
	for (i=0 ; i<5 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,numbers[i])==VECTOR_SUCCESS);		
	}
	
	for (i=1 ; i<=5 ; ++i)
	{
		ASSERT_THAT((Vector_Get(vec,(size_t)i,(void**)&item)==VECTOR_SUCCESS) && *item==i);

	}
	
	ASSERT_THAT(Vector_Get(vec,10,(void**)&item)==VECTOR_INDEX_OUT_OF_BOUNDS_ERROR);
	
	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(Vector_SetTest)
	
	Vector *vec;
	int  *item;
	int i , *numbers[5] ;	
	int n1=1, n2=2, n3=3, n4=4, n5=5;
	
	numbers[0]=&n1;
	numbers[1]=&n2;
	numbers[2]=&n3;
	numbers[3]=&n4;
	numbers[4]=&n5;

	ASSERT_THAT(Vector_Set(NULL,1,NULL)==VECTOR_UNITIALIZED_ERROR);
	
	ASSERT_THAT((vec=Vector_Create(5,1))!=NULL);
	
	for (i=0 ; i<5 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,NULL)==VECTOR_SUCCESS);		
	}
	
	for (i=5 ; i>=1 ; --i)
	{
		ASSERT_THAT(Vector_Set(vec,(size_t)(6-i),numbers[i-1])==VECTOR_SUCCESS);

	}
	
	for (i=1 ; i<=5 ; ++i)
	{
		ASSERT_THAT((Vector_Get(vec,(size_t)i,(void**)&item)==VECTOR_SUCCESS) && *item == 6-i);

	}

	ASSERT_THAT(Vector_Set(vec,10,NULL)==VECTOR_INDEX_OUT_OF_BOUNDS_ERROR);

	Vector_Destroy(&vec,NULL);
END_UNIT

UNIT(Vector_RemoveTest)
	
	Vector *vec;
	int  *item;
	int i , *numbers[5] ;	
	int n1=1, n2=2, n3=3, n4=4, n5=5;
	
	numbers[0]=&n1;
	numbers[1]=&n2;
	numbers[2]=&n3;
	numbers[3]=&n4;
	numbers[4]=&n5;

	ASSERT_THAT(Vector_Remove(NULL,(void**)&item)==VECTOR_UNITIALIZED_ERROR);
	
	ASSERT_THAT((vec=Vector_Create(5,1))!=NULL);

	ASSERT_THAT(Vector_Remove(vec,NULL)==VECTOR_UNITIALIZED_ERROR);
	
	ASSERT_THAT(Vector_Get(vec,1,NULL)==VECTOR_UNITIALIZED_ERROR);
	
	for (i=0 ; i<5 ; ++i)
	{
		ASSERT_THAT(Vector_Append(vec,numbers[i])==VECTOR_SUCCESS);		
	}
	
	for (i=5 ; i>=1 ; --i)
	{
		ASSERT_THAT((Vector_Remove(vec,(void**)&item)==VECTOR_SUCCESS)&&(*item==i));

	}
	
	ASSERT_THAT(Vector_Remove(vec,(void**)&item)==VECTOR_UNDERFLOW);

	Vector_Destroy(&vec,NULL);
END_UNIT


TEST_SUITE(Vector Tests)

	TEST(Vector_CreateTest)	

	TEST(Vector_AppendTest_Params)
	
	TEST(Vector_AppendTest_Normal)
	
	TEST(Vector_DestroyTest)
	
	TEST(Vector_SizeTest)

	TEST(VectorGetTest)
	
	TEST(Vector_SetTest)
	
	TEST(Vector_RemoveTest)

END_SUITE




