
/** 
 *  @file list_test.c
 *  @brief Tests for API for the double linked list (data==void*)
 *	
 *  @details  See the tests names.
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug No known bugs! 
 */



#include "list.h"
#include "list_itr.h"
#include "list_functions.h"
#include "../mu_test.h"

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif


/*List basic functions tests*/

UNIT(ListCreateTest)

	List* newList, *list2;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	list2 = newList;
	
	List_Destroy(&newList,NULL);
	
	/*double destroy test*/
	List_Destroy(&newList,NULL);
	List_Destroy(&list2,NULL);

END_UNIT


UNIT(ListPushHeadTestParams)

	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	ASSERT_THAT(List_PushHead(NULL,(void*)0)==LIST_UNINITIALIZED_ERROR);
	
	List_Destroy(&newList,NULL);

END_UNIT

int	checkIntElem(void* _element, void* _context)
{
	return (*(int*)_element)!=0;
}

UNIT(ListPushHeadTestsNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	void *item;
	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushHead(newList,&data[10-i])==LIST_SUCCESS);		
	}
	
	ASSERT_THAT(List_ForEach(newList,checkIntElem,NULL) == ListItr_End(newList));

	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT((List_PopHead(newList,(void**)&item)==LIST_SUCCESS)&&(*(int*)item==10-i+1));		
	}
	

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListPushTailTestParams)

	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	ASSERT_THAT(List_PushTail(NULL,(void*)0)==LIST_UNINITIALIZED_ERROR);
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListPushTailTestsNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	void *item;
	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushTail(newList,&data[i-1])==LIST_SUCCESS);		
	}
	
	ASSERT_THAT(List_ForEach(newList,checkIntElem,NULL) == ListItr_End(newList));

	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT((List_PopHead(newList,(void**)&item)==LIST_SUCCESS)&&(*(int*)item==i));		
	}
	
	List_Destroy(&newList,NULL);

END_UNIT


UNIT(ListIsEmptyTestParams)

	ASSERT_THAT(List_IsEmpty(NULL));
	
END_UNIT

UNIT(ListIsEmptyTestNormal)	

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	void *item;
	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushTail(newList,&data[i-1])==LIST_SUCCESS);		
	}
	
	ASSERT_THAT(!List_IsEmpty(newList));

	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT((List_PopHead(newList,(void**)&item)==LIST_SUCCESS)&&(*(int*)item==i));		
	}

	ASSERT_THAT(List_IsEmpty(newList));

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(List_SizeTestParams)

	ASSERT_THAT( List_Size(NULL)==0);
	
END_UNIT

UNIT(List_SizeTestNormal)	

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	void *item;
	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushTail(newList,&data[i-1])==LIST_SUCCESS);
		ASSERT_THAT(List_Size(newList)==i);		
	}
	
	ASSERT_THAT(!List_IsEmpty(newList));
	ASSERT_THAT( List_Size(newList)==10);

	for (i=10; i>=1 ; --i)
	{
		ASSERT_THAT((List_PopHead(newList,(void**)&item)==LIST_SUCCESS));
		ASSERT_THAT(List_Size(newList)==i-1);		
	}
	
	ASSERT_THAT( List_Size(newList)==0);

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListPopHeadTestParams)

	void *item;
	List* newList;
	
	ASSERT_THAT((newList=List_Create())!=NULL);

	ASSERT_THAT(List_PopHead(NULL,&item)==LIST_UNINITIALIZED_ERROR);
	
	ASSERT_THAT(List_PushHead(newList,(void*)1)==LIST_SUCCESS);

	ASSERT_THAT(List_PopHead(newList,NULL)==LIST_UNINITIALIZED_ERROR);
	
	ASSERT_THAT((List_PopHead(newList,&item)==LIST_SUCCESS)&&((void*)1==item));

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListPopHeadTestNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	void *item;
	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushTail(newList,&data[i-1])==LIST_SUCCESS);		
	}

	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT((List_PopHead(newList,&item)==LIST_SUCCESS)&&(*(int*)item==i));		
	}
	
	ASSERT_THAT(List_PopHead(newList,&item)==LIST_UNDERFLOW);

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListPopTailTestParams)

	void *item;
	List* newList;
	
	ASSERT_THAT((newList=List_Create())!=NULL);

	ASSERT_THAT(List_PopTail(NULL,&item)==LIST_UNINITIALIZED_ERROR);
	
	ASSERT_THAT(List_PushHead(newList,(void*)1)==LIST_SUCCESS);

	ASSERT_THAT(List_PopTail(newList,NULL)==LIST_UNINITIALIZED_ERROR);
	
	ASSERT_THAT((List_PopTail(newList,&item)==LIST_SUCCESS)&&((void*)1==item));

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListPopTailTestNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	void *item;
	List* newList;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushTail(newList,&data[i-1])==LIST_SUCCESS);		
	}

	for (i=10; i>=1 ; --i)
	{
		ASSERT_THAT((List_PopTail(newList,&item)==LIST_SUCCESS)&&(*(int*)item==i));		
	}
	
	ASSERT_THAT(List_PopTail(newList,&item)==LIST_UNDERFLOW);

	List_Destroy(&newList,NULL);

