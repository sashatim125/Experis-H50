
#include <stdlib.h>
#include <stdio.h>
#include "bst.h"
#include "../ADTErr.h"


/** 
 *  @file bst.c
 *  @brief Implementation of API for the binary search tree(of ints)
 *	
 *  @details  See the functions description
 *  
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */

 #ifndef TRUE
 #define TRUE 1
 #endif
 
 #ifndef FALSE
 #define FALSE 0
 #endif 

typedef struct Node Node;

struct Node
{
    int     m_data;
    Node*   m_left;
    Node*   m_right;
};

struct Tree
{
    Node*   m_root;
};

/*creates a new node*/
static Node* NodeCreate(int _data);

/*destroys the sub-tree from the _node)*/
static void NodeDestroy(Node* _node);

/*searches the tree for the data
 *if not found returns the place to insert
 */
static Node* FindData(Node* _node, int _data, int* _isFound);

/*prints the sub-tree of the _node*/
static void PrintNodePreorder(Node* _node);

static void PrintNodeInorder(Node* _node);

static void PrintNodePostorder(Node* _node);


Tree* TreeCreate()
{
	Tree* newTree;
	
	newTree=(Tree*)malloc(sizeof(Tree));
	if(NULL==newTree)
	{
		return NULL;
	}
	
	newTree->m_root=NULL;
	
	return newTree;
}


void TreeDestroy(Tree* _tree)
{
	if(NULL==_tree)
	{
		return;
	}

	NodeDestroy(_tree->m_root);
	free(_tree);
}


ADTErr TreeInsert(Tree* _tree, int _data)
{
	Node  *newNode, *placeNode;
	int isFound;

	if(NULL==_tree)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	newNode=NodeCreate(_data);
	if(NULL==newNode)
	{
		return ERR_ALLOCATION_FAILED;
	}
	
	if(NULL==_tree->m_root)
	{
		_tree->m_root=newNode;
		return ERR_OK;
	}
	
	placeNode=FindData(_tree->m_root,_data,&isFound);
	if(isFound)
	{
		return ERR_DATA_DUPLICATION;
	}
	
	if(_data < placeNode->m_data)
	{
		placeNode->m_left=newNode;
	}else
	{
		placeNode->m_right=newNode;
	}
	
	return ERR_OK;
}


int TreeIsDataFound(Tree* _tree, int _data)
{
	int isFound;
	
	if(NULL==_tree)
	{
		return FALSE;
	}
	
	FindData(_tree->m_root,_data,&isFound);
	
	return isFound;
}


void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
	if(NULL==_tree)
	{
		return;
	}
	
	switch (_traverseMode)
	{
		case PRE_ORDER :
			PrintNodePreorder(_tree->m_root);
			break;
			
		case IN_ORDER :
			PrintNodeInorder(_tree->m_root);
			break;
			
		case POST_ORDER :
			PrintNodePostorder(_tree->m_root);
			break;
	}
	putchar('\n');
}

static Node* NodeCreate(int _data)
{
	Node* newNode;

	newNode=(Node*)malloc(sizeof(Node));
	
	if(NULL==newNode)
	{
		return NULL;
	}
	
	newNode->m_data = _data;
	newNode->m_left = newNode->m_right = NULL;
	
	return newNode;

}

static void NodeDestroy(Node* _node)
{
	if(NULL==_node)
	{
		return;
	}
	
	NodeDestroy(_node->m_left);
	NodeDestroy(_node->m_right);
	free(_node);
}


static Node* FindData(Node* _node, int _data, int* _isFound)
{
	if(NULL==_node)
	{
		*_isFound=FALSE;
		return NULL;
	}
	
	if(_data==_node->m_data)
	{
		*_isFound=TRUE;
		return _node;
	}
	
	if(_data<_node->m_data)
	{
		if(NULL==_node->m_left)
		{
			*_isFound=FALSE;
			return _node;
		}else
		{
			return FindData(_node->m_left,_data,_isFound);
		}
	} else
	{
		if(NULL==_node->m_right)
		{
			*_isFound=FALSE;
			return _node;
		}else
		{
			return FindData(_node->m_right,_data,_isFound);
		}
	}
}



static void PrintNodePreorder(Node* _node)
{
	if(NULL==_node)
	{
		return;
	}

	printf("%d ",_node->m_data);
	PrintNodePreorder(_node->m_left);
	PrintNodePreorder(_node->m_right);
}

static void PrintNodeInorder(Node* _node)
{
	if(NULL==_node)
	{
		return;
	}
	PrintNodeInorder(_node->m_left);
	printf("%d ",_node->m_data);
	PrintNodeInorder(_node->m_right);
}

static void PrintNodePostorder(Node* _node)
{
	if(NULL==_node)
	{
		return;
	}
	
	PrintNodePostorder(_node->m_left);
	PrintNodePostorder(_node->m_right);
	printf("%d ",_node->m_data);
}




















