

#ifndef __DOUBLE_LINKED_LIST_H__
#define __DOUBLE_LINKED_LIST_H__


/** 
 *  @file DLinkList.h
 *  @brief API for the generic double linked list (data==void*)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work! 
 */

#include <stddef.h>  /* size_t */


typedef enum List_Result {
	LIST_SUCCESS,
	LIST_UNITIALIZED_ERROR,				/**< Uninitialized pointer error 	*/
	LIST_ALLOCATION_ERROR,				/**< realloc error on grow   */
	LIST_UNDERFLOW

} List_Result;

typedef struct List List;

/** 
 * @brief Create a new List container
 * @param[in] NONE 
 * @return newly created List or null on failure
 */
List*       ListCreate(void);


/** 
 * @brief Destroys the List container.Call no more then ONE time.
 * @param[in] _list - list to be destroyed 
 * @param[in] _elementDestroy : A function pointer to be used to destroy all elements in the vector
 *             or a null if no such destroy is required
 * @return NONE
 */
void        ListDestroy(List** _list, void (*_elementDestroy)(void* _item));

/** 
 * @brief Adds the new element to the head of list  (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[in] _data - new data to store in list
 * @return status
 * @retval LIST_SUCCESS (OK) ,
 * @retval LIST_UNITIALIZED_ERROR 
 * @retval LIST_ALLOCATION_ERROR   
 */
List_Result      ListPushHead(List* _list, void* _item);


/** 
 * @brief Adds the new element to the tail of list (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[in] _data - new data to store in list
 * @return status
 * @retval LIST_SUCCESS (OK) ,
 * @retval LIST_UNITIALIZED_ERROR 
 * @retval LIST_ALLOCATION_ERROR        
 */
List_Result	    ListPushTail(List* _list, void* _item);


/** 
 * @brief Removes the element from the head of list (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[out] _data - place to store the removed element's data
 * @retval LIST_SUCCESS (OK) ,
 * @retval LIST_UNITIALIZED_ERROR 
 * @retval LIST_UNDERFLOW (empty list)       
 */
List_Result      ListPopHead(List* _list, void** _item);


/** 
 * @brief Removes the element from the tail of list (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[out] _data - place to store the removed element's data
 * @retval LIST_SUCCESS (OK) ,
 * @retval LIST_UNITIALIZED_ERROR 
 * @retval LIST_UNDERFLOW (empty list)       
 */
List_Result	    ListPopTail(List* _list, void** _item);


/** 
 * @brief Gets the number of elements in the list (by O(n))
 * @return number of elements in the list; zero if the list is empty or _list==NULL
 */
size_t      ListCountItems(List* _list);



/** 
 * @brief Check if the list is empty (by O(1))
 * @return Zero if list is not empty , non-zero otherwise (or if _list==NULL)
 */
int         ListIsEmpty(List* _list);


#endif /* __DOUBLE_LINKED_LIST_H__ */