END_UNIT

static void MyListDestroy(void* _list)
{
	List_Destroy((List**)&_list,NULL);
}

UNIT(ListDestroyTestNormal)

	int i ;
	List *newList, *listArr[10];

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT((listArr[i]=List_Create())!=NULL);	
		ASSERT_THAT(List_PushTail(newList,listArr[i])==LIST_SUCCESS);		
	}

	List_Destroy(&newList,MyListDestroy);
	
	listArr[0]=newList;
	List_Destroy(&newList,NULL);
	List_Destroy(&listArr[0],NULL);
	List_Destroy(NULL,NULL);

END_UNIT

/*Iterator over Lists basic functions tests*/

UNIT(ListItr_BeginNormal)

	List* newList;
	int num=5;

	ASSERT_THAT(ListItr_Begin(NULL)==NULL);
	
	ASSERT_THAT((newList=List_Create())!=NULL);

	ASSERT_THAT(ListItr_Equals(ListItr_Next(ListItr_Begin(newList)),ListItr_Begin(newList)));
	
	ASSERT_THAT(ListItr_Get(ListItr_Begin(newList))==NULL);
	
	ASSERT_THAT(List_PushTail(newList,&num)==LIST_SUCCESS);
	
	ASSERT_THAT(*(int*)ListItr_Get(ListItr_Begin(newList))==num);
	
	ASSERT_THAT(ListItr_Equals(ListItr_Next(ListItr_Begin(newList)),ListItr_End(newList)));

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_EndNormal)

	List* newList;
	int num=5;
	
	ASSERT_THAT(ListItr_End(NULL)==NULL);

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	ASSERT_THAT(ListItr_Equals(ListItr_Next(ListItr_End(newList)),ListItr_End(newList)));
	
	ASSERT_THAT(ListItr_Get(ListItr_End(newList))==NULL);
	
	ASSERT_THAT(List_PushTail(newList,&num)==LIST_SUCCESS);
	
	ASSERT_THAT(*(int*)ListItr_Get(ListItr_Prev(ListItr_End(newList)))==num);
	
	ASSERT_THAT(ListItr_Equals(ListItr_Next(ListItr_Begin(newList)),ListItr_End(newList)));

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_Next_PrevNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	List* newList;
	ListItr curr;

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	ASSERT_THAT(ListItr_Equals(ListItr_Prev(ListItr_Prev(ListItr_Begin(newList))),\
		ListItr_Prev(ListItr_End(newList))));
	
	ASSERT_THAT(ListItr_Equals(ListItr_Next(ListItr_Begin(newList)),ListItr_End(newList)));

	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushTail(newList,&data[i-1])==LIST_SUCCESS);		
	}
	

	for (curr=ListItr_Begin(newList) ,i=1 ; curr != ListItr_End(newList) ; curr = ListItr_Next(curr) , ++i)
	{
		ASSERT_THAT(*(int*)(ListItr_Get(curr))==data[i-1]);	
	}
	
	for (curr=ListItr_Prev(ListItr_End(newList)) ,i=10 ; curr != ListItr_Prev(curr) ; curr = ListItr_Prev(curr) , --i)
	{
		ASSERT_THAT(*(int*)(ListItr_Get(curr))==data[i-1]);
	}

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_Get_SetNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	List* newList;
	ListItr iterator;
	

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(List_PushTail(newList,(void*)1)==LIST_SUCCESS);		
	}
	;
	iterator = ListItr_Begin(newList);
	
	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(ListItr_Set(iterator,&data[i-1])==(void*)1);		
	}
	
	iterator = ListItr_Begin(newList);
	
	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data[i-1]);		
	}

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_InsertBeforeNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	List* newList;
	ListItr iterator;
	
	ASSERT_THAT(ListItr_InsertBefore(NULL,(void*)1)==NULL);	

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_End(newList);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	
	iterator = ListItr_Begin(newList);
	
	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data[i-1]);		
	}

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_ListItr_RemoveNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	List* newList;
	ListItr iterator;
	
	ASSERT_THAT(ListItr_Remove(NULL)==NULL);	

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	ASSERT_THAT(ListItr_Remove(ListItr_Begin(newList))==NULL);
	
	iterator = ListItr_End(newList);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	
	iterator = ListItr_Begin(newList);
	
	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Remove(iterator))==data[i-1]);		
	}
	
	ASSERT_THAT(ListItr_Equals(ListItr_Begin(newList),ListItr_End(newList)));

	List_Destroy(&newList,NULL);

