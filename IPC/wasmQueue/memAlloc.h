
 
#ifndef __MEM_ALLOC_H__
#define __MEM_ALLOC_H__

/** 
 *  @file memAlloc.h
 *  @brief Definitions of simple memory management unit
 * (allocation and releasing)
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */
#include <stddef.h>

/*Memory block (header OR information)*/
typedef unsigned int Block;

/*single byte type*/
typedef char Byte;

/** 
 * @brief Initiate the memory buffer for management
 * 
 * @params[in] _buff - empty buffer
 * @params[in] _size - the buffer's size in bytes
 *			(should be at least MIN_BUFF_SIZE) 
 * @returns a pointer to the new buffer 
 * @retval NULL on failure 
 */
void* initMem(void* _buff, size_t _size);


/** 
 * @brief allocate chunk of memory
 * 
 * @params[in] _buffer - adress of the previously initiated buffer
 * @params[in] _size - requested size
 * @returns a pointer to the newly allocated space 
 * @retval NULL on failure 
 */
void* allocMem(void* _buffer, size_t _size);


/** 
 * @brief release the memory previously allocated with allocMem
 * 
 * @params[in] _blockPtr - pointer to the block
 * @returns ...
 */
void releaseMem(void *_blockPtr);

#endif /*__MEM_ALLOC_H__*/


