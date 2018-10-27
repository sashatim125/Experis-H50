
#include "stack.h"
#include <stdio.h>


#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE 
#define FALSE 0
#endif

#define INIT_STACK_SIZE 10
#define STACK_BLOCK 5
#define STRING_SIZE 100

int isOpenPar(int _par)
{
	switch (_par)
	{
		case '{':
		case '(':
		case '[':
			return TRUE;
	}
	return FALSE;
}

int isClosePar(int _par)
{
	switch (_par)
	{
		case '}':
		case ')':
		case ']':
			return TRUE;
	}
	return FALSE;
}

int getClosePar(int _openPar)
{
	int closePar;
	switch(_openPar)
	{
		case '{' :
			closePar='}';
			break;
		case '[' :
			closePar=']';
			break;
		case '(' :
			closePar=')';
			break;
	}
	return closePar;
}


int parsAreCorr(char* _str)
{

	Stack *myStack;
	int nextChar,lastPar;
	
	ADTErr res;

	if (_str == NULL)
	{
		return FALSE;
	}
	
	myStack = StackCreate(INIT_STACK_SIZE,STACK_BLOCK);
	if (myStack == NULL)
	{
		return FALSE;
	}
	
	while((nextChar=*(_str++))!='\0')
	{
		if(nextChar == '|')
		{
			res=StackTop(myStack,&lastPar);
			if ((res==ERR_UNDERFLOW)||(lastPar!='|'))
			{
				if(StackPush(myStack,nextChar)!=ERR_OK)
				{
					StackDestroy(myStack);
					return FALSE;
				}
			}else if(StackPop(myStack,&lastPar)!=ERR_OK)
			{
				StackDestroy(myStack);
				return FALSE;	
			}
			continue;			
		}
	
		if ((isOpenPar(nextChar))&&(StackPush(myStack,getClosePar(nextChar))!=ERR_OK))
		{
			StackDestroy(myStack);
			return FALSE;
		}
		
		if (isClosePar(nextChar))
		{
			if ((StackPop(myStack,&lastPar)!=ERR_OK)||(nextChar!=lastPar))
			{
				StackDestroy(myStack);
				return FALSE;
			}
		}	
	}
	res=StackIsEmpty(myStack);
	
	return res;
}

int main()
{
	char str[STRING_SIZE];
	
	printf("Enter your string to check the parentheses :\n");
	scanf("%s",str);
	
	if (parsAreCorr(str))
	{
		printf("Everithing is OK !\n");
	}else
	{
		printf("There is an ERROR !\n");
	}

	return 0;
}


















