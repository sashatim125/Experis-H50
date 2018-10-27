/*This file contains the main and multiplication table print function.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 13.12.2017
 */

#include <stdio.h>

static void PrintMultLine(int _n, int _times)
{
	int i,next;
	
	for(i=0 , next=_n ; i<_times ; ++i , next+=_n)
	{
		printf("%3d",next);
	}
	putchar('\n');
}

void MultTablePrint(int _n1,int _n2)
{
	if (_n1<=0)
	{
		return;		
	}
	MultTablePrint(_n1-1,_n2);
	PrintMultLine(_n1,_n2);
}

int main()
{
	int i,j;
	printf("Welcome to the multiplication table programm !\n");
	printf("Please enter 2 numbers:");
	
	scanf("%d%d",&i,&j);
	
	MultTablePrint(i,j);
	
	return 0;
}

