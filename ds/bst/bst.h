#ifndef __BST_H__
#define __BST_H__

#include "../ADTErr.h"


/** 
 *  @file bst.h
 *  @brief API for the binary search tree(of ints)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */

typedef struct Tree Tree;

typedef enum
{
    PRE_ORDER,
    IN_ORDER,
    POST_ORDER
} TreeTraverse;

/** 
 * @brief Create a new BST
 * @param[in] NONE 
 * @return newly created BST or NULL on failure
 */
Tree*   TreeCreate();

/** 
 * @brief Destroys the BST.Call no more then ONE time.
 * @param[in] _tree - the BST to be destroyed 
 * @return NONE
 */
void    TreeDestroy(Tree* _tree);


/** 
 * @brief Adds the new element to the BST(avg O(logn),worst O(n))
 * @param[in] _tree - exisiting BST
 * @param[in] _data - new data to store in BST
 * @return ADTErr : ERR_OK (OK) , ERR_NOT_INITIALIZED (_tree==NULL), 
 * @return ERR_ALLOCATION_FAILED(memory allocation failled),
 * @return ERR_DATA_DUPLICATION .       
 */
ADTErr  TreeInsert(Tree* _tree, int _data);


/** 
 * @brief Checks if the _data in on the tree(avg O(logn),worst O(n))
 * @param[in] _tree - exisiting BST
 * @param[out] _data - the search value
 * @return ZERO if data is not on the tree,
 * @return NON_ZERO otherwise       
 */
int     TreeIsDataFound(Tree* _tree, int _data);


/** 
 * @brief Prints the tree in the _taverseMode fashion
 * @param[in] _tree - exisiting BST
 * @param[out] _traverseMode - the tree walking fashion
 * @return NONE      
 */
void    TreePrint(Tree* _tree, TreeTraverse _traverseMode);

#endif /*__BST_H__*/
