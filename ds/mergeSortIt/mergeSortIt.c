

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
static void Merge(int *_begin, int *_middle, int *_end)
{
	int *leftP , *rightP , rightVal;
	
	rightP = _middle+1;
	while (rightP<=_end)
	{
		leftP = rightP-1;
		rightVal = *rightP;
		while (leftP>=_begin)
		{
			if(*leftP > rightVal)
			{
				*(leftP+1)=*leftP;
				--leftP;
			}else 
			{
				break;
			}
		}
		*(leftP+1)=rightVal;
		++rightP;
	}
}

static void MyMergeSort(int *_begin, int *_end)
{
	int *middle;
	
	if((_end-_begin)<=0)
	{
		return;
	}
	
	middle = _begin + (_end-_begin)/2;
	
	MyMergeSort(_begin,middle);
	MyMergeSort(middle+1,_end);
	
	Merge(_begin,middle,_end);

}

void MergeSort(int _arr[], size_t _size)
{
	if(NULL==_arr)
	{
		return ;
	}
	
	if(1 >= _size)
	{
		return ;
	}
	
	MyMergeSort(_arr,_arr+_size-1);
}

*/



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



/*
ORIGINAL
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
*/

void MergeSort(int _arr[], size_t _size)
{
	int *buff, *arrIn ,*arrOut , *temp;
	size_t currSize , step , middle, end;

	if(NULL==_arr)
	{
		return ;
	}
	
	if(1 >= _size)
	{
		return ;
	}
	
	buff = (int*)malloc(_size*sizeof(int));
	if (NULL==buff)
	{
		return;
	}
	
	arrIn=_arr;
	arrOut=buff;
	
	for(currSize=2 ; currSize/2<_size  ; currSize*=2)
	{
		for(step=0 ; step < _size ; step+=currSize)
		{
			middle = step+currSize/2-1;
			end = step+currSize-1;
			
			if (middle >= _size)
			{
				middle = _size-1;
			}
			if(end >= _size)
			{
				end = _size-1;
			}
			
			Merge(arrIn,arrOut,step,middle,end);
		}
		temp=arrIn;
		arrIn=arrOut;
		arrOut=temp;
	}
	
	if(arrIn != _arr)
	{
		memcpy(_arr,arrOut,_size);
	}
	
	free(buff);
}


int main()
{

	int i, arr[]={-34,45,0,54,-567,30,-76,6,345,2,34,6456,7,43,-67,453,-785,0,674,34,754,34,65,74,54,234,532,4};
/*
	int i,arr[]={10,9,8,7,6,5,4,3,2,1};
*/
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');

	
	MergeSort(arr,28);
	
	for(i=0 ; i<28 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');
	
	return 0;

}




















