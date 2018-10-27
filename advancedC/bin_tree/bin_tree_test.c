
/** 
 *  @file bin_tree_test.c
 *  @brief Tests for API a binary search tree(BST) container
 *	
 *  @details  See the tests names.
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug No known bugs! 
 */



#include "bin_tree.h"
#include "../mu_test.h"
#include <stdio.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif


static int IsLessInt(void * _element, void* _context)
{
	return *(int*)_element < *(int*)_context;
}



int IsIntBST(BSTree* _tree)
{
	BSTreeItr curr;
	
	curr = BSTreeItr_Begin(_tree);
	
	if(BSTreeItr_Equals(BSTreeItr_End(_tree),curr))
	{
		return TRUE;
	}
	
	while(!BSTreeItr_Equals(BSTreeItr_End(_tree),BSTreeItr_Next(curr)))
	{
		if (IsLessInt(BSTreeItr_Get(BSTreeItr_Next(curr)),BSTreeItr_Get(curr)))
		{
			return FALSE;
		}
		curr=BSTreeItr_Next(curr);
	}
	return TRUE;
}



UNIT(BSTCreateTest)

	BSTree *tree1, *tree2;

	ASSERT_THAT((tree1=BSTree_Create(IsLessInt))!=NULL);
	
	tree2 = tree1;
	
	BSTree_Destroy(tree1,NULL);
	
	/*double destroy test*/
	BSTree_Destroy(tree1,NULL);
	BSTree_Destroy(tree2,NULL);

END_UNIT

static int PrintInt(void * _element, void* _context)
{
	printf("%d ",*(int*)_element);
	return TRUE;
}

UNIT(BSTree_InsertNormal)

	int i,data[10]={1,10,4,3,9,6,8,7,5,2};
	BSTree* tree1;

	ASSERT_THAT((tree1=BSTree_Create(IsLessInt))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(BSTree_Insert(tree1,&data[10-i])!=NULL);	
		ASSERT_THAT(IsIntBST(tree1));
		ASSERT_THAT(BSTree_ForEach(tree1,BSTREE_TRAVERSAL_INORDER,PrintInt,NULL) == BSTreeItr_End(tree1));
		printf("\n");
	}
	/*
	ASSERT_THAT(BSTree_ForEach(tree1,BSTREE_TRAVERSAL_INORDER,PrintInt,NULL) == BSTreeItr_End(tree1));
	printf("\n");
	*/
	BSTree_Destroy(tree1,NULL);

END_UNIT

UNIT(BSTreeItr_RemoveNormal)

	int i,data[10]={1,10,4,3,9,6,8,7,5,2};
	BSTree* tree1;
	BSTreeItr itr,itr2;

	ASSERT_THAT((tree1=BSTree_Create(IsLessInt))!=NULL);
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(BSTree_Insert(tree1,&data[10-i])!=NULL);	
		ASSERT_THAT(IsIntBST(tree1));
	}
	
	ASSERT_THAT(BSTree_ForEach(tree1,BSTREE_TRAVERSAL_INORDER,PrintInt,NULL) == BSTreeItr_End(tree1));
	printf("\n");
	
	itr=BSTreeItr_Begin(tree1);
	
	printf("begin is %d \n",*(int*)BSTreeItr_Get(itr));
	
	for (i=1 ; i<=10 ; ++i)
	{
		itr2 = BSTreeItr_Next(itr);
		
		ASSERT_THAT(*(int*)BSTreeItr_Remove(itr) == i);	
		ASSERT_THAT(IsIntBST(tree1));
		ASSERT_THAT(BSTree_ForEach(tree1,BSTREE_TRAVERSAL_INORDER,PrintInt,NULL) == BSTreeItr_End(tree1));
		printf("\n");
		
		itr=itr2;		
	}
	
	for (i=1 ; i<=10 ; ++i)
	{
		ASSERT_THAT(BSTree_Insert(tree1,&data[10-i])!=NULL);	
		ASSERT_THAT(IsIntBST(tree1));
	}
	
	ASSERT_THAT(BSTree_ForEach(tree1,BSTREE_TRAVERSAL_INORDER,PrintInt,NULL) == BSTreeItr_End(tree1));
	printf("\n");
	
	itr=BSTreeItr_Prev(BSTreeItr_End(tree1));
	
	printf("one before begin is %d \n",*(int*)BSTreeItr_Get(itr));
	
	for (i=1 ; i<=10 ; ++i)
	{
		itr2 = BSTreeItr_Prev(itr);
		
		ASSERT_THAT(*(int*)BSTreeItr_Remove(itr) == 10-i+1);	
		ASSERT_THAT(IsIntBST(tree1));
		ASSERT_THAT(BSTree_ForEach(tree1,BSTREE_TRAVERSAL_INORDER,PrintInt,NULL) == BSTreeItr_End(tree1));
		printf("\n");
		
		itr=itr2;		
	}
	
	BSTree_Destroy(tree1,NULL);
	
END_UNIT


TEST_SUITE(BST Tests)

	/*BST functions tests*/
	
	TEST(BSTCreateTest)
	TEST(BSTree_InsertNormal)
	TEST(BSTreeItr_RemoveNormal)
	
/*
	
	TEST(ListDestroyTestNormal)
	
Iterator over Lists basic functions tests	
	
	TEST(ListItr_BeginNormal)
	TEST(ListItr_EndNormal)
	
	TEST(ListItr_Next_PrevNormal)
	
	TEST(ListItr_Get_SetNormal)


functions for Iterators over Lists tests

	TEST(ListItr_FindFirstParams)
	TEST(ListItr_FindFirstNormal)
	
	TEST(ListItr_ForEachParams)
	TEST(ListItr_ForEachNormal)

*/
END_SUITE













