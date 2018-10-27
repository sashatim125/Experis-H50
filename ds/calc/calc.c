/*This file contains the implementation of simple calculator.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#include "stack.h"
#include <math.h>
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

#define OK_CHECK(oper,res) \
	if ((oper)!=res)\
	{\
		StackDestroy(myStack);\
		return ERR_GENERAL;\
	}

static int isDigit(int _c);

static int isOper(int _c);

static int isGrPrec(int _op1, int _op2);

static int doOper(int _left, int _right, int _oper);

ADTErr InfixToPostFix(char *_ifStr, char *_pfStr)
{
	int next,last,shouldPush;
	Stack *myStack;
	ADTErr res;

	if ((_ifStr == NULL)||(_pfStr == NULL))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	myStack=StackCreate(INIT_STACK_SIZE,STACK_BLOCK);
	if (myStack == NULL)
	{
		return ERR_GENERAL;
	}
	
	while((next=*_ifStr++)!='\0')
	{
		if(isDigit(next))
		{
			*_pfStr++=(char)next;
			continue;
		}
		if(isOper(next))
		{
			shouldPush=FALSE;
			while ((res=StackPop(myStack,&last))==ERR_OK)
			{
				if (((isOper(last)&&isGrPrec(next,last))||
				    (last=='(')))
				{
					OK_CHECK(StackPush(myStack,last),ERR_OK)
				else
					{
						shouldPush=TRUE;
						break;
					} 
				}
				*_pfStr++=(char)last;
			}
			if ((res==ERR_UNDERFLOW)||(shouldPush))
			{
				OK_CHECK(StackPush(myStack,next),ERR_OK)
				continue;
			}else
			{
				StackDestroy(myStack);
				return ERR_GENERAL;
			}
			continue;
		}
		if(next=='(') 
		{
			OK_CHECK(StackPush(myStack,next),ERR_OK)
			continue;
		}
		if(next==')')
		{
			while ((res=StackPop(myStack,&last))==ERR_OK)
			{
				if (last=='(')
				{
					break;
				}
				*_pfStr++=(char)last;
			}
			if ((res!=ERR_UNDERFLOW)&&(last!='('))
			{
				StackDestroy(myStack);
				return ERR_GENERAL;
			}
			continue;
		}
	}
	while ((res=StackPop(myStack,&last))==ERR_OK)
		{
			*_pfStr++=(char)last;
		}
	OK_CHECK(res,ERR_UNDERFLOW)

	*_pfStr='\0';
	
	StackDestroy(myStack);
	return ERR_OK;
}

ADTErr MyCalc(char *_pfStr, int *_res)
{
	int next,left,right,res;
	Stack *myStack;

	if ((_pfStr == NULL)||(_res == NULL))
	{
		return ERR_NOT_INITIALIZED;
	}

	myStack=StackCreate(INIT_STACK_SIZE,STACK_BLOCK);
	if (myStack == NULL)
	{
		return ERR_GENERAL;
	}
	
	while((next=*_pfStr++)!='\0')
	{
	
		if(isDigit(next))
			{
				OK_CHECK(StackPush(myStack,next-(int)'0'),ERR_OK)
				continue;
			}
		/*else isOper*/
		OK_CHECK(StackPop(myStack,&right),ERR_OK)
		OK_CHECK(StackPop(myStack,&left),ERR_OK)
		res=doOper(left,right,next);
		OK_CHECK(StackPush(myStack,res),ERR_OK)	
	}
	OK_CHECK(StackPop(myStack,&res),ERR_OK)
	
	*_res=res;
	return ERR_OK;
}


static int isDigit(int _c)
{
	return ((_c>='0')&&(_c<='9'));
}

static int isOper(int _c)
{
	switch (_c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			return TRUE;
		break;
	}
	return FALSE;
}

int isGrPrec(int _op1, int _op2)
{
	switch (_op1)
	{
		case '^':
			switch (_op2)
			{
				case '+':
				case '-':
				case '*':
				case '/':
					return TRUE;
				default :
					return FALSE;		
			}
			break;
			
		case '/':
		case '*':
			switch (_op2)
			{
				case '+':
				case '-':
					return TRUE;
				default :
					return FALSE;		
			}
			break;
		break;
		
		case '+':
		case '-':
			switch (_op2)
			{
				case '+':
				case '-':
					return FALSE;
				default :
					return TRUE;		
			}
			break;
	}
	/*default*/
	return FALSE;
}

static int doOper(int _left, int _right, int _oper)
{
	int res;
/*	
	printf("left=%d , right=%d, oper=%c\n",_left,_right,_oper);
*/
	switch (_oper)
	{
		case '+':
			res=_left+_right;
			break;
		case '-':
			res=_left-_right;
			break;
		case '*':
			res=_left*_right;
			break;
		case '/':
			if (_right==0)
			{
				return 0;
			}
			res=_left/_right;
			break;
		case '^':
			res=(int)pow((double)_left,(double)_right);
			break;
	}
	return res;
}





