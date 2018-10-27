
#include "../ADTErr.h"
#include <stdio.h>

static void Swap(int *a, int *b)
{
	int temp;
	
	temp=*a;
	*a=*b;
	*b=temp;
}

static void DownBubblePtr(int *_startPtr , int *_finishPtr, size_t _step)
{
	int* i;
	
	_finishPtr+=_step;

	for(i=_startPtr ; i>= _finishPtr ; i-=_step)
	{		
		if(*i < *(i-_step))
		{
			Swap(i,i-_step);
		}else
		{
			break;
		}
	}
}

static void MyInsertionSortPtr(int *_beginPtr, int * _endPtr, size_t _step)
{
	int *i, num;
	
	if(_endPtr-_beginPtr <_step)
	{
		return ;
	}
	num=(int)((_endPtr-_beginPtr)%(long)_step);
	_endPtr=(num>0)?(_endPtr+num-_step):_endPtr;
	
	for(i=_beginPtr+_step ; i <= _endPtr ; i+=_step)
	{
		DownBubblePtr(i,_beginPtr,_step);	
	}
	
}

ADTErr InsertionSortPtr(int _arr[], size_t _size)
{
	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(0==_size)
	{
		return ERR_OK;
	}
	
	MyInsertionSortPtr(_arr,_arr+_size-1,1);	
	
	return ERR_OK;
 }


int main()
{

	int i, arr[]={-34,45,0,54,-567,-567,-76,6,345,2,34,6456,7,43,-67,453,-785,0,674,34,754,34,65,74,54,234,532,4};
	
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');

	
	InsertionSortPtr(arr,28);
	
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');
	
	
	return 0;

}





