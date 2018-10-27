

#include "DLinkListCommon.h"
#include <stdlib.h> 
#include <stdio.h>



/** 
 *  @file DlinkList.c
 *  @brief Implementation of the generic double linked list
 *	
 *  @details  The .............
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */





/*freeing memory of the node and destroying the item*/
static void NodeDestroy(Node* _node,void (*_elementDestroy)(void* _item));


/*unlinks the node from the list.
 *do not call with head or tail!
 */
static void NodeUnlink(Node* _node);



List* ListCreate(void)
{
	List *newList;
	
	newList=(List*)malloc(sizeof(List));
	
	if (IS_NULL(newList))
	{
		return NULL;
	}
	
	newList->m_head.m_prev=&newList->m_head;
	newList->m_head.m_next=&newList->m_tail;
	
	newList->m_tail.m_prev=&newList->m_head;
	newList->m_tail.m_next=&newList->m_tail;
	
	newList->m_magicNum=MAGIC_NUMBER;
	
	return newList;
}


void ListDestroy(List** _list, void (*_elementDestroy)(void* _item))
{

	Node *curr, *next;

	if(IS_NULL(_list)||IS_NULL(*_list)||(MAGIC_NUMBER != (*_list)->m_magicNum))
	{
		return;
	}
	
	for (curr=(*_list)->m_head.m_next ; curr!=&((*_list)->m_tail) ; curr=next)
	{
		next=curr->m_next;
		NodeDestroy(curr,_elementDestroy);
	}
	
	(*_list)->m_magicNum=0;
	
	free(*_list);
	
	*_list = NULL;
}


List_Result ListPushHead(List* _list, void* _item)
{
	Node *newNode;

	if(IS_NULL(_list))
	{
		return LIST_UNITIALIZED_ERROR;
	}
	
	newNode=NodeCreate(_item);
	
	if(IS_NULL(newNode))
	{
		return LIST_ALLOCATION_ERROR;
	}
	
	NodeLinkBefore(newNode,_list->m_head.m_next);
	
	return LIST_SUCCESS;
}

List_Result ListPushTail(List* _list, void* _item)
{
	Node *newNode;

	if(IS_NULL(_list))
	{
		return LIST_UNITIALIZED_ERROR;
	}
	
	newNode=NodeCreate(_item);
	
	if(IS_NULL(newNode))
	{
		return LIST_ALLOCATION_ERROR;
	}
	
	NodeLinkBefore(newNode,&_list->m_tail);
	
	return LIST_SUCCESS;
}

List_Result ListPopHead(List* _list, void** _item)
{

	if(IS_NULL(_list)||IS_NULL(_item))
	{
		return LIST_UNITIALIZED_ERROR;
	}
	
	if(ListIsEmpty(_list))
	{
		return LIST_UNDERFLOW;
	}

	*_item=NodeRemove(_list->m_head.m_next);
	
	return LIST_SUCCESS;
}

List_Result ListPopTail(List* _list, void** _item)
{

	if(IS_NULL(_list)||IS_NULL(_item))
	{
		return LIST_UNITIALIZED_ERROR;
	}
	
	if(ListIsEmpty(_list))
	{
		return LIST_UNDERFLOW;
	}
	
	*_item=NodeRemove(_list->m_tail.m_prev);
	
	return LIST_SUCCESS;
}


size_t ListCountItems(List* _list)
{
	size_t i;
	Node *next;

	if(IS_NULL(_list))
	{
		return 0;
	}
	
	for(next = _list->m_head.m_next , i=0 ; next != &(_list->m_tail) ; (next = next->m_next) , ++i)
	{
	}
	
	return i;
}


int ListIsEmpty(List* _list)
{
	return (IS_NULL(_list)||(_list->m_head.m_next == &(_list->m_tail)));
}


/*
size_t List_ForEach(const List* _list, ElementAction _action, void* _context)
{
	size_t i;
	Node *next;

	if(IS_NULL(_list)||IS_NULL(_action))
	{
		return 0;
	}
	
	for(next = _list->m_head.m_next , i=1 ; next != &(_list->m_tail) ; (next = next->m_next) , ++i)
	{
		if(!_action(next->m_item,i,_context))
		{
			break;
		}
	}

	return i-1;
}
*/



/*allocating memory for a new node*/
Node* NodeCreate(void *_item)
{
	Node *newNode;
	
	newNode=(Node*)malloc(sizeof(Node));
	
	if(IS_NULL(newNode))
	{
		return NULL;
	}
	
	newNode->m_item=_item;
	
	return newNode;	
}

/*freeing memory of the node and destroying the item*/
static void NodeDestroy(Node* _node,void (*_elementDestroy)(void* _item))
{
	if(IS_NULL(_node))
	{
		return;
	}
	if(!IS_NULL(_elementDestroy))
	{
		_elementDestroy(_node->m_item);
	}
	
	free(_node);
}


/*links the node before the given node*/
void NodeLinkBefore(Node* _node, Node* _nextNode)
{

	_node->m_prev=_nextNode->m_prev;
	_node->m_next=_nextNode;
	
	_node->m_prev->m_next=_node;
	_node->m_next->m_prev=_node;
}

static void NodeUnlink(Node* _node)
{
	_node->m_prev->m_next=_node->m_next;
	_node->m_next->m_prev=_node->m_prev;
}


/*removes the node from the list(unlinks and frees the memory).
 *item is returned;
 *do not call with head or tail!
 */
void* NodeRemove(Node* _node)
{
	void* item;
	
	item=_node->m_item;
	
	NodeUnlink(_node);
		
	free(_node);
	
	return item;
}












