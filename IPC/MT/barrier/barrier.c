

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


#include "barrier.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcfed
#endif /*MAGIC_NUMBER*/


struct Barrier
{
	int m_magicNum;
	
	size_t m_capacity;
	
	size_t m_commingCount;
	
	size_t m_leavingCount;

	pthread_cond_t m_commingCV;
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
		0 != pthread_cond_init(&(b->m_leavingCV),NULL) ||
		0!= pthread_mutex_init(&(b->m_mutex),NULL))
	{
		free(b);
		fprintf(stderr,"Barrier_Create: cond or mutex init error.\n");
		return NULL;
	}
	
	b->m_capacity = _capacity;
	b->m_commingCount = 0;
	b->m_leavingCount = 0;

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
	
	free(_b);
}


int Barrier_Wait(Barrier* _b)
{
	int isFirstLeaver;
	int isLastLeaver;

	if(_b == NULL || MAGIC_NUMBER != _b->m_magicNum)
	{
		return -1;
	}
	
	isFirstLeaver = 1;
	
	if(0!=pthread_mutex_lock(&(_b->m_mutex)))
	{
		return -2;
	}
	while(0 < _b->m_leavingCount)
	{
		if(0!=pthread_cond_wait(&(_b->m_leavingCV),&(_b->m_mutex)))
		{
			fprintf(stderr,"Barrier_Wait: Waiting for leaving cond. var. error!\n");
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
	
	++(_b->m_leavingCount);
	
	isLastLeaver = (_b->m_capacity == _b->m_leavingCount);
	
	if(isLastLeaver)
	{
		_b->m_leavingCount = 0;
		_b->m_commingCount = 0;
	}

	if(0!=pthread_mutex_unlock(&(_b->m_mutex)))
	{
		return -5;
	}
	
	if(isFirstLeaver && 0!=pthread_cond_broadcast(&(_b->m_commingCV)))
	{
		fprintf(stderr,"Barrier_Wait: Broadcast to commings error!\n");
		return -8;
	}
	
	if(isLastLeaver && 0!=pthread_cond_broadcast(&(_b->m_leavingCV)))
	{
		fprintf(stderr,"Barrier_Wait: Broadcast to commings error!\n");
		return -8;
	}

	return 0;
}
























