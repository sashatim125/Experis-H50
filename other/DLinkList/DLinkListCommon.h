
#ifndef __D_LINKED_LIST_COMMON__
#define __D_LINKED_LIST_COMMON__

/** 
 *  @file DLinkListCommon.h
 *  @brief internal definitions for the generic double linked list (data==void*)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Anonimous 
 * 
 *  @bug exterminator at work! 
 */
 
 #include "DLinkList.h"
 #include "DLinkListItr.h"

  
 #ifndef TRUE
 #define TRUE 1
 #endif
 
 #ifndef FALSE
 #define FALSE 0
 #endif 
 
#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcd
#endif /*MAGIC_NUMBER*/

#ifndef IS_NULL
#define IS_NULL(ptr) (NULL==(ptr))
#endif /*IS_NULL*/


typedef struct Node Node;

struct Node
{
	void *m_item;
	
	Node *m_prev;
	Node *m_next;
};

struct List
{	
	int m_magicNum;
	
	Node m_head;
	Node m_tail;
};
 
 
/*allocating memory for a new node*/
Node* NodeCreate(void *_item);
 
 /*links the node before the given node*/
void NodeLinkBefore(Node* _node, Node* _nextNode);
 
/*removes the node from the list(unlinks and destroys).
 *item is returned;
 *do not call with head or tail!
 */
void* NodeRemove(Node* _node);
 
 
#endif /*__D_LINKED_LIST_COMMON__*/
 
 
 
 
 
