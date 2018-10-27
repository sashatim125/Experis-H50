#ifndef DOUBLE_LINKED_LIST_H
#define DOUBLE_LINKED_LIST_H

#include <stddef.h>  /* size_t */
#include "../ADTErr.h"


/** 
 *  @file DLinkList.h
 *  @brief API for the double linked list (data==int)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug No known bugs! 
 */



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
 * @return NONE
 */
void        ListDestroy(List* _list);

/** 
 * @brief Adds the new element to the head of list  (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[in] _data - new data to store in list
 * @return ADTErr : ERR_OK (OK) , ERR_NOT_INITIALIZED (_list==NULL), 
 * @return ERR_ALLOCATION_FAILED(memory allocation failled).       
 */
ADTErr      ListPushHead(List* _list, int _data);


/** 
 * @brief Adds the new element to the tail of list (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[in] _data - new data to store in list
 * @return ADTErr : ERR_OK (OK) , ERR_NOT_INITIALIZED (_list==NULL), 
 * @return ERR_ALLOCATION_FAILED(memory allocation failled).       
 */
ADTErr 	    ListPushTail(List* _list, int _data);


/** 
 * @brief Removes the element from the head of list (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[out] _data - place to store the removed element's data
 * @return ADTErr : ERR_OK (OK) ,
 * @return ERR_NOT_INITIALIZED (_list==NULL or _data==NULL) - nothing is removed, 
 * @return ERR_UNDERFLOW(the list is empty).       
 */
ADTErr      ListPopHead(List* _list, int* _data);


/** 
 * @brief Removes the element from the tail of list (by O(1))
 * @param[in] _list - exisiting LIST
 * @param[out] _data - place to store the removed element's data
 * @return ADTErr : ERR_OK (OK) ,
 * @return ERR_NOT_INITIALIZED (_list==NULL or _data==NULL) - nothing is removed! 
 * @return ERR_UNDERFLOW(the list is empty).       
 */
ADTErr	    ListPopTail(List* _list, int* _data);


/** 
 * @brief Gets the number of elements in the list
 * @return number of elements in the list; zero if the list is empty or _list==NULL
 */
size_t      ListCountItems(List* _list);



/** 
 * @brief Check if the list is empty
 * @return Zero if list is not empty , non-zero otherwise (or _list==NULL)
 */
int	        ListIsEmpty(List* _list);


/* ListPrint is only for debug (NOT part of the requirments). */
void        ListPrint(List* _list);

#endif /* DOUBLE_LINKED_LIST_H */
