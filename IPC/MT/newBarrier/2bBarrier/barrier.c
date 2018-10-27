
/** 
 *  @file barrier.c
 *  @brief Barrier API
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stdlib.h>
#include <stdio.h>

#include "barrier.h"
#include "simpleBarrier.h"


#define MAGIC_NUMBER 0xdeafbed


struct Barrier
{
	int m_magicNum;

	SimpleBarrier* m_firstBarrier;
	
	SimpleBarrier* m_secondBarrier;
};


Barrier* Barrier_Create(size_t _capacity)
{
	Barrier* b;
	
	if(0 >=_capacity)
	{
		return NULL;
	}
	if(NULL == (b = malloc(sizeof(Barrier))))
	{
		return NULL;
	}

	if(NULL == (b->m_firstBarrier = SimpleBarrier_Create(_capacity)))
	{
		free(b);
		return NULL;
	}
	if(NULL == (b->m_secondBarrier = SimpleBarrier_Create(_capacity)))
	{
		free(b);
		SimpleBarrier_Destroy(b->m_firstBarrier);
		return NULL;
	}
	
	b->m_magicNum = MAGIC_NUMBER;
	
	return b;
}

void Barrier_Destroy(Barrier* _b)
{
	if(NULL == _b || MAGIC_NUMBER != _b->m_magicNum)
	{
		return;
	}
	_b->m_magicNum = -1;
	
	SimpleBarrier_Destroy(_b->m_secondBarrier);
	SimpleBarrier_Destroy(_b->m_firstBarrier);
	
	free(_b);
}


int Barrier_Wait(Barrier* _b, void(*_callBack)(void*), void* _context)
{
	int res;

	if(_b == NULL || MAGIC_NUMBER != _b->m_magicNum)
	{
		return -1;
	}
	
	res=SimpleBarrier_Wait(_b->m_firstBarrier);
	if(0 != res)
	{
		fprintf(stderr,"Barrier_Wait: first barrier error!\n");
		return res;
	}
	
	if(NULL != _callBack)
	{
		_callBack(_context);
	}
	
	res=SimpleBarrier_Wait(_b->m_secondBarrier);
	if(0 != res)
	{
		fprintf(stderr,"Barrier_Wait: second barrier error!\n");
		return res;
	}
	
	return 0;
}




