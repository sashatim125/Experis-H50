

/** 
 * @brief Create a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
 * 
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */ 


#include "vector.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcd
#endif /*MAGIC_NUMBER*/

#ifndef IS_NULL
#define IS_NULL(ptr) (NULL==(ptr))
#endif /*IS_NULL*/

#define IS_VECTOR_FULL(vec) ((vec)->m_size == (vec)->m_nItems)

#define IS_INDEX_WRONG(inx) (((_index) > _vector->m_nItems)||(1 > (_index)))


struct Vector
{
	int m_magicNum;
	
    /* The items */ 
    void  **m_items;
    
    /* original allocated space for items */ 
    size_t  m_originalSize;
    
     /* actual allocated space for items  */
    size_t  m_size;
    
     /* actual number of items */
    size_t  m_nItems;
    
    /* the chunk size to be allocated when no space*/
    size_t  m_blockSize;
};

static Vector_Result VectorGrow(Vector *_vector);

static Vector_Result VectorShrink(Vector *_vector);


Vector* Vector_Create(size_t _initialCapacity, size_t _blockSize)
{
	Vector *vec;
	
	if ((_initialCapacity==0)&&(_blockSize==0))
	{
		return NULL;
	}
	if (IS_NULL(vec=(Vector*)malloc(sizeof(Vector))))
	{
		return NULL;
	}
	if (IS_NULL(vec->m_items=(void**)malloc(sizeof(void*)*_initialCapacity)))
	{
		free(vec);
		return NULL;
	}
	vec->m_originalSize=_initialCapacity;
	vec->m_size=_initialCapacity;
	vec->m_nItems=0;
	vec->m_blockSize=_blockSize;
	
	vec->m_magicNum = MAGIC_NUMBER;
	
	return vec;
}



void Vector_Destroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
	size_t i; 

	if(IS_NULL(_vector))
	{
		return;
		
	}else if(IS_NULL(*_vector)||(MAGIC_NUMBER != (*_vector)->m_magicNum))
	{
		*_vector=NULL;
		return;
	}
	
	if(!IS_NULL(_elementDestroy))
	{
		for(i=(*_vector)->m_nItems ; i>=1 ; --i)
		{
			_elementDestroy((*_vector)->m_items[i-1]);
		}
	}
	
	free((*_vector)->m_items);
	(*_vector)->m_magicNum = 0;
	free(*_vector);
	*_vector=NULL;
}


Vector_Result Vector_Append(Vector* _vector, void* _item)
{
	Vector_Result res;

	if(IS_NULL(_vector))
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
		
	/*reallocation*/
	if(IS_VECTOR_FULL(_vector))
	{
		if (VECTOR_SUCCESS != (res=VectorGrow(_vector)))
		{
			return res;
		}
	}
	
	(_vector->m_items)[(_vector->m_nItems)++]=_item;

	return VECTOR_SUCCESS;
}


Vector_Result Vector_Remove(Vector* _vector, void** _pValue)
{
	Vector_Result res;
	
	if(IS_NULL(_vector)||IS_NULL(_pValue))
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	
	if(_vector->m_nItems == 0){
	
		return VECTOR_UNDERFLOW;
	}
	
	*_pValue=(_vector->m_items)[--(_vector->m_nItems)];
	
	/*shrink if needed*/
	if (VECTOR_SUCCESS != (res=VectorShrink(_vector)))
	{
		return res;
	}
	
	return VECTOR_SUCCESS;
}



Vector_Result Vector_Get(const Vector* _vector, size_t _index, void** _pValue)
{
	if(IS_NULL(_vector)||IS_NULL(_pValue))
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	
	if (IS_INDEX_WRONG(_index))
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	
	*_pValue=(_vector->m_items)[_index-1];
	
	return VECTOR_SUCCESS;
}


Vector_Result Vector_Set(Vector* _vector, size_t _index, void *_value)
{
	if(IS_NULL(_vector))
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	
	if (IS_INDEX_WRONG(_index))
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	
	(_vector->m_items)[_index-1]=_value;
	
	return VECTOR_SUCCESS;
}


size_t Vector_Size(const Vector* _vector)
{
	if(IS_NULL(_vector))
	{
		return 0;
	}
	return _vector->m_nItems;
}


size_t Vector_Capacity(const Vector* _vector)
{
	if(IS_NULL(_vector))
	{
		return 0;
	}
	return _vector->m_size;
}



size_t Vector_ForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	size_t i;
	int res;
	void *item;

	if(IS_NULL(_vector)||IS_NULL(_action))
	{
		return 0;
	}
	
	for(i=1, res=1 ; i <= _vector->m_nItems && res; ++i)
	{
		Vector_Get(_vector,i,&item);
		res = _action(item,i,_context);
	}
	
	return i-1;
}


static Vector_Result VectorGrow(Vector *_vector)
{
	void **tmpItems;
	size_t newSize ,blockSize ;
	
	blockSize = _vector->m_blockSize;
	
	newSize=_vector->m_size+blockSize;

	if(blockSize==0)
	{
		return VECTOR_OVERFLOW;
	}
	
	if(IS_NULL(tmpItems=(void**)realloc(_vector->m_items,
		sizeof(void*)*newSize)))
	{
		return VECTOR_ALLOCATION_ERROR;
	}
	
	_vector->m_items=tmpItems;
	_vector->m_size=newSize;
	
	return	VECTOR_SUCCESS;
}


static Vector_Result VectorShrink(Vector *_vector)
{
	void **tmpItems;
	size_t newSize ,blockSize ;

	blockSize = _vector->m_blockSize;

	/*too much free space*/
	newSize=_vector->m_size-blockSize;
	
	if(((_vector->m_size-_vector->m_nItems) >
		(2*blockSize)) &&
		((_vector->m_size-blockSize) >=
		(_vector->m_originalSize)))
	{
		if(IS_NULL(tmpItems=(void**)(realloc(_vector->m_items,
			sizeof(void*)*newSize))))
		{
			return VECTOR_ALLOCATION_ERROR;
		}
		_vector->m_items=tmpItems;
		_vector->m_size=newSize;
	}

	return	VECTOR_SUCCESS;
}





