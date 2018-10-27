
#include "bst.h"
#include "../mu_test.h"


/** 
 *  @file bsttest.c
 *  @brief Tests for API for the binary search tree (data == ints)
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

UNIT(TreeCreateTest)

	Tree* newTree;

	ASSERT_THAT((newTree=TreeCreate())!=NULL);
	
	TreeDestroy(newTree);
END_UNIT

UNIT(TreeInsertTestParams)
	
	ASSERT_THAT(TreeInsert(NULL,5)==ERR_NOT_INITIALIZED);
	
END_UNIT

UNIT(TreeInsertFindTestNormal)

	Tree* newTree;

	ASSERT_THAT((newTree=TreeCreate())!=NULL);
	
	
	ASSERT_THAT(TreeInsert(newTree,5)==ERR_OK);
	ASSERT_THAT(TreeIsDataFound(newTree,5));
	
	
	ASSERT_THAT(TreeInsert(newTree,3)==ERR_OK);
	ASSERT_THAT(TreeIsDataFound(newTree,3));

	ASSERT_THAT(TreeInsert(newTree,7)==ERR_OK);
	ASSERT_THAT(TreeIsDataFound(newTree,7));
	
	ASSERT_THAT(TreeInsert(newTree,2)==ERR_OK);
	ASSERT_THAT(TreeIsDataFound(newTree,2));
	
	ASSERT_THAT(TreeInsert(newTree,4)==ERR_OK);
	ASSERT_THAT(TreeIsDataFound(newTree,4));
	
	ASSERT_THAT(TreeInsert(newTree,6)==ERR_OK);	
	ASSERT_THAT(TreeIsDataFound(newTree,6));
	
	TreePrint(newTree,PRE_ORDER);
	TreePrint(newTree,IN_ORDER);
	TreePrint(newTree,POST_ORDER);

	ASSERT_THAT(TreeInsert(newTree,6)==ERR_DATA_DUPLICATION);	
	ASSERT_THAT(TreeInsert(newTree,7)==ERR_DATA_DUPLICATION);
	
	TreeDestroy(newTree);
END_UNIT


TEST_SUITE(BstTests)

	TEST(TreeCreateTest)

	TEST(TreeInsertTestParams)
	TEST(TreeInsertFindTestNormal)

END_SUITE



 
 


