
/*This file contains API for Dynamic Alocation data structure
 *(stack of integers).
 *All parametes of size are number of INTEGERS.
 */
 
#include <stdlib.h>
 
typedef enum {DA_OK=0, POINTER_NOT_INITIALIZED, DATA_OVERFLOW,
              REALLOC_FAIL, DATA_UNDERFLOW} DA_error;

typedef struct DA da_t; 
 
/*Description :This function creates the data structure(DS).
 *Input : size - size of DS, inc_block_size - size of incrementation block.
 "!!!size and inc_block_size should NOT be BOTH 0!!! 
 *Output: pointer to new DS.
 *Error : NULL if unsuccessful.
 */
da_t* createDA(size_t size, size_t inc_block_size);

/*Description :This function destroys the existing data structure(DS).
 *Input : ptr - pointer to the DS to be destoyed.
 *Output: NONE.
 *Error : **do nothing** if null pointer error.
 */
void destroyDA(da_t* ptr);

/*Description :This function add new element to the DS.
 *Input : ptr - pointer to DS, data - new element.
 *Output: status(see defined above DA_error(s)).
 *Error : same.
 */
DA_error insertDA(da_t* ptr,int data);

/*Description :This function removes the last element from the DS.
 *Input : ptr - pointer to to DS, data - pointer to the removed element.
 *Output: status(see defined above DA_error(s)).
 *Error : same.
 */
DA_error removeDA(da_t* ptr,int* data);

/*Description :This function prints the DS.
 *Input : ptr - pointer to to DS.
 *Output: status(see defined above DA_error(s)).
 *Error : same.
 */
DA_error printDA(da_t* ptr);















