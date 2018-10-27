
#include <stdio.h>

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif


unsigned long ItFib(unsigned int _n)
{
	unsigned int i;
	unsigned long res1=1,res0=0,tmp;
	
	for (i=2 ; i<=_n ; ++i)
	{
		tmp=res1;
		res1+=res0;
		res0=tmp;
	}
	
	return (_n==0)?0:res1;
}


unsigned long RecFib(unsigned int _n)
{

	if (_n<=1) 
	{
		return _n;
	}
	return RecFib(_n-1)+RecFib(_n-2);
}

int RevArr(char _arr[], size_t _len)
{
	char tmp;
	
	if (_arr == NULL)
	{
		return -1;
	}
	
	if (_len<=1)
	{
		return 0;
	}
	
	tmp=_arr[0];
	_arr[0]=_arr[_len-1];
	_arr[_len-1]=tmp;
	
	RevArr(_arr+1,_len-2);
	
	return 0;
}

int IsPalyndrome(char _arr[], size_t _len)
{
	if(_len <= 1)
	{
		return TRUE;
	}

	return ((_arr[0]==_arr[_len-1])&&IsPalyndrome(_arr+1,_len-2));	
}

char GetLast(char* _str)
{
	if ((*_str=='\0')||(*(_str+1)=='\0'))
	{
		return *_str;
	}
	return GetLast(_str+1);	
}



int main()
{
	/*unsigned int i;
	
	for (i=0 ; i<=50 ; ++i)
	{
		printf("The Fibonacci number of %3u is %5lu(rec) and %5lu(it).\n",i,RecFib(i),ItFib(i));
	}*/
	/*
	size_t i;
	char arr1[]={'a','b','c','d','e','f','g'};
	char arr2[]={'a','b','c','b','a'};
	*/
	/*
	printf("Befor : ");
	
	for(i=0 ; i<7 ; ++i)
	{
		putchar(arr[i]);
	}
	
	RevArr(arr,7);
	printf("\nAfter : ");
	for(i=0 ; i<7 ; ++i)
	{
		putchar(arr[i]);
	}
	putchar('\n');*/
	/*
	for(i=0 ; i<7 ; ++i)
	{
		putchar(arr1[i]);
	}
	printf(" is %s palyndrome.\n\n",IsPalyndrome(arr1,7)?"":"not");
	
	for(i=0 ; i<7 ; ++i)
	{
		putchar(arr2[i]);
	}
	printf(" is %s palyndrome.\n",IsPalyndrome(arr2,5)?"":"not");
	*/
	
	printf("Last char of %s is %c.\n","abcdefg",GetLast("ancdefg"));
	
	
	return 0;
}
