
/** 
 *  @file DLinkListItr.c
 *  @brief API for the iterators of generic double linked list (data==void*)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com 
 * 
 *  @bug exterminator at work! 
 */

#include "DLinkListCommon.h"

#define IS_WRONG_ITERATOR(itr) (IS_NULL(itr)|| ListItr_Equals((itr),ListItr_Next(itr)) || ListItr_Equals((itr),ListItr_Prev(itr)))


ListItr ListItr_Begin(const List* _list)
{
	if(IS_NULL(_list))
	{
		return NULL;
	}
	
	return (ListItr)(_list->m_head.m_next);
}


ListItr ListItr_End(const List* _list)
{
	if(IS_NULL(_list))
	{
		return NULL;
	}
	
	return (ListItr)(&_list->m_tail);
}


int ListItr_Equals(const ListItr _a, const ListItr _b)
{
	return (_a == _b);

}


ListItr ListItr_Next(ListItr _itr)
{
	if(IS_NULL(_itr))
	{
		return NULL;
	}
	
	return (ListItr)(((Node*)_itr)->m_next);
}


ListItr ListItr_Prev(ListItr _itr)
{
	if(IS_NULL(_itr))
	{
		return NULL;
	}
	
	return (ListItr)(((Node*)_itr)->m_prev);
}


void* ListItr_Get(ListItr _itr)
{
	if(IS_WRONG_ITERATOR(_itr))
	{
		return NULL;
	}
	
	return (void*)(((Node*)_itr)->m_item);
}


void* ListItr_Set(ListItr _itr, void* _element)
{
	void* item;
	
	if(IS_WRONG_ITERATOR(_itr) || IS_NULL(_element))
	{
		return NULL;
	}
	
	item =  ListItr_Get(_itr);

	((Node*)_itr)->m_item = _element;

	return (void*)item;
}


ListItr ListItr_InsertBefore(ListItr _itr, void* _element)
{
	Node *newNode;

	if (IS_NULL(_itr) || (_itr) == ListItr_Prev(_itr))
	{
		return NULL;
	}
	
	if (IS_NULL(newNode=NodeCreate(_element)))
	{
		return NULL;
	}
	
	NodeLinkBefore(newNode,(Node*)_itr);
	
	return (ListItr)newNode;
}


void* ListItr_Remove(ListItr _itr)
{

	if(IS_WRONG_ITERATOR(_itr))
	{
		return NULL;
	}
	
	return (void*)NodeRemove((Node*)_itr);
}

/**  
 * @brief Iterate over all elements in the list.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.  
 * @param[in] _list - vector to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided context, will be sent to _action
 * @returns iterator to the stopped element (end if completed)
 */
ListItr List_ForEach(const List* _list, ElementAction _action, void* _context)
{
	ListItr nextItr, endItr;

	if(IS_NULL(_list)||IS_NULL(_action))
	{
		return 0;
	}
	
	nextItr = ListItr_Begin(_list);
	endItr = ListItr_End(_list);
	
	
	while(!ListItr_Equals(nextItr,endItr))
	{
		if(!_action(ListItr_Get(nextItr),_context))
		{
			break;
		}
		
		nextItr=ListItr_Next(nextItr);	
	}
	return nextItr;
}





