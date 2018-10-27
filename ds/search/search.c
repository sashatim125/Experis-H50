
#include "../ADTErr.h"
#include <stdio.h>


ADTErr LinearSearch(int* _arr, size_t _size, int _data, int* _index)
{
	int i;
	
	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	for(i=0 ; i<_size && _arr[i] != _data ; ++i)
	{
		;
	}
	
	if (i>=_size)
	{
		return ERR_NOT_FOUND;
	}
	
	*_index = i;
	return ERR_OK;
}

ADTErr BinarySearch(int* _arr,size_t _size,int _data, int* _index)
{
	int *left,*right, *middle;
	
	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(0==_size)
	{
		return ERR_NOT_FOUND;
	}
	
	for(left=_arr, right=_arr+_size-1; left <= right ; )
	{
		middle = left+(right-left)/2;
		if(*middle == _data)
		{
			*_index= (int)(middle-_arr);
			return ERR_OK;
			
		}else if(_data < *middle)
		{
			right = middle-1;
		}else
		{
			left = middle+1;
		}
		
	}
	
	return ERR_NOT_FOUND;
}




int main()
{

	int i, num,index,arr[]={-34,45,0,54,-567,-567,-76,6,345,2,34,6456,7,43,-67,453,-785,0,674,34,754,34,65,74,54,234,532,4};
/*
	int i,num,index,arr[]={1,2,2,3,5,6,9,15,25,70};
*/
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');

	printf("Insert number :");
	scanf("%d",&num);
	if(ERR_OK==LinearSearch(arr,28,num,&index))
	{
		printf("\nFound in index %d\n",index);
	}else
	{
		printf("\nNot found\n");
	}
	
	/*
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');
	*/
	
	return 0;

}