END_UNIT

/*functions for Iterators over Lists tests*/

static int IsIntEqual(void * _element, void* _context)
{
	return *(int*)_element == *(int*)_context;
}

static int IsNotIntEqual(void * _element, void* _context)
{
	return *(int*)_element != *(int*)_context;
}

static int IsLessInt(void * _element, void* _context)
{
	return *(int*)_element < *(int*)_context;
}

/*
static int IntPrint(void * _element, void* _context)
{
	printf("%d ",*(int*)_element);
	return 1;
}
*/

UNIT(ListItr_FindFirstParams)

	List* newList;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ASSERT_THAT(ListItr_FindFirst(NULL,iterator,IsIntEqual,(void*)1)==NULL);
	
	ASSERT_THAT(ListItr_FindFirst(iterator,NULL,IsIntEqual,(void*)1)==NULL);
	
	ASSERT_THAT(ListItr_FindFirst(iterator,iterator,NULL,NULL)==NULL);	
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_FindFirstNormal)

	int i,data[10]={1,2,3,4,5,5,7,8,9,10};
	List* newList;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	
	i=5;
	ASSERT_THAT(*(int*)ListItr_Get(ListItr_FindFirst(ListItr_Begin(newList),\
		ListItr_End(newList),IsIntEqual,&i))==i);
		
	i=7;
	ASSERT_THAT(*(int*)ListItr_Get(ListItr_FindFirst(ListItr_Begin(newList),\
		ListItr_End(newList),IsIntEqual,&i))==i);
		
	i=15;
	ASSERT_THAT(ListItr_FindFirst(ListItr_Begin(newList),\
		ListItr_End(newList),IsIntEqual,&i)==ListItr_End(newList));

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_ForEachParams)

	List* newList;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ASSERT_THAT(ListItr_ForEach(NULL,iterator,IsIntEqual,(void*)1)==NULL);
	
	ASSERT_THAT(ListItr_ForEach(iterator,NULL,IsIntEqual,(void*)1)==NULL);
	
	ASSERT_THAT(ListItr_ForEach(iterator,iterator,NULL,NULL)==NULL);	
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_ForEachNormal)

	int i,data[10]={1,1,1,1,5,5,7,8,9,10};
	List* newList;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	
	i=1;
	ASSERT_THAT(*(int*)ListItr_Get(ListItr_ForEach(ListItr_Begin(newList),\
		ListItr_End(newList),IsIntEqual,&i))==5);
	
	i=0;
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList),\
		ListItr_End(newList),IsNotIntEqual,&i)==ListItr_End(newList));

	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_CountIfParams)

	List* newList;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ASSERT_THAT(ListItr_CountIf(NULL,iterator,IsIntEqual,(void*)1)==0);
	
	ASSERT_THAT(ListItr_CountIf(iterator,NULL,IsIntEqual,(void*)1)==0);
	
	ASSERT_THAT(ListItr_CountIf(iterator,iterator,NULL,NULL)==0);	
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_CountIfNormal)

	int i,data[10]={1,1,1,1,5,5,7,8,9,10};
	List* newList;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	
	i=1;
	ASSERT_THAT(ListItr_CountIf(ListItr_Begin(newList),\
		ListItr_End(newList),IsIntEqual,&i)==4);
	
	i=0;
	ASSERT_THAT(ListItr_CountIf(ListItr_Begin(newList),\
		ListItr_End(newList),IsNotIntEqual,&i)==10);

	List_Destroy(&newList,NULL);

