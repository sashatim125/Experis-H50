

/** 
 *  @file stack.c
 *  @brief Implementation of the generic stack over list
 *	
 *  @details  see incode comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */


#include "../list/list.h"
#include "../list/list_itr.h"
#include "stack.h"


Stack*  Stack_Create()
{		
	return (Stack*)List_Create();
}


void Stack_Destroy(Stack* _stack,DestroyFunc _destFunc)
{

	List_Destroy((List**)&_stack,_destFunc);
}


Stack_Result Stack_Push(Stack* _stack, void *_item)
{
	return (Stack_Result)List_PushTail((List*)_stack,_item);
}


Stack_Result Stack_Pop(Stack* _stack, void **_item)
{
	return (Stack_Result)List_PopTail((List*)_stack,_item);
}


Stack_Result Stack_Top(const Stack* _stack, void **_item)
{
	List *list = (List*)_stack;
	
	if(NULL==_stack || NULL==_item)
	{
		return STACK_NOT_INITIALIZED;
	}

	if(List_IsEmpty(list))
	{
		return STACK_UNDERFLOW;
	}
	
	*_item = ListItr_Get(ListItr_Prev(ListItr_End(list)));
	
	return STACK_OK;
}


int Stack_IsEmpty(const Stack* _stack)
{
	return List_IsEmpty((List*)_stack);
}


















