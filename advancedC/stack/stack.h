
 
#ifndef __STACK_H__
#define __STACK_H__

/** 
 *  @file stack.h
 *  @brief Definitions of the generic stack
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */


typedef struct Stack Stack;

typedef void(*DestroyFunc)(void *_item) ;


typedef enum Stack_Result
{
	STACK_OK = 0,
	STACK_NOT_INITIALIZED,
	STACK_ALLOCATION_FAILED,
	STACK_NULL_ELEMENT_ERROR,
	STACK_UNDERFLOW
} Stack_Result;

 
/** 
 * @brief Create a stack
 * 
 * @returns a pointer to the created stack.
 * @retval NULL on failure due to allocation failure
 */
Stack*  Stack_Create();


/** 
 * @brief Destroy stack
 * @details Destroys the stack completely 
 *          optionally destroys elements using user provided function
 *
 * @params[in] _stack : The previously created stack returned via Stack_Create
 * @params[in] _elementDestroy : A function pointer to be used to destroy elements inserted into the stack
 *             or a null if no such destroy is required
 */
void    Stack_Destroy(Stack* _stack,DestroyFunc _destFunc);


/** 
 * @brief Add element to top of stack
 * @details time complexity: O(1).
 *
 * @params _stack A previously created stack ADT returned via Stack_Create
 * @params _item An item to add to the stack
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the stack is not initialized
 * @retval LIST_NULL_ELEMENT_ERROR  if _item is NULL
 * @retval LIST_ALLOCATION_ERROR on memory allocation failure
 */
Stack_Result  Stack_Push(Stack* _stack, void *_item);


/** @brief Remove element from stack's top
 *  @details if successfull, stores a pointer to the removed item in _item
 *  time complexity O(1).
 *
 * @params _stack : A previously created stack ADT returned via Stack_Create
 * @params _pItem: To store a pointer to the removed item in
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the stack or _pItem are not initialized
 * @retval LIST_UNDERFLOW  if the stack is empty
 */
Stack_Result  Stack_Pop(Stack* _stack, void **_pItem);


 /** @brief Get the element from stack's top(without removing)
 *  @details if successfull, stores a pointer to the item in _item
 *  time complexity O(1).
 *
 * @params _stack : A previously created stack ADT returned via Stack_Create
 * @params _pItem: To store a pointer to the top item in
 * @returns error code
 * @retval LIST_SUCCESS on success
 * @retval LIST_UNINITIALIZED_ERROR if the stack or _pItem are not initialized
 * @retval LIST_UNDERFLOW  if the stack is empty
 */
Stack_Result  Stack_Top(const Stack* _stack, void **_pItem);


/** 
 * @brief Check if the stack is empty (by O(1))
 * @return Zero if stack is not empty , non-zero otherwise (or if _stack==NULL)
 */
int Stack_IsEmpty(const Stack* _stack);



#endif/*#ifndef __STACK_H__*/
