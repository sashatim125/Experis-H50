/*This file contains the API for the Vector data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#ifndef __STACK_H__
#define __STACK_H__

#include "../ADTErr.h"
#include <stddef.h>

 
/*Definition of the Vector type*/ 
typedef struct Stack Stack;
 
/*Description :new stack creation with _size and _blockSize;
 *Params : _size (in elements) , _blockSize[should NOT be both 0];
 *Return: pointer to the created stack;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_ALLOCATION_FAILED(NOT reported).
 */
Stack*  StackCreate( size_t _size, size_t _blockSize);


/*Description :destroction of the stack;
 *Params : _stack - to be destroyed.
 *Return: none;
 *Error : ERR_NOT_INITIALIZED - does nothing , DO NOT use this function more then ONE time.
 */
void    StackDestroy(Stack* _stack);


/*Description :addition of new element to the top and resizing the stack be 1 new block bigger
 *             if nessesary.
 *Params : existing _stack, new _item;
 *Return: status (see Errors)
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_REALLOCATION_FAILED,
 *        ERR_OVERFLOW.
 */
ADTErr  StackPush(Stack* _stack, int  _item);


/*Description :removes the top item from the stack and shrinks the stack
 *             by one block if two are empty if nessesary;
 *Params : the _vector, pointer to the _item returned;
 *Return: status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_REALLOCATION_FAILED,ERR_UNDERFLOW.
 */
ADTErr  StackPop(Stack* _stack, int* _item);


/*Description :get the top element from the vector by the index(starts with 0);
 *Params : the _vector and place(pointer) to the _item;
 *Return: status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_UNDERFLOW.
 */
ADTErr  StackTop(Stack* _stack, int* _item);


/*Description :checks if the stack is empty;
 *Params : the _stack;
 *Return: true(1) or false(0) [ true for ERR_NOT_INITIALIZED];
 *Error : ---.
 */
int     StackIsEmpty(Stack* _stack);


/*Description :prints the stack;
 */
void    StackPrint(Stack *_stack);


#endif/*#ifndef __STACK_H__*/
