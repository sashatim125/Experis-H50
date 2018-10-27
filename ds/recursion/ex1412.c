/*This file contains the main and other function(class exercises of 14.12.2017.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 16.12.2017
 */
 
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
 
/* 
unsigned int GcdFind(unsigned int a, unsigned int b)
{
 	if (a==0)
 	{
 		return a;
 	}
 	if (b==0)
 	{
 		return b;
 	}
 	
 	if (a==b)
 	{
 	return a;
 	}
 	
 	if (a>b)
 	{
 		return GcdFind(a-b,b);
 	}
 	else
 	{
		return GcdFind(a,b-a);
	}
}


int MyStrcmp(char *_str1, char *_str2)
{
	int res;

	if (*_str1=='\0')
	{
		if (*_str2=='\0')
		{
			return 0;
		}
		else 
		{
		return (0-*_str2);
		}
	}
	else
	{
		if (*_str2=='\0')
		{
			return (*_str1);
		}
		else
		{
			res=(*_str1-*_str2);
			return (res!=0)?res:MyStrcmp(_str1+1,_str2+1);
		}
	}
}

float Avr(int arr[],int n)
{

	if (n==1)
	{
		return (float)arr[0];
	}
	return (Avr(arr+1,n-1)*(float)(n-1)+(float)arr[0])/(float)n;
}
*/

/*
void Bubble(int _arr[],size_t _size)
{
	int temp;
	
	if(_size<=1)
	{
		return;
	}
	if(_arr[0]>_arr[1])
	{
		temp=_arr[1];
		_arr[1]=_arr[0];
		_arr[0]=temp;
	}
	Bubble(_arr+1,_size-1);
}

void BubbleSort(int _arr[],size_t _size)
{
	if(_size<=1)
	{
		return;
	}
	Bubble(_arr,_size);
	BubbleSort(_arr,_size-1);
	
}
*/

/*Stack sort recursive function using the Bubble Sort*/
/*
typedef struct Node Node;
struct Node 
{
	int m_data;
	Node* m_next;
};


static int NodeBubble(Node* _head)
{
	int temp, swaps=0;
	if (_head==NULL)
	{
		return 0;
	}
	
	for(; _head->m_next!=NULL ; _head=_head->m_next)
	{
		if(_head->m_data > _head->m_next->m_data)
		{
			temp=_head->m_data;
			_head->m_data=_head->m_next->m_data;
			_head->m_next->m_data=temp;
			++swaps;
		}
	}
	return swaps;
}
*/
/*call with(stack,NULL,NULL)*/
/*
int StackSort(Stack* _theStack, Node* _head, Node* _prev)
{
	Node currNode;
	int wereSwaps;
		
	if(StackIsEmpty(_theStack))
	{
		return 1;
	}
	
	if(_prev!=NULL)
	{
		_prev->m_next=&currNode;
	}
	StackPop(_theStack,&currNode.m_data);
	
	wereSwaps = StackSort(_theStack, (_head!=NULL)? _head: &currNode, &currNode);
	currNode.m_next=NULL;
	
	if (wereSwaps)
	{
		wereSwaps = NodeBubble(_head);
	}
	StackPush(_theStack,currNode.m_data);
	
	return wereSwaps;	
}
*/


static void QueensPrint(int _queens[], int _Rows)
{
	int i,j;
	
	for(i=0 ; i<_Rows ; ++i)
	{
		for (j=1 ; j<=_Rows ; ++j)
		{
			printf("%c ",(_queens[i]==j)?'Q':'+');
		}
		putchar('\n');
	}
	putchar('\n');
}

static int IsGoodSolution(int _queens[],int _currRow)
{
	int i,currPos;
	
	for(currPos=_queens[_currRow], i=0 ; i<_currRow ; ++i)
	{
		if((_queens[i]==currPos)||
		  ((_queens[i]-currPos)==(i-_currRow))||
		  ((currPos-_queens[i])==(i-_currRow)))
		{
			return 0;
		}
	}
	return 1;
}

/*define int queens[numbers_of_rows]={0};
 *call with (queens,0,numbers_of_rows)
 */
int QueensSolver(int _queens[],int _currRow, int _Rows)
{
	int i,start;

	if(_currRow == _Rows)
	{
		/*for ALL solutions*/
		QueensPrint(_queens,_Rows);
		return 0;
		
		/*for one random solution
		QueensPrint(_queens,_Rows);
		return 1;
		*/
	}
	srand((unsigned int)time(0));
	start=rand()%_Rows+1;
	
	for(i=start ; i<(start+_Rows) ; ++i)
	{
		_queens[_currRow]=i%_Rows+1;
		if(IsGoodSolution(_queens,_currRow)&&
		   QueensSolver(_queens,_currRow+1,_Rows))
		{
			return 1;
		}
	}
	return 0;
}





















 
int main(){

/*GcdFind test*/

/*	unsigned int a,b;
	
	printf("Enter 2 natural numbers :");
	scanf("%u%u",&a,&b);
	
	printf("The GCD of %u and %u is %u.\n",a,b,GcdFind(a,b));
*/

/*MyStrcmp test and Avr test*/

/*	char str1[]="abcd";
	char str2[]="aacd";
	
	int arr[]={1,2,3,4,5};
	
	
	printf("The result of comparison of \"%s\" and \"%s\" is %d.\n",str1,str2,MyStrcmp(str1,str2));
	
	printf("The average is %.3f.\n",Avr(arr,5)); 
	
*/

/*StackSort test
	
	Stack *st;
	int item;
	
	st=StackCreate(10,10);

	item=1;
	printf("Lets fill the stack (0 for end):\n");	
	while (item!=0)
	{ 		
		scanf("%d",&item);
		StackPush(st,item);
	}
		
	StackSort(st,NULL,NULL);
	printf("The sorted stack is :\n");
	
	while (StackPop(st,&item)==ERR_OK)
	{
		printf("%d ",item);
	}
	putchar('\n');

	StackDestroy(st);
*/

int queens[8]={0} ;

/*define int queens[numbers_of_rows]={0};
 *call with (queens,0,numbers_of_rows)
 */

	QueensSolver(queens,0,8);

	return 0;
}
 
 
 
 
