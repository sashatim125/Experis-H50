/*This file contains the API for the Vector data structure.
 *AUTHOR        : Timoshenko Alexander
 *LAST MODIFIED : 12.12.2017
 */
 
#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "../ADTErr.h"
#include <stddef.h>


 
/*Definition of the Vector type*/ 
typedef struct Vector Vector;
 
/*Description :new vector creation with _initialSize and _extensionBblockSize;
 *Input : _initialSize (in elements) , _extensionBlockSize[should NOT be both 0];
 *Output: pointer to the created vector;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_ALLOCATION_FAILED(NOT reported).
 */
Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize);


/*Description :destroction of the vector;
 *Input : _vector - to be destroyed.
 *Output: none;
 *Error : ERR_NOT_INITIALIZED - does nothing , DO NOT use this function more then ONE time.
 */
void    VectorDestroy(Vector* _vector);


/*Description :addition of new element to the end and resizing the array be 1 new block
 *             if nessesary.
 *Input : existing _vector, new _item;
 *Output: status (see Errors)
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_REALLOCATION_FAILED,
 *        ERR_OVERFLOW.
 */
ADTErr  VectorAdd(Vector *_vector,  int  _item);


/*Description :removes the last item from the vector and shrinks the vector
 *             by one block if two are empty if nessesary;
 *Input : the _vector, pointer to the _item returned;
 *Output: removed item in *_itemstatus returned;
 *Error : RR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_REALLOCATION_FAILED,ERR_UNDERFLOW.
 */
ADTErr  VectorDelete(Vector *_vector,  int* _item); /* Remove from end. */


/*Description :get the element from the vector by the index(starts with 0);
 *Input : the _vector, the _index and place(pointer) to the _item;
 *Output: retrieved item in *_item, status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_WRONG_INDEX.
 */
ADTErr  VectorGet(Vector *_vector, size_t _index, int *_item);


/*Description :set the element in the vector by the index(starts with 0);
 *Input : the _vector, the _index and the _item value;
 *Output: status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED,ERR_WRONG_INDEX.
 */
ADTErr  VectorSet(Vector *_vector, size_t _index, int  _item);


/*Description :get number of element int the vector;
 *Input : the _vector and place(pointer) the thr _numOfItems;
 *Output: number of elements in *_numOfItems, status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED.
 */
ADTErr  VectorItemsNum(Vector *_vector, size_t*  _numOfItems);


/*Description :prints the vector;
 *Input : the _vector;
 *Output: prints the vector and returns the status;
 *Error : ERR_OK,ERR_GENERAL,ERR_NOT_INITIALIZED.
 */
void    VectorPrint(Vector *_vector);


#endif/*#ifndef __VECTOR_H__*/
