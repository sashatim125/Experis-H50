 
#include "bin_tree.h"
#include <stdlib.h> 

/** 
 *  @file bin_tree.c
 *  @brief Implementation of the Generic Binary Search Tree
 *	
 *  @details  The .............
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */

#ifndef TRUE
#define TRUE 1
#endif
 
#ifndef FALSE
#define FALSE 0
#endif 
 
#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcd
#endif /*MAGIC_NUMBER*/

#define IS_LEFT_SON(node)  ((NULL==(node))?FALSE:(node)==((node)->m_parent->m_left))

#define IS_RIGHT_SON(node) ((NULL==(node))?FALSE:(node)==((node)->m_parent->m_right))

#define REMOVE_NODE(node,replace) \
{\
	if(IS_LEFT_SON(node))\
	{\
		(node)->m_parent->m_left=(replace);\
	}\
	\
	if(IS_RIGHT_SON(node))\
	{\
		(node)->m_parent->m_right=(replace);\
	}\
	if(NULL!=(replace))\
	{\
		(replace)->m_parent=(node)->m_parent;\
	}\
}

typedef struct BSTNode BSTNode;

struct BSTNode
{
	void *m_item;
	
	BSTNode* m_parent;
	BSTNode* m_left;
	BSTNode* m_right;
	
};

struct BSTree
{
	int m_magicNum;
	
	BSTNode m_sent;
	
	LessComparator m_less;	
};




static void BSTNodeDestroy(BSTNode* _node, void (*_destroyer)(void*))
{
	if(NULL != _node->m_left)
	{
		BSTNodeDestroy(_node->m_left,_destroyer);
	}
	
	if(NULL != _node->m_right)
	{
		BSTNodeDestroy(_node->m_right,_destroyer);
	}

	if(NULL != _destroyer)
	{
		_destroyer(_node->m_item);
	}
		
	free(_node);
}




 
BSTree* BSTree_Create(LessComparator _less)
{
	BSTree *newTree;
	
	if(NULL == _less)
	{
		return NULL;
	}
	
	if(NULL==(newTree=malloc(sizeof(BSTree))))
	{
		return NULL;
	}
	
	newTree->m_sent.m_parent = &newTree->m_sent;
	newTree->m_sent.m_left = NULL;
	newTree->m_sent.m_right = NULL;
	newTree->m_less=_less;
	
	newTree->m_magicNum = MAGIC_NUMBER;
	
	return newTree;
}


void BSTree_Destroy(BSTree* _tree, void (*_destroyer)(void*))
{
	if(NULL==_tree || MAGIC_NUMBER != _tree->m_magicNum)
	{
		return;
	}
	
	if(NULL != _tree->m_sent.m_left)
	{
		BSTNodeDestroy(_tree->m_sent.m_left,_destroyer);
	}
	
	_tree->m_magicNum = 0;
		
	free(_tree);
}



static BSTNode* BSTNodeCreate(BSTNode* _parent, void* _item)
{
	BSTNode* newNode;
	
	if(NULL==(newNode=malloc(sizeof(BSTNode))))
	{
		return NULL;
	}
	
	newNode->m_item = _item;
	newNode->m_left = newNode->m_right = NULL;
	newNode->m_parent = _parent;
	
	return newNode;
}



/*return a pointer to the new node with the item */
static BSTNode* BSTNodeInsert(BSTNode* _node, void* _item, LessComparator _less)
{
	if(_less(_item,_node->m_item))
	{
		if(NULL==_node->m_left)
		{			
			return (_node->m_left = BSTNodeCreate(_node,_item));
		}else
		{
			return BSTNodeInsert(_node->m_left,_item,_less);
		}
	}else
	{
		if(!_less(_node->m_item,_item)) /**<_item == _node->m_item*/
		{
			return NULL;
		}
		if(NULL==_node->m_right)
		{
			return (_node->m_right = BSTNodeCreate(_node,_item));
		}else
		{
			return BSTNodeInsert(_node->m_right,_item,_less);
		}
	}
}



BSTreeItr BSTree_Insert(BSTree* _tree, void* _item)
{
	BSTNode* newNode;

	if(NULL==_tree)
	{
		return NULL;
	}
	
	if(NULL==_tree->m_sent.m_left)
	{
		newNode = _tree->m_sent.m_left = _tree->m_sent.m_right =\
			BSTNodeCreate(&(_tree->m_sent),_item);
	}else
	{
		newNode = BSTNodeInsert(_tree->m_sent.m_left,_item,_tree->m_less);
	}
	
	return (NULL!=newNode) ? (BSTreeItr)newNode : (BSTreeItr)(&_tree->m_sent);
}


BSTreeItr BSTreeItr_Begin(const BSTree* _tree)
{
	BSTNode *begin;

	if(NULL==_tree)
	{
		return NULL;
	}
	
	begin = _tree->m_sent.m_left;

	if(NULL==begin)
	{
		return(BSTreeItr)(&_tree->m_sent);
	}
	
	while(NULL!=begin->m_left)
	{
		begin = begin->m_left;
	}
	
	return (BSTreeItr)begin;
}

BSTreeItr BSTreeItr_End(const BSTree* _tree)
{
	if(NULL==_tree)
	{
		return NULL;
	}

	return(BSTreeItr)(&_tree->m_sent);
}

void* BSTreeItr_Get(BSTreeItr _it)
{

	if(NULL==_it)
	{
		return NULL;
	}

	return ((BSTNode*)_it)->m_item;
}


int BSTreeItr_Equals(BSTreeItr _a, BSTreeItr _b)
{
	return (_a == _b);
}