END_UNIT


UNIT(ListItr_SortParams)

	List* newList;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ListItr_Sort(NULL,iterator,IsIntEqual);
	
	ListItr_Sort(iterator,NULL,IsIntEqual);
	
	ListItr_Sort(iterator,iterator,NULL);	
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_SortNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	List* newList;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList),\
		ListItr_End(newList),IntPrint,NULL)==ListItr_End(newList));
	*/
	ListItr_Sort(ListItr_Begin(newList),ListItr_End(newList),IsLessInt);
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList),\
		ListItr_End(newList),IntPrint,NULL)==ListItr_End(newList));
	*/
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList),ListItr_End(newList),IsLessInt));

	List_Destroy(&newList,NULL);

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	
	ListItr_Sort(ListItr_Begin(newList),ListItr_End(newList),IsLessInt);
	
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList),ListItr_End(newList),IsLessInt));
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_SpliceParams)

	List* newList;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ASSERT_THAT(ListItr_Splice(NULL,iterator,iterator)==NULL);
	
	ASSERT_THAT(ListItr_Splice(iterator,NULL,iterator)==NULL);
	
	ASSERT_THAT(ListItr_Splice(iterator,iterator,NULL)==NULL);	
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_SpliceNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	List *newList,*newList2;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);
	ASSERT_THAT((newList2=List_Create())!=NULL);	
	
	
	iterator = ListItr_End(newList);
	
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	/*
	ListItr_ForEach(ListItr_Begin(newList),ListItr_End(newList),IntPrint,NULL);
	*/
	ASSERT_THAT(ListItr_Splice(ListItr_End(newList2),ListItr_Begin(newList),ListItr_End(newList))==ListItr_Begin(newList2));
	/*
	ListItr_ForEach(ListItr_Begin(newList2),ListItr_End(newList2),IntPrint,NULL);
	*/
	
	ASSERT_THAT(!ListItr_IsSorted(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt));
	
	ListItr_Sort(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt);
	
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt));
	
	iterator = ListItr_Begin(newList2);
	
	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data[i-1]);		
	}
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList2),\
		ListItr_End(newList2),IntPrint,NULL)==ListItr_End(newList2));
	*/
	List_Destroy(&newList,NULL);
	List_Destroy(&newList2,NULL);

END_UNIT

UNIT(ListItr_CutParams)

	List *newList,*newList2;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ASSERT_THAT(ListItr_Cut(NULL,iterator)==NULL);
	
	ASSERT_THAT(ListItr_Cut(iterator,NULL)==NULL);
	
	ASSERT_THAT((newList2=ListItr_Cut(ListItr_Begin(newList),ListItr_End(newList)))!=NULL);
	
	ASSERT_THAT(ListItr_Equals(ListItr_Begin(newList2),ListItr_End(newList2)));
	
	List_Destroy(&newList,NULL);
	List_Destroy(&newList2,NULL);

END_UNIT

