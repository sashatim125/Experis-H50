
#include "sort.h"
#include "../stack/stack.h"
#include <stdio.h>
#include <stdlib.h>

/** 
 *  @file sort.c
 *  @brief Various sort algorithms
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */
 
#ifndef TRUE
#define TRUE 1
#endif /*TRUE*/

#ifndef FALSE 
#define FALSE 0
#endif /*FALSE*/

#define STACK_SIZE 1024

#define FILL_QSSE(elem,begin,end,pivot,isLeftSorted) \
{\
	elem##QSSE.m_begin           = begin;\
	elem##QSSE.m_end             = end;\
	elem##QSSE.m_pivotInx        = pivot;\
	elem##QSSE.m_leftSideSorted  = isLeftSorted;\
}
 
typedef struct QuickSortStackEl
{
	int m_begin;
	int m_end;
	int m_pivotInx;
	int m_leftSideSorted;
	
} QuickSortStackEl;


static void MyInsertionSort(int _arr[], size_t _begin, size_t _end, size_t _step);
 
static void DownBubble(int _arr[], size_t _start , size_t _finish, size_t _step);
 
static size_t Partion(int _arr[], size_t _begin, size_t _end);

static void MyQuickSortRec(int _arr[], size_t _begin, size_t _end);

static void QSSPush(Stack *_stack, const QuickSortStackEl *nextQSSE);

static void QSSPop(Stack *_stack, QuickSortStackEl *nextQSSE);

static void Swap(int *a, int *b);

static int* GetMin(int *_begin, int *_end);

static void MyMergeSort(int *_arrIn, int *_arrOut , size_t _begin, size_t _end);

static void Merge(int *_arrIn,int *_arrOut,size_t _begin, size_t middle, size_t _end);

static ADTErr MyCountSort(int *_arrIn, int *_arrOut, size_t _size, unsigned range);


 
 
 
ADTErr InsertionSort(int _arr[], size_t _size)
{
	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
	
	MyInsertionSort(_arr,0,_size-1,1);	
	
	return ERR_OK;
 }
 

 
ADTErr ShellSort(int _arr[], size_t _size)
{
	size_t step,i;

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
	
	
	for(step=(_size)/2 ; step>0 ; step/=2)
	{
		for(i=0 ; i<step ; ++i)
		{
			MyInsertionSort(_arr,i,_size-1,step);
		}
	}
	return ERR_OK;
}


ADTErr QuickSortRec(int _arr[], size_t _size)
{

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
	
	MyQuickSortRec(_arr,0,_size-1);
	
	return ERR_OK;
}


ADTErr QuickSortIt(int _arr[], size_t _size)
{
	Stack *stack;
	QuickSortStackEl currQSSE, nextQSSE, prevQSSE;
	int nextPivot;

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
		
	if(NULL== (stack=StackCreate(STACK_SIZE*sizeof(QuickSortStackEl),STACK_SIZE*sizeof(QuickSortStackEl))))
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	nextPivot=(int)Partion(_arr,0,_size-1);
	
	FILL_QSSE(next,(int)0,(int)(_size-1),nextPivot,FALSE)
	
	QSSPush(stack,&nextQSSE);
	
	while (!StackIsEmpty(stack))
	{
		QSSPop(stack,&currQSSE);

		if(!currQSSE.m_leftSideSorted)
		{
			/*have to sort the left side*/
			if((0 < currQSSE.m_pivotInx) && (currQSSE.m_pivotInx-1 > currQSSE.m_begin))
			{
				QSSPush(stack,&currQSSE);
				
				nextPivot=(int)Partion(_arr, (size_t)(currQSSE.m_begin), (size_t)(currQSSE.m_pivotInx-1));
				
				FILL_QSSE(next,currQSSE.m_begin,currQSSE.m_pivotInx-1,nextPivot,FALSE)	
				
				QSSPush(stack,&nextQSSE);
				continue;	
			}
			else
			{	
				currQSSE.m_leftSideSorted = TRUE;
				QSSPush(stack,&currQSSE);
				continue;
			}
		}
		
		/*have to sort the right side*/						
		if (currQSSE.m_pivotInx+1 < currQSSE.m_end)
		{
			nextPivot=(int)Partion(_arr, (size_t)(currQSSE.m_pivotInx+1), (size_t)(currQSSE.m_end));
			
			FILL_QSSE(next,currQSSE.m_pivotInx+1,currQSSE.m_end,nextPivot,FALSE)
	
			QSSPush(stack,&nextQSSE);
			continue;			
		}
		if(!StackIsEmpty(stack))
		{
			QSSPop(stack,&prevQSSE);
			
			if(!prevQSSE.m_leftSideSorted)
			{
				prevQSSE.m_leftSideSorted=TRUE;
				QSSPush(stack,&prevQSSE);
			}
		}
	}
	
	StackDestroy(stack);
	return ERR_OK;
}



