

#ifndef __DOUBLE_LINKED_LIST_ITERATOR_H__
#define __DOUBLE_LINKED_LIST_ITERATOR_H__

/** 
 *  @file DLinkListItr.h
 *  @brief API for the iterators of generic double linked list (data==void*)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Anonimous 
 * 
 *  @bug exterminator at work! 
 */


#include "DLinkList.h"

typedef int	(*ElementAction)(void* _element, void* _context);

typedef void* ListItr;

/** 
 * @brief Get itertator to the list's beginning
 *
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 */
ListItr ListItr_Begin(const List* _list);

/** 
 * @brief Get itertator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 */
ListItr ListItr_End(const List* _list);

/** 
 * @brief retruns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro
 */
int ListItr_Equals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get itertator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 */
ListItr ListItr_Next(ListItr _itr);

/** 
 * @brief Get itertator to the previous element
 * @warning if _itr is begin iterator(NOT the first element) it will be returned
 */
ListItr ListItr_Prev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 *
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at or NULL if pointing to end/begin
 */
void* ListItr_Get(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing to
 * @return the data from the node to be changed
 */
void* ListItr_Set(ListItr _itr, void* _element);

/** 
 * @brief Inserts a new node before node the iterator is pointing at
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItr_InsertBefore(ListItr _itr, void* _element);

/** 
 * @brief Removes the node the iterator is pointing at
 *
 * @params _itr : A list iterator
 * @return the removed data
 */
void* ListItr_Remove(ListItr _itr);



/**  
 * @brief Iterate over all elements in the list.
 * @details The user provided _action function will be called for each element
 *          if _action return a zero for an element the iteration will stop.  
 * @param[in] _list - vector to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided context, will be sent to _action
 * @returns iterator to the stopped element (end if completed)
 */
ListItr List_ForEach(const List* _list, ElementAction _action, void* _context);


#endif /*__DOUBLE_LINKED_LIST_ITERATOR_H__*/