UNIT(ListItr_CutNormal)

	int i,data[10]={1,2,3,4,5,6,7,8,9,10};
	List *newList,*newList2;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data[i-1])!=NULL);		
	}
	/*
	ListItr_ForEach(ListItr_Begin(newList),ListItr_End(newList),IntPrint,NULL);
	*/
	ASSERT_THAT((newList2=ListItr_Cut(ListItr_Begin(newList),ListItr_End(newList)))!=NULL);
	/*
	ListItr_ForEach(ListItr_Begin(newList2),ListItr_End(newList2),IntPrint,NULL);
	*/
	
	ASSERT_THAT(!ListItr_IsSorted(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt));
	
	ListItr_Sort(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt);
	
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt));
	
	iterator = ListItr_Begin(newList2);
	
	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data[i-1]);		
	}
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList2),\
		ListItr_End(newList2),IntPrint,NULL)==ListItr_End(newList2));
	*/
	List_Destroy(&newList,NULL);
	List_Destroy(&newList2,NULL);

END_UNIT

UNIT(ListItr_MergeParams)

	List* newList;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ASSERT_THAT(ListItr_Merge(NULL,iterator,iterator,iterator,iterator,IsLessInt)==NULL);
	
	ASSERT_THAT(ListItr_Merge(iterator,NULL,iterator,iterator,iterator,IsLessInt)==NULL);
	
	ASSERT_THAT(ListItr_Merge(iterator,iterator,NULL,iterator,iterator,IsLessInt)==NULL);
	
	ASSERT_THAT(ListItr_Merge(iterator,iterator,iterator,NULL,iterator,IsLessInt)==NULL);
	
	ASSERT_THAT(ListItr_Merge(iterator,iterator,iterator,iterator,NULL,IsLessInt)==NULL);	
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_MergeNormal)

	int i,data1[10]={1,2,3,4,5,6,7,8,9,10}, data2[5]={11,12,13,14,15};
	List *newList , *newList2, *newList3;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=5 ; i>=1 ; --i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data2[i-1])!=NULL);		
	}
		
	ASSERT_THAT((newList2=ListItr_Cut(ListItr_Begin(newList),ListItr_End(newList)))!=NULL);
	
	ListItr_Sort(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt);
	
	iterator = ListItr_End(newList);
	
	for (i=10 ; i>=1 ; --i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data1[i-1])!=NULL);		
	}
	
	ListItr_Sort(ListItr_Begin(newList),ListItr_End(newList),IsLessInt);
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList),\
		ListItr_End(newList),IntPrint,NULL)==ListItr_End(newList));
	putchar('\n');
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList2),\
		ListItr_End(newList2),IntPrint,NULL)==ListItr_End(newList2));
	putchar('\n');
	fflush(stdout);	
	*/
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList),ListItr_End(newList),IsLessInt));
	
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList2),ListItr_End(newList2),IsLessInt));
	
	ASSERT_THAT((newList3=List_Create())!=NULL);	
	
	ASSERT_THAT(ListItr_Merge(ListItr_End(newList3),ListItr_Begin(newList2),ListItr_End(newList2),\
		ListItr_Begin(newList),ListItr_End(newList),IsLessInt)==ListItr_Begin(newList3));
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList3),\
		ListItr_End(newList3),IntPrint,NULL)==ListItr_End(newList3));
	putchar('\n');
	fflush(stdout);
	*/
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList3),ListItr_End(newList3),IsLessInt));


	iterator = ListItr_Begin(newList3);

	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data1[i-1]);
	}
	
	for (i=1 ; i<=5 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data2[i-1]);
	}
	
	List_Destroy(&newList,NULL);
	List_Destroy(&newList2,NULL);
	List_Destroy(&newList3,NULL);

END_UNIT

UNIT(ListItr_UniqueParams)

	List* newList;
	ListItr iterator;
		

	ASSERT_THAT((newList=List_Create())!=NULL);
	
	iterator = ListItr_Begin(newList);

	ASSERT_THAT(ListItr_Unique(NULL,iterator,IsIntEqual)==NULL);
	
	ASSERT_THAT(ListItr_Unique(iterator,NULL,IsIntEqual)==NULL);
	
	ASSERT_THAT(ListItr_Unique(iterator,iterator,NULL)==NULL);	
	
	List_Destroy(&newList,NULL);

END_UNIT