ADTErr SelectionSort(int _arr[], size_t _size)
{
	int *i, *last, *min;
	

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
	last=_arr+_size-1;
	
	for (i=_arr ; i<last ; ++i)
	{
		min = GetMin(i,last);
		if(*min < *i)
		{
			Swap(min,i);
		}
	}
	
	return ERR_OK;
}


ADTErr MergeSort(int _arr[], size_t _size)
{
	int *buff;

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
	
	buff = (int*)malloc(_size*sizeof(int));
	if (NULL==buff)
	{
		return ERR_ALLOCATION_FAILED;
	}
		
	MyMergeSort(_arr,buff,0,_size-1);	
	
	free(buff);
	
	return ERR_OK;
}



ADTErr CountSort(int _arr[], size_t _size)
{
	int *buff , i;
	ADTErr res;

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
	
	buff = (int*)malloc(_size*sizeof(int));
	if (NULL==buff)
	{
		return ERR_ALLOCATION_FAILED;
	}

	res = MyCountSort(_arr,buff,_size,100);
	
	if(ERR_OK != res)
	{
		return res;
	}
	
	for (i=0 ; i<_size ; ++i)
	{
		_arr[i]=buff[i];
	}

	free(buff);
	
	return ERR_OK;
}



static void MyInsertionSort(int _arr[], size_t _begin, size_t _end, size_t _step)
{
	size_t i, num;
	
	if(_end-_begin <_step)
	{
		return ;
	}
	num=(_end-_begin)%_step;
	_end=(num>0)?(_end+num-_step):_end;
	
	for(i=_begin+_step ; i <= _end ; i+=_step)
	{
		DownBubble(_arr,i,_begin,_step);	
	}
	
}
 
 
static void DownBubble(int _arr[], size_t _start , size_t _finish, size_t _step)
{
	size_t i;
	int temp ;

	_finish+=_step;

	for(i=_start ; i>= _finish ; i-=_step)
	{		
		if(_arr[i] < _arr[i-_step])
		{
			temp=_arr[i];
			_arr[i]=_arr[i-_step];
			_arr[i-_step]=temp;
		}else
		{
			break;
		}
	}
}


static size_t Partion(int _arr[], size_t _begin, size_t _end)
{
	size_t tooBigInx, tooSmallInx, pivotInx;
	int temp, pivotVal;

	pivotInx = _begin;
	pivotVal = _arr[pivotInx];
	
	tooBigInx=_begin+1;
	
	tooSmallInx = _end;
	
	do
	{
		while((_arr[tooBigInx] <= pivotVal) && (tooBigInx < _end))
		{
			++tooBigInx;
		}
		while((_arr[tooSmallInx] > pivotVal) && (tooSmallInx > _begin))
		{
			--tooSmallInx;
		}
		if(tooBigInx < tooSmallInx)
		{
			/* arr[toobig]<->arr[toosmall]*/
			temp=_arr[tooBigInx];
			_arr[tooBigInx] = _arr[tooSmallInx];
			_arr[tooSmallInx] = temp;
		}
	}while(tooSmallInx > tooBigInx);
	
	/*arr[toosmall]<->arr[pivot]*/
	temp=_arr[tooSmallInx];
	_arr[tooSmallInx] = _arr[pivotInx];
	_arr[pivotInx] = temp;
	
	/*return the new pivot index*/
	return tooSmallInx;

}


