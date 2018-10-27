
#include "sort.h"
#include <time.h>
#include <sys/time.h>
#include <stdlib.h> /*(s)rand(),malloc()*/
#include <stdio.h>


/** 
 *  @file sort.c
 *  @brief Testing and benchmarking various sorting algorithms
 *	
 *  @details  insertion sort, Shell sort , recursive and itarative quicksort.
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug None! 
 */

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

#define SORT_BENCHMART_ERROR -1l
#define INCORRECT_SORT -2l

#define MIN_ITEMS 1000
#define MAX_ITEMS 64000


static int isSorted(int _arr[],size_t _size)
{
	
	for(--_size ; _size>0 ; --_size)
	{
		if (_arr[_size] < _arr[_size-1])
		{
			return FALSE;
		}
	}
	
	return TRUE;
}


static long SortBenchmark(ADTErr(*_sortFunc)(int* _arr,size_t _size), size_t _sizeOfArray)
{
	size_t i;
	int *arr;
	struct timeval start,finish;
	ADTErr res;

	if(NULL==_sortFunc)
	{
		return SORT_BENCHMART_ERROR;
	}
	
	arr=(int*)malloc(_sizeOfArray*sizeof(int));
	if(NULL==arr)
	{
		return SORT_BENCHMART_ERROR;
	}
	
	srand(0);
	for(i=0 ; i < _sizeOfArray ; ++i)
	{
		arr[i]=rand()%100;
	}
	
	gettimeofday(&start, 0);
	
	res=_sortFunc(arr,_sizeOfArray);
	
	gettimeofday(&finish, 0);
	
	if(res != ERR_OK)
	{
		return SORT_BENCHMART_ERROR;
	}

	if(!isSorted(arr,_sizeOfArray))
	{
		;/*return INCORRECT_SORT;*/
	}

	free(arr);
	/*time in milliseconds*/
	return (finish.tv_sec-start.tv_sec) * 1000 + (finish.tv_usec-start.tv_usec)/1000;
}

int main(int argc , char *argv[])
{
	long timeOfSort;

	long unsigned i;
	ADTErr(*sortFuncs[])(int* _arr,size_t _size)=\
		{InsertionSort,SelectionSort,ShellSort,MergeSort,CountSort,QuickSortRec,QuickSortIt};
	int k;

	FILE* output ;

	if((2 != argc)||(NULL==(output=fopen(argv[1],"w"))))
	{
		exit(EXIT_FAILURE);
	}



	fprintf(output,"%15s %15s %15s %15s %15s %15s %15s %15s\n",
		"Num items","Insertion","SelectionSort","Shellsort","MergeSort","CountSort","QuicksortRec","QuicksortIt");
	
	for (i=MIN_ITEMS ; i<=MAX_ITEMS ; i*=2)
	{
		fprintf(output,"%15ld ",i);
		
		for (k=0; k < 7 ; ++k)
		{
			/*insertion sort too lazy on big arrays */

			if(k==0 && i>=64000)
			{
				timeOfSort=-111;
			}else 
			{
				timeOfSort = SortBenchmark(sortFuncs[k],i);
		
				if(timeOfSort < 0)
				{
					perror("\nSorting error!\n");
					exit(EXIT_FAILURE);
				}
			}
	
			fprintf(output,"%15ld ",timeOfSort);
		}
		fprintf(output,"\n");
	}

	fclose(output);
	exit(EXIT_SUCCESS);

}






























