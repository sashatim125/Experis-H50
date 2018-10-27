/*This file contains the implementation for the Vector data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 10.12.2017
 */

#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
 
/*Definition of the Vector type*/ 
struct Vector
{
    /* The items */ 
    int*    m_items;
    /* original allocated space for items */ 
    size_t  m_originalSize;
     /* actual allocated space for items  */
    size_t  m_size;
     /* actual number of items */
    size_t  m_nItems;
    /* the chunk size to be allocated when no space*/
    size_t  m_blockSize;
};

 
/*Description :new vector creation with _initialSize and _extensionBblockSize;
 *Input : _initialSize (in elements) , _extensionBlockSize;
 *Output: pointer to the created vector;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_ALLOCATION_FAILED.
 */
Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
	Vector *vec;
	
	if ((_initialSize==0)&&(_extensionBlockSize==0))
	{
		return NULL;
	}
	if ((vec=(Vector*)malloc(sizeof(Vector)))==NULL)
	{
		return NULL;
	}
	if ((vec->m_items=(int*)malloc(sizeof(int)*_initialSize))==NULL)
	{
		free(vec);
		return NULL;
	}
	vec->m_originalSize=_initialSize;
	vec->m_size=_initialSize;
	vec->m_nItems=0;
	vec->m_blockSize=_extensionBlockSize;
	
	return vec;
}


/*Description :destroction of the vector;
 *Input : _vector - to be destroyed.
 *Output: none;
 *Error : ERR_NOT_INITIALIZED - does nothing , DO NOT use this function more then ONE time.
 */
void    VectorDestroy(Vector* _vector)
{

	if (_vector==NULL)
	{
		return;
	}
	free(_vector->m_items);
	free(_vector);
}


/*Description :addition of new element to the end and resizing the array be 1 new block
 *             if nessesary.
 *Input : existing _vector, new _item;
 *Output: status (see Errors)
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_REALLOCATION_FAILED,
 *        ERR_OVERFLOW.
 */
ADTErr  VectorAdd(Vector *_vector,  int  _item)
{
	int *tmpItems;
	size_t newSize;

	if(_vector==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
		
	/*reallocation*/
	newSize=_vector->m_size+_vector->m_blockSize;
	if(_vector->m_size == _vector->m_nItems)
	{
		if(_vector->m_blockSize==0)
		{
			return ERR_OVERFLOW;
		}
		if((tmpItems=(int*)realloc(_vector->m_items,
			sizeof(int)*newSize))==NULL)
		{
			return ERR_REALLOCATION_FAILED;
		}
		_vector->m_items=tmpItems;
		_vector->m_size=newSize;
	}
	
	(_vector->m_items)[_vector->m_nItems++]=_item;

	return ERR_OK;
}


/*Description :removes the last item from the vector and shrinks the vector
 *             by one block if two are empty if nessesary;
 *Input : the _vector, pointer to the _item returned;
 *Output: removed item in *_itemstatus returned;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_REALLOCATION_FAILED,ERR_UNDERFLOW.
 */
ADTErr  VectorDelete(Vector *_vector,  int* _item)
{
	int *tmpItems;
	size_t newSize;
	
	if((_vector==NULL)||(_item==NULL))
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_vector->m_nItems == 0){
		return ERR_UNDERFLOW;
	}
	
	*_item=(_vector->m_items)[--(_vector->m_nItems)];
	
	/*too much free space*/
	newSize=_vector->m_size-_vector->m_blockSize;
	
	if(((_vector->m_size-_vector->m_nItems)>\
		(2*_vector->m_blockSize))&&\
		((_vector->m_size-_vector->m_blockSize)>=\
		(_vector->m_originalSize)))
	{
		if((tmpItems=(int*)(realloc(_vector->m_items,\
			sizeof(int)*newSize)))==NULL)
		{
			return ERR_REALLOCATION_FAILED;
		}
		_vector->m_items=tmpItems;
		_vector->m_size=newSize;
	}
	
	return ERR_OK;
}


/*Description :get the element from the vector by the index(starts with 0);
 *Input : the _vector, the _index and place(pointer) to the _item;
 *Output: retrieved item in *_item, status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_WRONG_INDEX.
 */
ADTErr  VectorGet(Vector *_vector, size_t _index, int *_item)
{

	if((_vector==NULL)||(_item==NULL))
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_index >= _vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	
	*_item=(_vector->m_items)[_index];
	
	return ERR_OK;
}


/*Description :set the element in the vector by the index(starts with 0);
 *Input : the _vector, the _index and the _item value;
 *Output: status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_WRONG_INDEX.
 */
ADTErr  VectorSet(Vector *_vector, size_t _index, int  _item)
{

	if(_vector==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if (_index >= _vector->m_nItems)
	{
		return ERR_WRONG_INDEX;
	}
	
	(_vector->m_items)[_index]=_item;
	
	return ERR_OK;
}


/*Description :get number of element int the vector;
 *Input : the _vector and place(pointer) the thr _numOfItems;
 *Output: number of elements in *_numOfItems, status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED.
 */
ADTErr  VectorItemsNum(Vector *_vector, size_t*  _numOfItems)
{
	if((_vector==NULL)||(_numOfItems==NULL))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_numOfItems=_vector->m_nItems;
	
	return ERR_OK;
}


/*Description :prints the vector;
 *Input : the _vector;
 *Output: prints the vector and returns the status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED - does nothing.
 */
void    VectorPrint(Vector *_vector)
{
	int i;
	
	if(_vector==NULL)
	{
		return;
	}
	for(i=0 ; i<_vector->m_nItems ; ++i)
	{
		printf("%d ",(_vector->m_items)[i]);
	}
	putchar('\n');
}

