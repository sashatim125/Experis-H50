#ifndef __HEAP_H__
#define __HEAP_H__

#include "../vector/vector.h"
#include "../ADTErr.h"

/** 
 *  @file heap.h
 *  @brief API for the the heap(of ints)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */

typedef struct Heap Heap;

/** 
 * @brief Create a new heap (O(n))- DO NOT CHANGE THE VECTOR
 * @param[in] _vec - Vector that contains the elements for heap creation
 *            the vector IS NOT duplicated
 * @return newly created heap or NULL on failure
 */
Heap*   HeapBuild(Vector* _vec);

/** 
 * @brief Destroys the heap, but NOT the inner vector.Call no more then ONE time.
 * @param[in] _heap - the heap to be destroyed 
 * @return NONE
 */
void    HeapDestroy(Heap* _heap);



/** 
 * @brief Adds the new element to the heap(worst O(log n))
 * @param[in] _heap - existing heap
 * @param[in] _data - new data to store in heap
 * @return ADTErr : ERR_OK (OK) , ERR_NOT_INITIALIZED (_heap==NULL), 
 * @return ERR_REALLOCATION_FAILED,ERR_OVERFLOW.     
 */
ADTErr  HeapInsert(Heap* _heap, int _data);


/** 
 * @brief get the VALUE the maximum element from the heap (worst O(1))
 * @param[in] _heap - existing heap
 * @param[in] _data - place to store the maximum
 * @return ADTErr : ERR_OK (OK) , ERR_NOT_INITIALIZED (_heap==NULL),
 * @return ERR_UNDERFLOW(heap is empty)      
 */
ADTErr  HeapMax(Heap* _heap, int* _data);



/** 
 * @brief removes the maximum from the heap and returns it as parameter(worst O(log n))
 * @param[in] _heap - existing heap
 * @param[out] _data - maximum
 * @return ADTErr : ERR_OK (OK) , ERR_NOT_INITIALIZED (_heap==NULL), 
 * @return ERR_REALLOCATION_FAILED,ERR_UNDERFLOW(heap is empty)        
 */
ADTErr  HeapExtractMax(Heap* _heap, int* _data); 


/** 
 * @brief get the size of heap(worst O(1))
 * @param[in] _heap - existing heap
 * @return number of items in heap or 0 if _heap==NULL      
 */
size_t  HeapItemsNum(Heap* _heap);



/** 
 * @brief unit test - prints the heap
 * @param[in] _heap - the heap
 * @return NONE
 */
void HeapPrint(Heap* _heap);

/** 
 * @brief unit test - checks for the heap's integrity(basic rule)
 * @param[in] _heap - the heap
 * @return 0 - have error(s), non0 - OK.
 */
int IsHeapOK(Heap* _heap);


#endif/*__HEAP_H__*/
