

/** 
 *  @file ShMemWCQueue.c
 *  @brief Waitable shared memory cyclic queue 
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include "ShMemWCQueue.h"
#include "memAlloc.h"
#include "sysutils.h"

#include <string.h>
#include <stdio.h> 


#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/

struct ShMemWCQueue 
{
	int m_magicNum;
	
	int m_sem;
	size_t m_contMemAddr;	
    size_t  m_size;
    size_t  m_head;    /* Index of head */
    size_t  m_tail;    /* Index of tail */
    size_t  m_nItems;
    size_t  m_items[1];
};

typedef struct Item
{
	size_t m_size;
	char m_item[1];
} Item;

ShMemWCQueue* ShMemWCQueue_Init(void* _shmem, size_t _shmemSize, size_t _qSize)
{
	ShMemWCQueue* q;
	size_t qTotSize;
	void* contMemPtr;
	
	if(NULL==_shmem || _qSize*sizeof(size_t) + sizeof(ShMemWCQueue) >= _shmemSize ||
		0 == _qSize )
	{
		return NULL;
	}
	
	qTotSize = sizeof(ShMemWCQueue) + _qSize*sizeof(size_t);
	
	q = _shmem;
	
	if(NULL == (contMemPtr = initMem((char*)_shmem + qTotSize,_shmemSize - qTotSize)))
	{
		return NULL;
	}
	
	q->m_contMemAddr = (size_t)((char*)contMemPtr - (char*)q);
	
	q->m_sem = GetSemaphore();
	
	if(0 != InitSemaphore(q->m_sem,_qSize))
	{
		return NULL;
	}
	
	q->m_size = _qSize;
	q->m_nItems = 0;
	
	q->m_magicNum = MAGIC_NUMBER;

	return q;
}



ShMemWCQueue* ShMemWCQueue_Connect(void* _shmem)
{
	return (ShMemWCQueue*)_shmem;
}



int ShMemWCQueue_Insert(ShMemWCQueue* _q, const void* _itemCont, size_t _itemSize)
{
	size_t itemOffset;
	Item *newItem;

	if(_q == NULL || MAGIC_NUMBER != _q->m_magicNum || NULL==_itemCont || 0==_itemSize)
	{
		return -1;
	}
	
	if(0 != InsertRequest(_q->m_sem))
	{
		return -2;
	}
	
	if(NULL == (newItem = allocMem((char*)_q + _q->m_contMemAddr,sizeof(Item) -1 + _itemSize)))
	{
		fprintf(stderr,"allocation error.\n");
		UndoInsertRequest(_q->m_sem);
		return -3;
	}
	
	itemOffset = (size_t)((char*)newItem - (char*)_q);
	
	newItem->m_size = _itemSize;	
	
	memcpy(newItem->m_item,_itemCont,_itemSize);
	
	if(_q->m_nItems==0)
	{
		_q->m_head=_q->m_tail=0;
		_q->m_items[0]=itemOffset;
		_q->m_nItems=1;
	}else
	{
		_q->m_tail=(_q->m_tail+1)%_q->m_size;
		_q->m_items[_q->m_tail]=itemOffset;
		_q->m_nItems++;
	}
	
	ReleaseSem(_q->m_sem);
	
	return 0;
}



int ShMemWCQueue_Remove(ShMemWCQueue* _q, void* _buff, size_t _buffSize, size_t* _itemSizePtr)
{
	size_t itemOffset;
	Item *item;

	if(_q == NULL || MAGIC_NUMBER != _q->m_magicNum ||
		NULL==_buff || 0==_buffSize || NULL==_itemSizePtr)
	{
		return -1;
	}
	
	if(0 != RemoveRequest(_q->m_sem))
	{
		return -2;
	}
	
	itemOffset = _q->m_items[_q->m_head];
	
	item = (Item*)((char*)_q + itemOffset);
	
	if(_buffSize < item->m_size)
	{
		UndoRemoveRequest(_q->m_sem);
		return -3;
	}
	
	memcpy(_buff,item->m_item,item->m_size);
	
	*_itemSizePtr = item->m_size;
	
	releaseMem(item);

	_q->m_head=(_q->m_head+1)%_q->m_size;
	_q->m_nItems--;
	
	ReleaseSem(_q->m_sem);
	
	return 0;
}


size_t ShMemWCQueue_GetSize(ShMemWCQueue* _q)
{
	if(NULL==_q)
	{
		return 0;
	}
	
	return _q->m_nItems;

}