BSTreeItr BSTreeItr_Next(BSTreeItr _it)
{
	BSTNode *curr;

	if(NULL==_it)
	{
		return NULL;
	}

	curr = (BSTNode*)_it;
	
	if(NULL!=curr->m_right)
	{
		curr = curr->m_right;
		while(NULL!=curr->m_left)
		{
			curr = curr->m_left;
		}
		return (BSTreeItr)curr;
	}
	
	while(IS_RIGHT_SON(curr))
	{
		curr = curr->m_parent;
	}
	
	return (BSTreeItr)(curr->m_parent);
}


BSTreeItr BSTreeItr_Prev(BSTreeItr _it)
{
	BSTNode *curr;

	if(NULL==_it)
	{
		return NULL;
	}

	curr = (BSTNode*)_it;
	
	if(NULL!=curr->m_left)
	{
		curr = curr->m_left;
		while(NULL!=curr->m_right)
		{
			curr = curr->m_right;
		}
		return (BSTreeItr)curr;
	}
	
	while(IS_LEFT_SON(curr))
	{
		curr = curr->m_parent;
	}
	
	return (BSTreeItr)(curr->m_parent);
}

 
void* BSTreeItr_Remove(BSTreeItr _it)
{	
	BSTNode *curr;
	void *item;

	if(NULL==_it)
	{
		return NULL;
	}

	curr = (BSTNode*)_it;
	item=curr->m_item;
	
	if(NULL==curr->m_left)
	{
		if(NULL==curr->m_right) /**<is leaf*/
		{
			if(IS_LEFT_SON(curr))
			{
				curr->m_parent->m_left=NULL;
			}else
			{
				curr->m_parent->m_right=NULL;
			}
			free(curr);
		}else
		{
			REMOVE_NODE(curr,curr->m_right);
			free(curr);
		}
	}else
	{
		if(NULL==curr->m_right) 
		{
			REMOVE_NODE(curr,curr->m_left);
			free(curr);
		}else
		{
			curr->m_item=BSTreeItr_Remove(BSTreeItr_Next((BSTreeItr)curr));
		}
	}
	return item;
}



static const BSTNode* BSTNode_FindFirst(const BSTNode* _node, PredicateFunction _predicate, void* _context)
{
	const BSTNode *node;

	if(NULL==_node)
	{
		return NULL;
	}
	
	node = BSTNode_FindFirst(_node->m_left,_predicate,_context);
	
	if(NULL!=node)
	{
		return node;
	}
	
	if(_predicate(_node->m_item,_context))
	{
		return _node;
	}
	
	return BSTNode_FindFirst(_node->m_right,_predicate,_context);
}



BSTreeItr BSTree_FindFirst(const BSTree* _tree, PredicateFunction _predicate, void* _context)
{

	const BSTNode *node;

	if(NULL==_tree)
	{
		return NULL;
	}
	
	if(NULL==_predicate)
	{
		return BSTreeItr_End(_tree);
	}
	
	node = BSTNode_FindFirst(_tree->m_sent.m_left,_predicate,_context);
	
	return (NULL!=node) ? (BSTreeItr)node :(BSTreeItr)(&_tree->m_sent);
}



static const BSTNode* BSTNode_ForEachInorder(const BSTNode* _node, ActionFunction _action, void* _context)
{
	const BSTNode *node;

	if(NULL==_node)
	{
		return NULL;
	}
	
	node = BSTNode_ForEachInorder(_node->m_left,_action,_context);
	
	if(NULL!=node)
	{
		return node;
	}
	
	if(!_action(_node->m_item,_context))
	{
		return _node;
	}
	
	return BSTNode_ForEachInorder(_node->m_right,_action,_context);
}


static const BSTNode* BSTNode_ForEachPreorder(const BSTNode* _node, ActionFunction _action, void* _context)
{
	const BSTNode *node;

	if(NULL==_node)
	{
		return NULL;
	}
	
	if(!_action(_node->m_item,_context))
	{
		return _node;
	}
	
	node = BSTNode_ForEachPreorder(_node->m_left,_action,_context);
	
	if(NULL!=node)
	{
		return node;
	}
	
	return BSTNode_ForEachPreorder(_node->m_right,_action,_context);
}


static const BSTNode* BSTNode_ForEachPostorder(const BSTNode* _node, ActionFunction _action, void* _context)
{
	const BSTNode *node;

	if(NULL==_node)
	{
		return NULL;
	}
	
	
	node = BSTNode_ForEachPreorder(_node->m_left,_action,_context);
	
	if(NULL!=node)
	{
		return node;
	}
	
	node =  BSTNode_ForEachPreorder(_node->m_right,_action,_context);
	
		
	if(NULL!=node)
	{
		return node;
	}
	
	if(!_action(_node->m_item,_context))
	{
		return _node;
	}else
	{
		return NULL;
	}
}



BSTreeItr BSTree_ForEach(const BSTree* _tree, TreeTraversalMode _mode,
                 ActionFunction _action, void* _context)
{
	const BSTNode *node;

	if(NULL==_tree)
	{
		return NULL;
	}
	
	if(NULL==_action)
	{
		return BSTreeItr_End(_tree);
	}
	
	switch(_mode)
	{
		case BSTREE_TRAVERSAL_PREORDER :
			node = BSTNode_ForEachPreorder(_tree->m_sent.m_left,_action,_context);
			break;
			
		case BSTREE_TRAVERSAL_INORDER :
			node = BSTNode_ForEachInorder(_tree->m_sent.m_left,_action,_context);
			break;
			
		case BSTREE_TRAVERSAL_POSTORDER :
			node = BSTNode_ForEachPostorder(_tree->m_sent.m_left,_action,_context);
			break;
			
		default:
			node=NULL;
			break;
	}
	
	return (NULL!=node) ? (BSTreeItr)node :(BSTreeItr)(&_tree->m_sent);
}















