

/** 
 *  @file waitQueue.c
 *  @brief Waitable generic cyclic queue 
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include "waitQueue.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>


#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/

struct WaitQueue 
{
	int m_magicNum;
	
    size_t  m_size;
    size_t  m_head;    /* Index of head */
    size_t  m_tail;    /* Index of tail */
    size_t  m_nItems;
    
	sem_t m_freeSem;
	sem_t m_occSem;
	pthread_mutex_t m_qMutex;
		
    void*  m_items[1];
};


WaitQueue* WaitQueue_Create(size_t _qSize)
{
	WaitQueue* q;
	
	if(0 == _qSize)
	{
		return NULL;
	}
	
	if(NULL == (q = malloc(sizeof(WaitQueue) + _qSize*sizeof(void*) )))
	{
		return NULL;
	}
	
	if(0 != sem_init(&(q->m_freeSem),0,(unsigned)_qSize) ||
		0 != sem_init(&(q->m_occSem),0,0) ||
		0!= pthread_mutex_init(&(q->m_qMutex),NULL))
	{
		free(q);
		fprintf(stderr,"sem or mutex init error.\n");
		return NULL;
	}
	
	q->m_size = _qSize;
	q->m_nItems = 0;
	
	q->m_magicNum = MAGIC_NUMBER;

	return q;
}



void WaitQueue_Destroy(WaitQueue* _q)
{
	if(NULL==_q || MAGIC_NUMBER!= _q->m_magicNum)
	{
		return;
	}
	
	_q->m_magicNum = -1;
	
	free(_q);
}



int WaitQueue_Insert(WaitQueue* _q, void* _item)
{

	if(_q == NULL || MAGIC_NUMBER != _q->m_magicNum)
	{
		return -1;
	}
	
	if(0 != sem_wait(&(_q->m_freeSem)))
	{
		return -2;
	}
	
	if(0!=pthread_mutex_lock(&(_q->m_qMutex)))
	{
		return -3;
	}
	
	if(0 ==_q->m_nItems)
	{
		_q->m_head =_q->m_tail = 0;
	}else
	{
		_q->m_tail = (_q->m_tail+1) % _q->m_size;
	}
	_q->m_items[_q->m_tail] = _item;
	_q->m_nItems++;
	
	if(0!=pthread_mutex_unlock(&(_q->m_qMutex)))
	{
		return -4;
	}
	
	if(0 != sem_post(&(_q->m_occSem)))
	{
		return -5;
	}
	
	return 0;
}



int WaitQueue_Remove(WaitQueue* _q, void** _itemPtr)
{

	if(_q == NULL || MAGIC_NUMBER != _q->m_magicNum ||
		NULL==_itemPtr)
	{
		return -1;
	}
	
	if(0 != sem_wait(&(_q->m_occSem)))
	{
		return -2;
	}
	
	if(0!=pthread_mutex_lock(&(_q->m_qMutex)))
	{
		return -3;
	}
	
	*_itemPtr = _q->m_items[_q->m_head];

	_q->m_head = (_q->m_head+1) % _q->m_size;
	_q->m_nItems--;
	
	if(0!=pthread_mutex_unlock(&(_q->m_qMutex)))
	{
		return -4;
	}
	
	if(0 != sem_post(&(_q->m_freeSem)))
	{
		return -5;
	}
	
	return 0;
}


size_t WaitQueue_GetSize(WaitQueue* _q)
{
	if(NULL==_q)
	{
		return 0;
	}
	
	return _q->m_nItems;

}







