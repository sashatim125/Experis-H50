
#include "../ADTErr.h"
#include <stdio.h>


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


ADTErr InsertionSort(int _arr[], size_t _begin, size_t _end, size_t _step)
{
	size_t i, num;

	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_begin > _end)
	{
		return ERR_WRONG_INDEX;
	}
	
	if(_end-_begin <_step)
	{
		return ERR_OK;
	}
	num=(_end-_begin)%_step;
	_end=(num>0)?(_end+num-_step):_end;
	
	for(i=_begin+_step ; i <= _end ; i+=_step)
	{
		DownBubble(_arr,i,_begin,_step);	
	}
	
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

	
	InsertionSort(arr,0,27,1);
	
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');
	
	
	return 0;

}