static void MyQuickSortRec(int _arr[], size_t _begin, size_t _end)
{
	size_t newPivotInx;
	
	if(_begin >= _end)
	{
		return;
	}
	
	newPivotInx=Partion(_arr,_begin,_end);

	if((newPivotInx>0)&&(newPivotInx-1 > _begin))
	{
		MyQuickSortRec(_arr,_begin,newPivotInx-1);
	}
	
	if(_end > newPivotInx+1)
	{
		MyQuickSortRec(_arr,newPivotInx+1,_end);
	}
}



static void QSSPush(Stack *_stack, const QuickSortStackEl *nextQSSE)
{
	StackPush(_stack,nextQSSE->m_begin);
	StackPush(_stack,nextQSSE->m_end);
	StackPush(_stack,nextQSSE->m_pivotInx);
	StackPush(_stack,nextQSSE->m_leftSideSorted);
}


static void QSSPop(Stack *_stack, QuickSortStackEl *nextQSSE)
{
	StackPop(_stack,&nextQSSE->m_leftSideSorted);
	StackPop(_stack,&nextQSSE->m_pivotInx);
	StackPop(_stack,&nextQSSE->m_end);
	StackPop(_stack,&nextQSSE->m_begin);
}

static void Swap(int *a, int *b)
{
	int temp;
	
	temp=*a;
	*a=*b;
	*b=temp;
}


static int* GetMin(int *_begin, int *_end)
{
	int *min , *i;
	
	min = _begin;
	
	for(i=_begin ; i<=_end ; ++i)
	{
		if(*i < *min)
		{
			min = i;
		}
	}
	
	return min;
}


static void MyMergeSort(int *_arrIn, int *_arrOut , size_t _begin, size_t _end)
{
	size_t middle, i;
	
	if((_end-_begin)<=0)
	{
		return;
	}
	
	middle = (_begin+_end)/2;
	
	MyMergeSort(_arrIn,_arrOut,_begin,middle);
	
	MyMergeSort(_arrIn,_arrOut,middle+1,_end);
	
	for	(i=_begin ; i<=_end ; ++i)
	{
		_arrOut[i] = _arrIn[i];
	}
	
	Merge(_arrOut,_arrIn,_begin,middle,_end);
}



static void Merge(int *_arrIn,int *_arrOut,size_t _begin, size_t middle, size_t _end)
{
	size_t arrOutInx, rightInx, leftInx;
	
	arrOutInx = _begin;
	leftInx = _begin;
	rightInx = middle+1;

	
	while((leftInx<=middle)&&(rightInx<=_end))
	{
		if(_arrIn[leftInx]<=_arrIn[rightInx])
		{
			_arrOut[arrOutInx++]=_arrIn[leftInx++];
		}else
		{
			_arrOut[arrOutInx++]=_arrIn[rightInx++];
		}
	}
	while(leftInx<=middle)
	{
		_arrOut[arrOutInx++]=_arrIn[leftInx++];
	}
	while(rightInx<=_end)
	{
		_arrOut[arrOutInx++]=_arrIn[rightInx++];
	}
}


static ADTErr MyCountSort(int *_arrIn, int *_arrOut, size_t _size, unsigned range)
{
	unsigned *counters;
	int i,j;

	
	counters = (unsigned*)calloc(range+1,sizeof(unsigned));
	if(NULL==counters)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	for(j=0 ; j<_size ; ++j)
	{
		++(counters[_arrIn[j]]);
	}
	
	for(i=1 ; i<=range ; ++i)
	{
		counters[i]=counters[i]+counters[i-1];
	}
	
	for(j=(int)_size-1 ; j>=0 ; --j)
	{
		--(counters[_arrIn[j]]);
		_arrOut[counters[_arrIn[j]]] = _arrIn[j];
	}
	
	free(counters);
	
	return ERR_OK;
}












