
/** 
 *  @file hashTest.c
 *  @brief Tests for API for the hash table (data == ints)
 *	
 *  @details  See the tests names.
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug None! 
 */

#include "hash.h"
#include "../mu_test.h"
#include <stdio.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

/*
static void userFunction(size_t _data)
{
	printf("%lu ",_data);
}
*/
static size_t hashFunction(size_t _data)
{
	return(_data/3);
}

UNIT(HashSetCreateParams)

	ASSERT_THAT(HashSetCreate(5lu,0.7f,NULL)==NULL);
	ASSERT_THAT(HashSetCreate(0lu,0.7f,hashFunction)==NULL);
	
END_UNIT

UNIT(HashSetCreateNormal)

	HashSet* set;
	size_t i;
	
	ASSERT_THAT((set=HashSetCreate(25lu,1.0f,hashFunction))!=NULL);
	
	for (i=501; i<=510 ; ++i)
	{
		ASSERT_THAT(HashSetAdd(set,i)==ERR_OK);
		ASSERT_THAT(HashSetContains(set,i));		
	}
	
	ASSERT_THAT(HashSetSize(set)==10);
	/*
	HashSetForEach(set,userFunction);
	putchar('\n');
	*/
	for (i=501; i<=510 ; ++i)
	{
		ASSERT_THAT(HashSetRemove(set,i)==ERR_OK);
		/*
		HashSetForEach(set,userFunction);
		putchar('\n');
		*/
		ASSERT_THAT(!HashSetContains(set,i));
	}

	HashSetDestroy(set);
	HashSetDestroy(set);

END_UNIT

UNIT(HashSetAddParams)

	ASSERT_THAT(HashSetAdd(NULL,5lu)==ERR_NOT_INITIALIZED);
	
END_UNIT

UNIT(HashSetAddNormal)

	HashSet* set;
	size_t i;
	
	ASSERT_THAT((set=HashSetCreate(25lu,1.0f,hashFunction))!=NULL);
	
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetAdd(set,i)==ERR_OK);
		ASSERT_THAT(HashSetContains(set,i));		
	}
	
	ASSERT_THAT(HashSetSize(set)==25);
	/*
	HashSetForEach(set,userFunction);
	putchar('\n');
	*/
	ASSERT_THAT(HashSetAdd(set,750)==ERR_OVERFLOW);
	
	ASSERT_THAT(HashSetRemove(set,525)==ERR_OK);	
	
	for (i=501 ; i<=524 ; ++i)
	{
		ASSERT_THAT(HashSetAdd(set,i)==ERR_ALREADY_EXISTS);		
	}
		
	/*
	HashSetForEach(set,userFunction);
	putchar('\n');
	*/
	for (i=501; i<=524 ; ++i)
	{
		ASSERT_THAT(HashSetRemove(set,i)==ERR_OK);
		/*
		HashSetForEach(set,userFunction);
		putchar('\n');
		*/
		ASSERT_THAT(!HashSetContains(set,i));
	}


	HashSetDestroy(set);

END_UNIT

UNIT(HashSetRemoveParams)

	ASSERT_THAT(HashSetRemove(NULL,5lu)==ERR_NOT_INITIALIZED);
	
END_UNIT

UNIT(HashSetRemoveNormal)

	HashSet* set;
	size_t i;
	
	ASSERT_THAT((set=HashSetCreate(25lu,1.0f,hashFunction))!=NULL);
	
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetAdd(set,i)==ERR_OK);		
	}
	
	ASSERT_THAT(HashSetRemove(set,525)==ERR_OK);	
	ASSERT_THAT(HashSetRemove(set,524)==ERR_OK);
	
	ASSERT_THAT(HashSetSize(set)==23);
	/*
	HashSetForEach(set,userFunction);
	putchar('\n');
	*/
	ASSERT_THAT(HashSetAdd(set,525)==ERR_OK);
	ASSERT_THAT(HashSetAdd(set,524)==ERR_OK);	
		
	/*
	HashSetForEach(set,userFunction);
	putchar('\n');
	*/
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetRemove(set,i)==ERR_OK);
		ASSERT_THAT(!HashSetContains(set,i));
	}

	/*
	HashSetForEach(set,userFunction);
	putchar('\n');
	*/
	HashSetDestroy(set);

END_UNIT

UNIT(HashSetContainsParams)

	ASSERT_THAT(HashSetContains(NULL,5)==0);
	
END_UNIT

UNIT(HashSetSizesParams)

	ASSERT_THAT(HashSetSize(NULL)==0);
	
END_UNIT

