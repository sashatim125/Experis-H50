
/** 
 *  @file heap.c
 *  @brief implementation of API for the the heap(of ints)
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

#ifndef LEFT
#define LEFT(i)	((i)<<1)
#endif /*LEFT*/

#ifndef RIGHT
#define RIGHT(i) (((i)<<1)|1u)
#endif /*RIGHT*/

#ifndef PARENT
#define PARENT(i) ((i)>>1)
#endif /*PARENT*/

struct Heap
{
	Vector* m_vec;
	
	size_t m_size;
	
	int m_magNum;
};

/*IMPORTENT !!!
 *indices in heap are 1...size
 */

static void Heapify(Heap* _heap, size_t _i);

static void VectorSwap(Vector* _vec, size_t i, size_t j);

Heap* HeapBuild(Vector* _vec)
{
	size_t heapSize,i;
	Heap* newHeap;
	
	if(NULL==_vec)
	{
		return NULL;
	}
	
	newHeap=(Heap*)malloc(sizeof(Heap));
	
	if(NULL==newHeap)
	{
		return NULL;
	}
	
	newHeap->m_vec=_vec;
	newHeap->m_magNum=MAGIC_NUMBER;

	if(ERR_OK!=VectorItemsNum(_vec,&heapSize))
	{
		return NULL;
	}
	
	newHeap->m_size=heapSize;
	
  	for (i=PARENT(heapSize) ; i>=1 ; --i)
  	{
    	Heapify(newHeap, i);
	}
	
	return newHeap;
}


void HeapDestroy(Heap* _heap)
{
	if((NULL==_heap)||(MAGIC_NUMBER==_heap->m_magNum))
	{
		return;
	}
	
	_heap->m_magNum=0;
	
	free(_heap);
}

ADTErr  HeapInsert(Heap* _heap, int _data)
{
	ADTErr res;
	size_t i;
	int item1,item2;
	Vector *vec;

	if(NULL==_heap)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	vec=_heap->m_vec;
	
	res=VectorAdd(vec,_data);
	if(ERR_OK!=res)
	{
		return res;
	}
	
	i = ++_heap->m_size;
	
	VectorGet(vec,PARENT(i)-1,&item1);
	VectorGet(vec,i-1,&item2);
	
	while((i > 1)&&(item1 < item2))
	{
		VectorSwap(vec,i-1,PARENT(i)-1);
		i = PARENT(i);
		
		VectorGet(vec,PARENT(i)-1,&item1);
		VectorGet(vec,i-1,&item2);		
	}
	
	
	
	return ERR_OK;
}


ADTErr HeapMax(Heap* _heap, int* _data)
{
	if((NULL==_heap)||(NULL==_data))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(0==_heap->m_size)
	{
		return ERR_UNDERFLOW;
	}
	
	return VectorGet(_heap->m_vec,0,_data);
}


ADTErr  HeapExtractMax(Heap* _heap, int* _data){

	if((NULL==_heap)||(NULL==_data))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(0==_heap->m_size)
	{
		return ERR_UNDERFLOW;
	}
	
	--_heap->m_size;
	
	VectorSwap(_heap->m_vec,0,_heap->m_size);

	Heapify(_heap,1);
	
	return VectorDelete(_heap->m_vec,_data);
}


size_t HeapItemsNum(Heap* _heap)
{
	if(NULL==_heap)
	{
		return 0;
	}
	
	return _heap->m_size;
}

void HeapPrint(Heap* _heap)
{
	if(NULL==_heap)
	{
		return;
	}
	
	VectorPrint(_heap->m_vec);
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
  	VectorGet(vec,left.m_ind-1,&left.m_val);
  	VectorGet(vec,parent.m_ind-1,&parent.m_val);
  	
	if (left.m_ind <= heapSize && left.m_val > parent.m_val)
	{
		largest=&left;
    }
    
    VectorGet(vec,right.m_ind-1,&right.m_val);
    
	if (right.m_ind <= heapSize && right.m_val > largest->m_val)
	{
		largest=&right;
	}
	
	if (largest != &parent){
		VectorSet(vec,parent.m_ind-1,largest->m_val);
		VectorSet(vec,largest->m_ind-1,parent.m_val);
		
		Heapify(_heap,largest->m_ind);
	}
	
}

static void VectorSwap(Vector* _vec, size_t _i, size_t _j)
{
	int item1,item2;

	VectorGet(_vec,_j,&item2);
	VectorGet(_vec,_i,&item1);
	VectorSet(_vec,_i,item2);
	VectorSet(_vec,_j,item1);
}

int IsHeapOK(Heap* _heap)
{
	size_t i;
	int item1,item2,item3;

	if(NULL==_heap)
	{
		return FALSE;
	}

	for (i=1 ; i<=(_heap->m_size)/2 ; ++i)
  	{
  		VectorGet(_heap->m_vec,i-1,&item1);
  		VectorGet(_heap->m_vec,LEFT(i)-1,&item2);
  		if(item1 < item2)
    	{
    		return FALSE;
    	}
  		if(RIGHT(i) > _heap->m_size)
  		{
  			continue;
  		} else
  		{
  			VectorGet(_heap->m_vec,RIGHT(i)-1,&item3);
    		if(item1 < item3)
    		{
    			return FALSE;
    		}
    	}
	}
	
	return TRUE;
}





