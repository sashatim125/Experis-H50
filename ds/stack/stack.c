/*This file contains the implementation for the Stack data structure
 *using the Vector data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 11.12.2017
 */

#include "stack.h"
#include "vector.h"
#include <stdio.h>
#include <stdlib.h>
 
/*Definition of the Stack type*/ 
struct Stack
{
    Vector *m_vector;
};

Stack*  StackCreate( size_t _size, size_t _blockSize)
{
	Stack *st;
	
	st=(Stack*)malloc(sizeof(Stack));
		
	if (st==NULL)
	{
		return NULL;
	}
	if ((st->m_vector=VectorCreate(_size,_blockSize))==NULL)
	{
		free(st);
		return NULL;
	}
	
	return st;
}

void    StackDestroy(Stack* _stack)
{
	
	if (_stack!=NULL)
	{
		VectorDestroy(_stack->m_vector);
		free(_stack);
	}
}

ADTErr  StackPush(Stack* _stack, int  _item)
{
	if(_stack==NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorAdd(_stack->m_vector,_item);
}


ADTErr  StackPop(Stack* _stack, int* _item)
{
	
	if((_stack==NULL)||(_item==NULL))
	{
		return ERR_NOT_INITIALIZED;
	}
	return VectorDelete(_stack->m_vector,_item);
}


ADTErr  StackTop(Stack* _stack, int* _item)
{
	ADTErr res;
	size_t num;	

	if((_stack==NULL)||(_item==NULL))
	{
		return ERR_NOT_INITIALIZED;
	}
	if ((res=VectorItemsNum(_stack->m_vector,&num))!=ERR_OK)
	{
		return res;
	}
	if (num==0)
	{
		return ERR_UNDERFLOW;
	}
	return VectorGet(_stack->m_vector,num-1,_item);
}

int     StackIsEmpty(Stack* _stack)
{
	size_t num;
		
	if(_stack==NULL)
	{
		return 1;
	}
	if (VectorItemsNum(_stack->m_vector,&num)!=ERR_OK)
	{
		return 1;
	}
	return (num==0);
}


void    StackPrint(Stack *_stack)
{
	if(_stack==NULL)
	{
		return;
	}
	VectorPrint(_stack->m_vector);
}

