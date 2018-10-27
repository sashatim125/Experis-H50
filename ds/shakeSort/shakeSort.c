
#include "shakeSort.h"

/*#include <stdio.h>*/


static int UpBubble(Vector *_vec, size_t _start , size_t _finish)
{
	size_t i;
	int item1,item2 , countSwap;
	
	countSwap=0;

	for(i=_start ; i < _finish ; ++i)
	{
		VectorGet(_vec,i,&item1);
		VectorGet(_vec,i+1,&item2);
		
		if(item1 > item2)
		{
			VectorSet(_vec,i,item2);
			VectorSet(_vec,i+1,item1);
			++countSwap;
		}
	}
	
	return countSwap;
}

static int DownBubble(Vector *_vec, size_t _start , size_t _finish)
{
	size_t i;
	int item1,item2, countSwap;
	
	countSwap=0;

	for(i=_start ; i > _finish ; --i)
	{
		VectorGet(_vec,i,&item1);
		VectorGet(_vec,i-1,&item2);
		
		if(item1 < item2)
		{
			VectorSet(_vec,i,item2);
			VectorSet(_vec,i-1,item1);
			++countSwap;
		}
	}
	
	return countSwap;
}



ADTErr ShakeSort(Vector *_vec)
{
	size_t i,j;

	if(NULL==_vec)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	VectorItemsNum(_vec,&j);
	if(0 == j)
	{
		return ERR_OK;
	}
	
	for(i=0 , --j ; i < j ; ++i , --j)
	{
		if ((0 == UpBubble(_vec,i,j))||(0 == DownBubble(_vec,j-1,i)))
		{
			break;
		}
	
	}
	
	return ERR_OK;

}
/*
int main()
{
	Vector* vec;
	int i;

	vec=VectorCreate(10,10);
	
	for (i=5 ; i>=1 ; --i)
	{
		VectorAdd(vec,i);		
	}
	for (i=15 ; i>=6 ; --i)
	{
		VectorAdd(vec,i);		
	}
	for (i=25 ; i>=16 ; --i)
	{
		VectorAdd(vec,i);		
	}

	VectorPrint(vec);
	
	ShakeSort(vec);
	
	VectorPrint(vec);
	
	return 0;

}
*/




