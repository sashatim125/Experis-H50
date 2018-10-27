/*This file contains the the Queue data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 13.12.2017
 */

#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

struct Queue
{
    size_t  m_size;
    size_t  m_head;    /* Index of head */
    size_t  m_tail;    /* Index of tail */
    size_t  m_nItems;
    int     m_items[1];
};

Queue* QueueCreate(size_t _size){

	
	Queue *queue;
	
	if (_size == 0)
	{
		return NULL;
	}
	
	queue=(Queue*)malloc(sizeof(Queue)+(_size-1)*sizeof(int));
	if (queue == NULL)
	{
		return NULL;
	}

	queue->m_size=_size;
	queue->m_nItems=0;
	
	return queue;
}

void   QueueDestroy(Queue *_queue)
{
	if (_queue == NULL)
	{
		return;
	}
	free(_queue);
}

ADTErr QueueInsert(Queue *_queue, int  _item)
{
	if(_queue == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_queue->m_size==_queue->m_nItems)
	{
		return ERR_OVERFLOW;
	}
	if(_queue->m_nItems==0)
	{
		_queue->m_head=_queue->m_tail=0;
		_queue->m_items[0]=_item;
		_queue->m_nItems=1;
		
		return ERR_OK;
	}
	_queue->m_tail=(_queue->m_tail+1)%_queue->m_size;
	_queue->m_items[_queue->m_tail]=_item;
	_queue->m_nItems++;
	
	return ERR_OK;
}

ADTErr QueueRemove(Queue *_queue, int *_item)
{
	if((_queue == NULL)||(_item == NULL))
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_queue->m_nItems==0)
	{
		return ERR_UNDERFLOW;
	}
	
	*_item = _queue->m_items[_queue->m_head];
	_queue->m_head=(_queue->m_head+1)%_queue->m_size;
	_queue->m_nItems--;
	return ERR_OK;
}

int    QueueIsEmpty(Queue *_queue)
{
	if(_queue == NULL)
	{
		return TRUE;
	}

	return (_queue->m_nItems == 0);
}

void   QueuePrint(Queue *_queue)
{
	size_t i,j;
	
	if(_queue == NULL)
	{
		return;
	}
	
	for(i=0, j=_queue->m_head ; i<_queue->m_nItems ; ++i, j=(j+1)%_queue->m_size)
	{
		printf("%d ",_queue->m_items[j]);
	}
	putchar('\n');
}
















