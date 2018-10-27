
/** 
 *  @file heap.c
 *  @brief implementation of API for the the heap(of void*)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */
 
#include "heap.h"
#include <stdlib.h>


#ifndef TRUE
#define TRUE 1
#endif /*TRUE*/

#ifndef FALSE 
#define FALSE 0
#endif /*FALSE*/

#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER	-0xabccba
#endif /*MAGIC_NUMBER*/

#define LEFT(i)	((i)<<1)

#define RIGHT(i) (((i)<<1)|1ul)

#define PARENT(i) ((i)>>1)

struct Heap
{
	int m_magNum;
	
	Vector* m_vec;
	
	size_t m_size;
	
	LessComparator m_less;
	
};

/*IMPORTENT !!!
 *indices in heap are 1...size
 */

static void Heapify(Heap* _heap, size_t _i);

static void VectorSwap(Vector* _vec, size_t i, size_t j);

Heap* HeapBuild(Vector* _vec, LessComparator _less)
{
	size_t i;
	Heap* newHeap;
	
	if(NULL==_vec || NULL==_less)
	{
		return NULL;
	}
	
	newHeap=(Heap*)malloc(sizeof(Heap));
	
	if(NULL==newHeap)
	{
		return NULL;
	}
	
	newHeap->m_vec=_vec;
	
	newHeap->m_size=Vector_Size(_vec);
	
	newHeap->m_less=_less;
	
  	for (i=PARENT(newHeap->m_size) ; i>=1 ; --i)
  	{
    	Heapify(newHeap, i);
	}
	
	newHeap->m_magNum=MAGIC_NUMBER;
	
	return newHeap;
}


void HeapDestroy(Heap* _heap)
{
	if((NULL==_heap)||(MAGIC_NUMBER!=_heap->m_magNum))
	{
		return;
	}
	
	_heap->m_magNum=0;
	
	free(_heap);
}

Heap_Result  HeapInsert(Heap* _heap, void* _data)
{
	Vector_Result res;
	size_t i;
	void *item1,*item2;
	Vector *vec;

	if(NULL==_heap)
	{
		return HEAP_UNINITIALIZED_ERROR;
	}
	
	vec=_heap->m_vec;
	
	res=Vector_Append(vec,_data);
	if(VECTOR_SUCCESS!=res)
	{
		return (Heap_Result)res;
	}
	
	i = ++_heap->m_size;
	
	Vector_Get(vec,PARENT(i),&item1);
	Vector_Get(vec,i,&item2);
	
	while((i > 1)&&(_heap->m_less(item1,item2)))
	{
		VectorSwap(vec,i,PARENT(i));
		i = PARENT(i);
		
		Vector_Get(vec,PARENT(i),&item1);
		Vector_Get(vec,i,&item2);		
	}

	return HEAP_SUCCESS;
}


Heap_Result HeapMax(Heap* _heap, void** _data)
{
	if((NULL==_heap)||(NULL==_data))
	{
		return HEAP_UNINITIALIZED_ERROR;
	}
	
	if(0==_heap->m_size)
	{
		return HEAP_UNDERFLOW_ERROR;
	}
	
	return (Heap_Result)Vector_Get(_heap->m_vec,1,_data);
}


Heap_Result  HeapExtractMax(Heap* _heap, void** _data){

	if((NULL==_heap)||(NULL==_data))
	{
		return HEAP_UNINITIALIZED_ERROR;
	}
	
	if(0==_heap->m_size)
	{
		return HEAP_UNDERFLOW_ERROR;
	}
	
	VectorSwap(_heap->m_vec,1,_heap->m_size--);

	Heapify(_heap,1);
	
	return (Heap_Result)Vector_Remove(_heap->m_vec,_data);
}


size_t HeapItemsNum(Heap* _heap)
{
	if(NULL==_heap)
	{
		return 0;
	}
	
	return _heap->m_size;
}


static void Heapify(Heap* _heap, size_t _i)
{
	size_t heapSize;
	Vector *vec;
	
	struct Item
	{
		void* m_val;
		size_t m_ind;
	} left , right , parent , *largest;

	left.m_ind=LEFT(_i);
  	right.m_ind=RIGHT(_i);
  	parent.m_ind=_i;
  	
  	heapSize=_heap->m_size;
  	vec=_heap->m_vec;

  	largest=&parent;
  	Vector_Get(vec,left.m_ind,&left.m_val);
  	Vector_Get(vec,parent.m_ind,&parent.m_val);
  	
	if (left.m_ind <= heapSize && _heap->m_less(parent.m_val,left.m_val))
	{
		largest=&left;
    }
    
    Vector_Get(vec,right.m_ind,&right.m_val);
    
	if (right.m_ind <= heapSize && _heap->m_less(largest->m_val,right.m_val))
	{
		largest=&right;
	}
	
	if (largest != &parent)
	{
		Vector_Set(vec,parent.m_ind,largest->m_val);
		Vector_Set(vec,largest->m_ind,parent.m_val);
		
		Heapify(_heap,largest->m_ind);
	}
	
}

static void VectorSwap(Vector* _vec, size_t _i, size_t _j)
{
	void *item1,*item2;

	Vector_Get(_vec,_j,&item2);
	Vector_Get(_vec,_i,&item1);
	Vector_Set(_vec,_i,item2);
	Vector_Set(_vec,_j,item1);
}

int IsHeapOK(Heap* _heap)
{
	size_t i;
	void *item1,*item2,*item3;

	if(NULL==_heap)
	{
		return FALSE;
	}

	for (i=1 ; i<=(_heap->m_size)/2 ; ++i)
  	{
  		Vector_Get(_heap->m_vec,i,&item1);
  		Vector_Get(_heap->m_vec,LEFT(i),&item2);
  		if(_heap->m_less(item1,item2))
    	{
    		return FALSE;
    	}
  		if(RIGHT(i) > _heap->m_size)
  		{
  			continue;
  		} else
  		{
  			Vector_Get(_heap->m_vec,RIGHT(i),&item3);
    		if(_heap->m_less(item1,item3))
    		{
    			return FALSE;
    		}
    	}
	}
	
	return TRUE;
}

#undef LEFT
#undef RIGHT
#undef PARENT




