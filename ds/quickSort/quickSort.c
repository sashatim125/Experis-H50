

#include "../ADTErr.h"
#include "../stack/stack.h"
#include <stdio.h>


#ifndef TRUE
#define TRUE 1
#endif /*TRUE*/

#ifndef FALSE 
#define FALSE 0
#endif /*FALSE*/

#define STACK_SIZE 50

#define FILL_QSSE(elem,begin,end,pivot,isLeftSorted) \
{\
	elem##QSSE.m_begin           = begin;\
	elem##QSSE.m_end             = end;\
	elem##QSSE.m_pivotInx        = pivot;\
	elem##QSSE.m_leftSideSorted  = isLeftSorted;\
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

/*
static void MyQuickSortRec(int _arr[], size_t _begin, size_t _end)
{
	size_t newPivotInx;
	
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


ADTErr QuickSortRec(int _arr[], size_t _begin, size_t _end)
{

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_begin > _end)
	{
		return ERR_WRONG_INDEX;
	}
	
	if(_begin == _end)
	{
		return ERR_OK;
	}
	
	MyQuickSortRec(_arr,_begin,_end);
	
	return ERR_OK;
}

*/
typedef struct QuickSortStackEl
{
	int m_begin;
	int m_end;
	int m_pivotInx;
	int m_leftSideSorted;
	
} QuickSortStackEl;

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


ADTErr QuickSortIt(int _arr[], size_t _begin, size_t _end)
{
	Stack *stack;
	QuickSortStackEl currQSSE, nextQSSE, prevQSSE;
	int nextPivot;

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_begin > _end)
	{
		return ERR_WRONG_INDEX;
	}
	
	if(_begin == _end)
	{
		return ERR_OK;
	}
	
	if(NULL== (stack=StackCreate(STACK_SIZE*sizeof(QuickSortStackEl),(STACK_SIZE*sizeof(QuickSortStackEl))/2)))
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	nextPivot=(int)Partion(_arr,_begin,_end);
	
	FILL_QSSE(next,(int)_begin,(int)_end,nextPivot,FALSE)
	
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


int main()
{
	
	/*int arr[]={1,6,4,67,43,2,56,34,98,2,4,5} , i;*/
	
	int i, arr[]={-34,45,0,54,-567,-567,-76,6,345,2,34,6456,7,43,-67,453,-785,0,674,34,754,34,65,74,54,234,532,4};
	
	for(i=0 ; i<=27 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');

	
	 QuickSortIt(arr,0,27);
	
	for(i=0 ; i<=27 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');
	
	
	return 0;

}