UNIT(HashSetSizeNormal)

	HashSet* set;
	size_t i;
	
	ASSERT_THAT((set=HashSetCreate(100lu,1.0f,hashFunction))!=NULL);
	
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetAdd(set,i)==ERR_OK);		
	}
	
	ASSERT_THAT(HashSetSize(set)==25);
	
	ASSERT_THAT(HashSetRemove(set,525)==ERR_OK);	
	ASSERT_THAT(HashSetRemove(set,524)==ERR_OK);
	
	ASSERT_THAT(HashSetSize(set)==23);

	ASSERT_THAT(HashSetAdd(set,525)==ERR_OK);
	ASSERT_THAT(HashSetAdd(set,524)==ERR_OK);	
		
	ASSERT_THAT(HashSetSize(set)==25);
	
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetRemove(set,i)==ERR_OK);
		ASSERT_THAT(!HashSetContains(set,i));
	}


	ASSERT_THAT(HashSetSize(set)==0);

	HashSetDestroy(set);

END_UNIT

UNIT(HashSetStatisticsParams)

	HashSet* set;
	size_t a;
	float b;
	
	ASSERT_THAT((set=HashSetCreate(100lu,1.0f,hashFunction))!=NULL);

	ASSERT_THAT(HashSetStatistics(NULL,&a,&b)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT(HashSetStatistics(set,NULL,&b)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT(HashSetStatistics(set,&a,NULL)==ERR_NOT_INITIALIZED);
	
	HashSetDestroy(set);

END_UNIT

UNIT(HashSetStatisticsNormal)

	HashSet* set;
	size_t i;
	size_t a,a1;
	float b,b1;
	
	ASSERT_THAT((set=HashSetCreate(100lu,1.0f,hashFunction))!=NULL);
	
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetAdd(set,i)==ERR_OK);		
	}
	
	ASSERT_THAT((HashSetStatistics(set,&a,&b)==ERR_OK)&&(a>=0)&&(b>=0));
	
	ASSERT_THAT(HashSetRemove(set,525)==ERR_OK);	
	ASSERT_THAT(HashSetRemove(set,524)==ERR_OK);
	
	ASSERT_THAT((HashSetStatistics(set,&a1,&b1)==ERR_OK)&&(a1>=a)&&(b1>=b));

	ASSERT_THAT(HashSetAdd(set,525)==ERR_OK);
	ASSERT_THAT(HashSetAdd(set,524)==ERR_OK);	
		
	ASSERT_THAT(HashSetSize(set)==25);
	
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetRemove(set,i)==ERR_OK);
		ASSERT_THAT(!HashSetContains(set,i));
	}


	ASSERT_THAT((HashSetStatistics(set,&a,&b)==ERR_OK)&&(a>=a1)&&(b>=b1));

	HashSetDestroy(set);

END_UNIT


static size_t counter;

static void countFunction(size_t _data)
{
	++counter;
}


UNIT(HashSetForEachNormal)

	HashSet* set;
	size_t i;
	
	ASSERT_THAT((set=HashSetCreate(25lu,1.0f,hashFunction))!=NULL);
	
	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetAdd(set,i)==ERR_OK);		
	}
	
	ASSERT_THAT(HashSetRemove(set,525)==ERR_OK);	
	ASSERT_THAT(HashSetRemove(set,524)==ERR_OK);
	
	counter = 0;
	HashSetForEach(set,countFunction);
	ASSERT_THAT(HashSetSize(set)==counter);

	ASSERT_THAT(HashSetAdd(set,525)==ERR_OK);
	ASSERT_THAT(HashSetAdd(set,524)==ERR_OK);	
	
	counter = 0;
	HashSetForEach(set,countFunction);
	ASSERT_THAT(HashSetSize(set)==counter);
	
	ASSERT_THAT(HashSetSize(set)==counter);

	for (i=501; i<=525 ; ++i)
	{
		ASSERT_THAT(HashSetRemove(set,i)==ERR_OK);
		ASSERT_THAT(!HashSetContains(set,i));
	}

	counter = 0;
	HashSetForEach(set,countFunction);
	ASSERT_THAT(HashSetSize(set)==counter);
	
	HashSetDestroy(set);

END_UNIT

TEST_SUITE(HashTests)

	TEST(HashSetCreateParams)
	TEST(HashSetCreateNormal)

	TEST(HashSetAddParams)
	TEST(HashSetAddNormal)
	
	TEST(HashSetRemoveParams)
	TEST(HashSetRemoveNormal)
	
	TEST(HashSetContainsParams)
	
	TEST(HashSetSizesParams)
	TEST(HashSetSizeNormal)
	
	TEST(HashSetStatisticsParams)
	TEST(HashSetStatisticsNormal)
	
	TEST(HashSetForEachNormal)
	

END_SUITE













