

#include "../ADTErr.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define BASE 0xffu
#define BITS 8u

/*POWER OF TWO BASE*/
void countSortByDigit(unsigned *_arrIn, unsigned *_arrOut, size_t _size, unsigned _digit)
{
	unsigned *counters, mask, offset ;
	int  i, j;

	if(NULL==_arrIn || NULL==_arrOut)
	{
		return ;
	
	}
	
	counters = (unsigned*)calloc(BASE,sizeof(unsigned));
	if(NULL==counters)
	{
		return ;
	}
	
	offset=((_digit-1)*BITS);
	
	mask=BASE<<offset;
	
	
	for(j=0 ; j<(int)_size ; ++j)
	{
		++(counters[(mask&_arrIn[j])>>offset]);
	}
	
	for(i=1 ; i<(int)BASE ; ++i)
	{
		counters[i]=counters[i]+counters[i-1];
	}
	
	for(j=(int)_size-1 ; j>=0 ; --j)
	{
		--(counters[(mask&_arrIn[j])>>offset]);
		_arrOut[counters[(mask&_arrIn[j])>>offset]] = _arrIn[j];
	}
	
	free(counters);
}


ADTErr RadixSort(unsigned *_arr, size_t _size)
{

	unsigned *buff;
	unsigned digit , numOfSorts = sizeof(int) ;
	
	if(NULL==_arr)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(1 >= _size)
	{
		return ERR_OK;
	}
	
	buff = (unsigned*)malloc(_size*sizeof(int));
	if (NULL==buff)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	for (digit=1 ; digit <= numOfSorts ; digit+=2)
	{
		countSortByDigit(_arr,buff,_size,digit);
		countSortByDigit(buff,_arr,_size,digit+1);
	}
	
	free(buff);
	return ERR_OK;

}




int main()
{
/*
	int i, arr[]={34,45,0,54,57,30,76,6,345,2,34,56,7,43,67,453,78,0,674,34,754,34,65,74,54,24,52,4};
*/
	unsigned i , arr[]={59842,14521,125,7,78952,5,11,6,5214,69845};/* , arr2[10]={0};*/

	for(i=0 ; i<10 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');

	
	RadixSort(arr,10);
	
	for(i=0 ; i<10 ; ++i)
	{
		printf("%4d ",arr[i]);
	}
	putchar('\n');
	
	return 0;

}





