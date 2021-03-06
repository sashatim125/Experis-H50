

/** 
 *  @file barrier.c
 *  @brief Barrier implementation
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#include "barrier.h"

#define MAGIC_NUMBER 0xabcfed

struct Barrier
{
	int m_magicNum;
	
	size_t m_capacity;
	
	size_t m_commingCount;
	
	size_t m_readyAfterFuncCount;
	
	size_t m_leavingCount;
	
	size_t m_totCount;
	
	size_t m_groupCount;

	pthread_cond_t m_commingCV;
	pthread_cond_t m_funcCV;
	pthread_cond_t m_leavingCV;
	
	pthread_mutex_t m_mutex;
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

	if( 0 != pthread_cond_init(&(b->m_commingCV),NULL) ||
		0 != pthread_cond_init(&(b->m_funcCV),NULL) ||
		0 != pthread_cond_init(&(b->m_leavingCV),NULL) ||
		0!= pthread_mutex_init(&(b->m_mutex),NULL))
	{
		free(b);
		fprintf(stderr,"Barrier_Create: cond or mutex init error.\n");
		return NULL;
	}
	
	b->m_capacity = _capacity;
	b->m_commingCount = 0;
	b->m_readyAfterFuncCount = 0;
	b->m_leavingCount = 0;
	b->m_totCount = 0;
	b->m_groupCount = 0;

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
	
	pthread_cond_broadcast(&(_b->m_commingCV));
	pthread_cond_broadcast(&(_b->m_leavingCV));
	
	free(_b);
}


int Barrier_Wait(Barrier* _b, void(*_callBack)(void*), void* _context)
{
	int isFirstLeaver;
	int isLastLeaver;
	size_t myGroup;

	if(_b == NULL || MAGIC_NUMBER != _b->m_magicNum)
	{
		return -1;
	}
	
	isFirstLeaver = 1;
	
	if(0!=pthread_mutex_lock(&(_b->m_mutex)))
	{
		return -2;
	}
	
	myGroup = _b->m_totCount / _b->m_capacity;
	++(_b->m_totCount);
	
	while(myGroup != _b->m_groupCount || 0 < _b->m_leavingCount)
	{
		if(0!=pthread_cond_wait(&(_b->m_leavingCV),&(_b->m_mutex)))
		{
			fprintf(stderr,"Barrier_Wait: Waiting for leaving cond.var. error!\n");
			return -3;
		}
	}
		
	++(_b->m_commingCount);

	while(_b->m_capacity > _b->m_commingCount)
	{
		isFirstLeaver = 0;
		
		if(0!=pthread_cond_wait(&(_b->m_commingCV),&(_b->m_mutex)))
		{
			fprintf(stderr,"Barrier_Wait: Waiting for comming cond. var. error!\n");
			return -4;
		}
	}
	if(0!=pthread_mutex_unlock(&(_b->m_mutex)))
	{
		return -5;
	}
	
	if(isFirstLeaver && 0!=pthread_cond_broadcast(&(_b->m_commingCV)))
	{
		fprintf(stderr,"Barrier_Wait: Broadcast to commings error!\n");
		return -6;
	}
	
	if(NULL!=_callBack)
	{
		_callBack(_context);
	}
	
	isFirstLeaver = 1;
	
	if(0!=pthread_mutex_lock(&(_b->m_mutex)))
	{
		return -7;
	}
	
	++(_b->m_readyAfterFuncCount);
	
	while(_b->m_capacity > _b->m_readyAfterFuncCount)
	{
		isFirstLeaver = 0;
		
		if(0!=pthread_cond_wait(&(_b->m_funcCV),&(_b->m_mutex)))
		{
			fprintf(stderr,"Barrier_Wait: Waiting for after func. cond. var. error!\n");
			return -8;
		}
	}
	
	++(_b->m_leavingCount);
	
	isLastLeaver = (_b->m_capacity == _b->m_leavingCount);
	
	if(isLastLeaver)
	{
		_b->m_leavingCount = 0;
		_b->m_commingCount = 0;
		_b->m_readyAfterFuncCount = 0;
		++(_b->m_groupCount);
	}

	if(0!=pthread_mutex_unlock(&(_b->m_mutex)))
	{
		return -9;
	}
	
	if(isFirstLeaver && 0!=pthread_cond_broadcast(&(_b->m_funcCV)))
	{
		fprintf(stderr,"Barrier_Wait: Broadcast to commings error!\n");
		return -10;
	}
	
	if(isLastLeaver && 0!=pthread_cond_broadcast(&(_b->m_leavingCV)))
	{
		fprintf(stderr,"Barrier_Wait: Broadcast to commings error!\n");
		return -11;
	}

	return 0;
}
























