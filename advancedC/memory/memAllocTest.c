

#include "memAlloc.h"

#include <stdio.h>

#define _BITS 8

#define _MSB_ON (((Block)1) << (sizeof(Block)*_BITS-1) )

#define _GET_BLOCK(blockPtr) (*((Block*)(blockPtr)))

#define _IS_FREE(blockPtr) (!(_GET_BLOCK(blockPtr) & _MSB_ON))

#define _GET_BLOCK_SIZE(blockPtr)  (*((Block*)(blockPtr)) & ~_MSB_ON)


int main()
{
	
	char buff[64]={0};
	void *ibuff;
	void *alBlock1, *alBlock2;
	int i;
	
	if(NULL!=(ibuff = initMem(buff+1,63)))
	{
		printf("initMem OK\n");
	}
	
	for(i=0; i<15 ; ++i)
	{
		printf("%c%u ",_IS_FREE((Block*)ibuff+i)?'F':'A',_GET_BLOCK_SIZE((Block*)ibuff+i));
	}
	printf("\n");

	if(NULL!=(alBlock1 = allocMem(ibuff,15)))
	{
		printf("allocMem1 OK\n");
	}
	
	for(i=0; i<15 ; ++i)
	{
		printf("%c%u ",_IS_FREE((Block*)ibuff+i)?'F':'A',_GET_BLOCK_SIZE((Block*)ibuff+i));
	}
	printf("\n");
	
	
	if(NULL!=(alBlock2 = allocMem(ibuff,2)))
	{
		printf("allocMem2 OK\n");
	}
	for(i=0; i<15 ; ++i)
	{
		printf("%c%u ",_IS_FREE((Block*)ibuff+i)?'F':'A',_GET_BLOCK_SIZE((Block*)ibuff+i));
	}
	printf("\n");

	releaseMem(alBlock2);
	for(i=0; i<15 ; ++i)
	{
		printf("%c%u ",_IS_FREE((Block*)ibuff+i)?'F':'A',_GET_BLOCK_SIZE((Block*)ibuff+i));
	}
	printf("\n");
	
	if(NULL!=(alBlock2 = allocMem(ibuff,30)))
	{
		printf("allocMem1 OK\n");
	}
	
	for(i=0; i<15 ; ++i)
	{
		printf("%c%u ",_IS_FREE((Block*)ibuff+i)?'F':'A',_GET_BLOCK_SIZE((Block*)ibuff+i));
	}
	printf("\n");
	
	releaseMem(alBlock1);
	for(i=0; i<15 ; ++i)
	{
		printf("%c%u ",_IS_FREE((Block*)ibuff+i)?'F':'A',_GET_BLOCK_SIZE((Block*)ibuff+i));
	}
	printf("\n");
	
	
	return 0;
}

