
/*This file contains API for Dynamic Alocation data structure
 *(stack of integers).
 *All parametes of size are number of INTEGERS.
 */
 
#include <stdlib.h>
 
#define DA_OK 0
#define POINTER_NOT_INITIALIZED -1
#define DATA_OVERFLOW -2
#define REALLOC_FAIL -3
#define DATA_UNDERFLOW -4
 
 
/*Description :This function creates the data structure(DS).
 *Input : size of DS
 *Output: pointer to new DS.
 *Error : NULL if unsuccessful.
 */
int* createDA(size_t size);

/*Description :This function destroys the existing data structure(DS).
 *Input : pointer to the DS
 *Output: NONE.
 *Error : **do nothing** if null pointer error.
 */
void destroyDA(int* ptr);

/*Description :This function add new element to the DS.
 *Input : ptr-pointer to pointer to DS, data-new element, size-size of the DS,
 *        num_of_elements-number of elements, inc_block_size-size of incrementation block
          (unused unless is needed).
 *Output: status(see the #defined constants).
 *Error : same.
 */
int insertDA(int** ptr,int data, size_t* size, size_t* num_of_elements, size_t inc_block_size);

/*Description :This function removes the last element from the DS.
 *Input : ptr-pointer to to DS, data-pointer to the removed element,
 *        num_of_elements-number of elements.
 *Output: status(see the #defined constants).
 *Error : same.
 */
int removeDA(int* ptr,int* data, size_t* num_of_elements);

/*Description :This function prints the DS.
 *Input : ptr-pointer to to DS,
 *        num_of_elements-number of elements.
 *Output: status(see the #defined constants).
 *Error : same.
 */
int printDA(int* ptr,size_t num_of_elements);















