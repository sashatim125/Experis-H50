

#include <stdlib.h>
#include <stdio.h>






void countSort(int *_arrIn, int *_arrOut, size_t _size, unsigned range)
{
	unsigned *counters;
	int i,j;


	if(NULL==_arrIn || NULL==_arrOut)
	{
		return ;
	
	}
	
	counters = (unsigned*)calloc(range+1,sizeof(unsigned));
	if(NULL==counters)
	{
		return ;
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
}







int main()
{
/*
	int i, arr[]={34,45,0,54,57,30,76,6,345,2,34,56,7,43,67,453,78,0,674,34,754,34,65,74,54,24,52,4};
*/
	int i , arr[]={9,9,9,7,6,5,4,3,2,1} , arr2[10]={0};

	for(i=0 ; i<10 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');

	
	countSort(arr,arr2,10,10);
	
	for(i=0 ; i<10 ; ++i)
	{
		printf("%4d ",arr2[i]);
	}
	putchar('\n');
	
	return 0;

}




















