
#include "DLinkList.h"
#include <stdlib.h> 
#include <stdio.h>



/** 
 *  @file DlinkKist.c
 *  @brief Implementation of the double linked list
 *	
 *  @details  The .............
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug No known bugs! 
 */
 
 #ifndef TRUE
 #define TRUE 1
 #endif
 
 #ifndef FALSE
 #define FALSE 0
 #endif 
 
 #ifndef MAGIC_NUMBER
 #define MAGIC_NUMBER 0XABCDEF
 #endif  


typedef struct Node Node;

struct Node
{
	int m_data;
	Node *m_prev;
	Node *m_next;
};

struct List
{
	Node m_head;
	Node m_tail;
	size_t m_numOfItems;
};


/*allocating memory for a new node*/
static Node* NodeCreate(int _data);

/*freeng memory for the node*/
static void NodeDestroy(Node* _node);

/*links the node after the given node
static void NodeLinkAfter(Node* _node, Node* _prevNode);
*/
/*links the node before the given node*/
static void NodeLinkBefore(Node* _node, Node* _nextNode);

/*unlinks the node from the list.
 *do not call with head or tail!
 */
static void NodeUnlink(Node* _node);

/*removes the node from the list(unlinks and destroys).
 *data is returned;
 *do not call with head or tail!
 */
static int NodeRemove(Node* _node);

/*prints the node's data*/
static void NodePrint(Node* _node);

/*gets the next node - usefull for iterations*/
static Node* NodeGetNext(Node* _node);


List* ListCreate(void)
{
	List *newList;
	
	newList=(List*)malloc(sizeof(List));
	
	if (NULL==newList)
	{
		return NULL;
	}
	
	newList->m_head.m_prev=NULL;
	newList->m_head.m_next=&newList->m_tail;
	newList->m_tail.m_prev=&newList->m_head;
	newList->m_tail.m_next=NULL;
	newList->m_numOfItems=0;
	
	newList->m_head.m_data=MAGIC_NUMBER;
	
	return newList;
}


void ListDestroy(List* _list)
{

	Node *curr, *next;

	if((NULL==_list)||(MAGIC_NUMBER != _list->m_head.m_data))
	{
		return;
	}
	
	for (curr=_list->m_head.m_next ; curr!=&_list->m_tail ; curr=next)
	{
		next=curr->m_next;
		NodeDestroy(curr);
	}
/*	
	while (!ListIsEmpty(_list))
	{
		NodeRemove(_list->m_head.m_next);
	}
*/	
	_list->m_head.m_data=0;
	free(_list);
}


ADTErr ListPushHead(List* _list, int _data)
{
	Node *newNode;

	if(NULL==_list)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	newNode=NodeCreate(_data);
	
	if(NULL==newNode)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	NodeLinkBefore(newNode,_list->m_head.m_next);
	++(_list->m_numOfItems);
	
	return ERR_OK;
}

ADTErr ListPushTail(List* _list, int _data)
{
	Node *newNode;

	if(NULL==_list)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	newNode=NodeCreate(_data);
	
	if(NULL==newNode)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	NodeLinkBefore(newNode,&_list->m_tail);
	++(_list->m_numOfItems);
	
	return ERR_OK;
}

ADTErr ListPopHead(List* _list, int* _data)
{

	if((NULL==_list)||(NULL==_data))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(ListIsEmpty(_list))
	{
		return ERR_UNDERFLOW;
	}

	*_data=NodeRemove(_list->m_head.m_next);
	
	--(_list->m_numOfItems);
	
	return ERR_OK;
}

ADTErr ListPopTail(List* _list, int* _data)
{

	if((NULL==_list)||(NULL==_data))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(ListIsEmpty(_list))
	{
		return ERR_UNDERFLOW;
	}
	
	*_data=NodeRemove(_list->m_tail.m_prev);
	
	--(_list->m_numOfItems);
	
	return ERR_OK;
}


size_t ListCountItems(List* _list)
{
	if(NULL==_list)
	{
		return 0;
	}
	
	return _list->m_numOfItems;
}


int ListIsEmpty(List* _list)
{
	return ((NULL==_list)||(0 == _list->m_numOfItems));
}



void ListPrint(List* _list)
{
	Node *nextNode;
	
	if(NULL==_list)
	{
		return;
	}
	
	nextNode=NodeGetNext(&_list->m_head);
	
	putchar('\n');
	while(nextNode!=&_list->m_tail)
	{
		NodePrint(nextNode);
		nextNode=NodeGetNext(nextNode);
	}
	putchar('\n');
}




/*allocating memory for a new node*/
static Node* NodeCreate(int _data)
{
	Node *newNode;
	
	newNode=(Node*)malloc(sizeof(Node));
	
	if(NULL==newNode)
	{
		return NULL;
	}
	
	newNode->m_data=_data;
	
	return newNode;	
}

/*freeng memory for the node*/
static void NodeDestroy(Node* _node)
{
	if(NULL==_node)
	{
		return;
	}
	free(_node);
}

/*links the node after the given node
static void NodeLinkAfter(Node* _node, Node* _prevNode)
{

	_node->m_prev=_prevNode;
	_node->m_next=_prevNode->m_next;
	
	_node->m_next->m_prev=_node;
	_node->m_prev->m_next=_node;
}
*/
/*links the node before the given node*/
static void NodeLinkBefore(Node* _node, Node* _nextNode)
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


/*removes the node from the list(unlinks and destroys).
 *data is returned;
 *do not call with head or tail!
 */
static int NodeRemove(Node* _node)
{
	int data;
	
	data=_node->m_data;
	NodeUnlink(_node);	
	NodeDestroy(_node);
	
	return data;
}

static void NodePrint(Node* _node)
{
	printf("%d ",_node->m_data);
}

static Node* NodeGetNext(Node* _node)
{
	return _node->m_next;
}










