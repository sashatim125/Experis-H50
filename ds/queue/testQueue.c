/*This file contains the main=test for queue.h API.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#include "queue.h"
#include "../mu_test.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

UNIT(QueueCreateTestNormal)

	Queue *q;
	
	ASSERT_THAT((q=QueueCreate(10))!=NULL);
	QueueDestroy(q);
	
END_UNIT

UNIT(QueueCreateTestZeroSize)	

	ASSERT_THAT(QueueCreate(0)==NULL);

END_UNIT

UNIT(QueueCreateTestHugeSize)

	ASSERT_THAT(QueueCreate(ULONG_MAX-50)==NULL);

END_UNIT

UNIT(QueueInsertTestParams)

	Queue *q;

	ASSERT_THAT(QueueInsert(NULL,1)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((q=QueueCreate(1))!=NULL);
	ASSERT_THAT((QueueInsert(q,1)==ERR_OK)&&(QueueInsert(q,2)==ERR_OVERFLOW));
	
	QueueDestroy(q);
	
END_UNIT

UNIT(QueueInsertTestOverflow)
	
	Queue *q;
	int i;	
	
	ASSERT_THAT((q=QueueCreate(10))!=NULL);

	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(QueueInsert(q,i)==ERR_OK);		
	}
	ASSERT_THAT(QueueInsert(q,i)==ERR_OVERFLOW);
	QueueDestroy(q);
END_UNIT


UNIT(QueueIsEmptyTestParams)

	ASSERT_THAT(QueueIsEmpty(NULL)==TRUE);
	
END_UNIT

UNIT(QueueIsEmptyTestNormal)	

	Queue *q;
	int i,k;

	ASSERT_THAT((q=QueueCreate(10))!=NULL);	
	
	ASSERT_THAT(QueueIsEmpty(q)==TRUE);

	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(QueueInsert(q,i)==ERR_OK);
	}
	ASSERT_THAT(QueueIsEmpty(q)==FALSE);
	
	for (i=10; i>0 ; --i)
	{
		ASSERT_THAT(QueueRemove(q,&k)==ERR_OK);
	}
	ASSERT_THAT(QueueIsEmpty(q)==TRUE);
	
	QueueDestroy(q);
END_UNIT


UNIT(QueueRemoveTestParams)
	
	Queue *q;
	int item;

	ASSERT_THAT(QueueRemove(NULL,&item)==ERR_NOT_INITIALIZED);
	
	ASSERT_THAT((q=QueueCreate(10))!=NULL);

	ASSERT_THAT(QueueRemove(q,NULL)==ERR_NOT_INITIALIZED);
	
	QueueDestroy(q);
END_UNIT	

UNIT(QueueRemoveTestUnderflow)	
	
	Queue *q;
	int item;
	
	ASSERT_THAT((q=QueueCreate(10))!=NULL);
	
	ASSERT_THAT(QueueRemove(q,&item)==ERR_UNDERFLOW);

	QueueDestroy(q);
END_UNIT

UNIT(QueueRemoveTestNormal)	
	
	Queue *q;	
	int i,item;
	
	ASSERT_THAT((q=QueueCreate(10))!=NULL);
	
	for (i=0 ; i<10 ; ++i)
	{
		ASSERT_THAT(QueueInsert(q,i)==ERR_OK);
	}
	for (i=0 ; i<=9 ; ++i)
	{
		ASSERT_THAT((QueueRemove(q,&item)==ERR_OK)&&(item==i));

	}

	QueueDestroy(q);
END_UNIT

UNIT(QueueInsertRemoveTestNormal)	
	
	Queue *q;	
	int i,j,item;
	
	ASSERT_THAT((q=QueueCreate(10))!=NULL);
	j=SHRT_MAX;
	
	for (i=0 ; i<5 ; ++i)
		{
			ASSERT_THAT(QueueInsert(q,i)==ERR_OK);
		}
	
	
	while(j--)
	{
		for (i=0 ; i<5 ; ++i)
		{
			ASSERT_THAT(QueueInsert(q,i)==ERR_OK);
		}
		for (i=0 ; i<=4 ; ++i)
		{
			ASSERT_THAT((QueueRemove(q,&item)==ERR_OK)&&(item==i));
		}
	}

	QueueDestroy(q);
END_UNIT


TEST_SUITE(Vector Tests)

	TEST(QueueCreateTestNormal)
	TEST(QueueCreateTestZeroSize)
	TEST(QueueCreateTestHugeSize)
	
	TEST(QueueInsertTestParams)
	TEST(QueueInsertTestOverflow)
	
	TEST(QueueIsEmptyTestParams)
	TEST(QueueIsEmptyTestNormal)
	
	TEST(QueueRemoveTestParams)
	TEST(QueueRemoveTestUnderflow)
	TEST(QueueRemoveTestNormal)	
	
	TEST(QueueInsertRemoveTestNormal)
	
	


END_SUITE