UNIT(ListItr_UniqueNormal)

	int i,data1[10]={1,2,3,4,5,6,7,8,9,10}, data2[10]={1,2,3,4,5,6,7,8,9,10};
	List *newList , *newList2, *newList3, *newList4;
	ListItr iterator;

	ASSERT_THAT((newList=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data1[i-1])!=NULL);		
	}
	
	ASSERT_THAT((newList2=List_Create())!=NULL);	
	
	iterator = ListItr_End(newList2);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(ListItr_InsertBefore(iterator,&data2[i-1])!=NULL);		
	}	
	
	ASSERT_THAT((newList3=List_Create())!=NULL);	
	
	ASSERT_THAT(ListItr_Merge(ListItr_End(newList3),ListItr_Begin(newList2),ListItr_End(newList2),\
		ListItr_Begin(newList),ListItr_End(newList),IsLessInt)==ListItr_Begin(newList3));
	
	ASSERT_THAT(ListItr_IsSorted(ListItr_Begin(newList3),ListItr_End(newList3),IsLessInt));
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList3),\
		ListItr_End(newList3),IntPrint,NULL)==ListItr_End(newList3));
	putchar('\n');
	fflush(stdout);
	*/
	ASSERT_THAT((newList4=ListItr_Unique(ListItr_Begin(newList3),ListItr_End(newList3),IsIntEqual))!=NULL);
	
	/*
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList3),\
		ListItr_End(newList3),IntPrint,NULL)==ListItr_End(newList3));
	putchar('\n');
	ASSERT_THAT(ListItr_ForEach(ListItr_Begin(newList4),\
		ListItr_End(newList4),IntPrint,NULL)==ListItr_End(newList4));
	putchar('\n');
	fflush(stdout);
	*/
	
	iterator = ListItr_Begin(newList4);

	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data1[i-1]);
	}
	
	iterator = ListItr_Begin(newList3);
	
	for (i=1 ; i<=10 ; ++i, iterator=ListItr_Next(iterator))
	{
		ASSERT_THAT(*(int*)(ListItr_Get(iterator))==data2[i-1]);
	}
	
	List_Destroy(&newList,NULL);
	List_Destroy(&newList2,NULL);
	List_Destroy(&newList3,NULL);
	List_Destroy(&newList4,NULL);

END_UNIT



TEST_SUITE(Linked list Tests)

/*List basic functions tests*/

	TEST(ListCreateTest)
	
	TEST(ListPushHeadTestParams)
	TEST(ListPushHeadTestsNormal)

	TEST(ListPushTailTestParams)
	TEST(ListPushTailTestsNormal)
	
	TEST(ListIsEmptyTestParams)
	TEST(ListIsEmptyTestNormal)	

	TEST(List_SizeTestParams)
	TEST(List_SizeTestNormal)	
	
	TEST(ListPopHeadTestParams)
	TEST(ListPopHeadTestNormal)
	
	TEST(ListPopTailTestParams)
	TEST(ListPopTailTestNormal)
	
	TEST(ListDestroyTestNormal)
	
/*Iterator over Lists basic functions tests*/	
	
	TEST(ListItr_BeginNormal)
	TEST(ListItr_EndNormal)
	
	TEST(ListItr_Next_PrevNormal)
	
	TEST(ListItr_Get_SetNormal)
	
	TEST(ListItr_InsertBeforeNormal)
	
	TEST(ListItr_ListItr_RemoveNormal)

/*functions for Iterators over Lists tests*/

	TEST(ListItr_FindFirstParams)
	TEST(ListItr_FindFirstNormal)
	
	TEST(ListItr_ForEachParams)
	TEST(ListItr_ForEachNormal)

	TEST(ListItr_CountIfParams)
	TEST(ListItr_CountIfNormal)
	
	TEST(ListItr_SortParams)
	TEST(ListItr_SortNormal)
	
	TEST(ListItr_SpliceParams)
	TEST(ListItr_SpliceNormal)
	
	TEST(ListItr_CutParams)
	TEST(ListItr_CutNormal)
	
	TEST(ListItr_MergeParams)
	TEST(ListItr_MergeNormal)
	
	TEST(ListItr_UniqueParams)
	TEST(ListItr_UniqueNormal)	

END_SUITE



 
 


