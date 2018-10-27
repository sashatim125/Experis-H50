
#ifndef __MSGQUEUE_H__
#define __MSGQUEUE_H__

/** 
 *  @file ShMemWCQueue.h
 *  @brief Waitable shared memory cyclic queue 
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h>

typedef struct ShMemWCQueue ShMemWCQueue;

/**  
 * @brief initiate the queue
 * @param[in] _shmem - adress of the shared memory start
 * @param[in] _shmemSize - size of the shared memory (in bytes)
 * @param[in] _qSize - size of the queue (in ITEMS)
 * @return pointer to the queue 
 */
ShMemWCQueue* ShMemWCQueue_Init(void* _shmem, size_t _shmemSize, size_t _qSize);

/**  
 * @brief connect to the queue over shared memory
 * @param[in] _shmem - adress of the shared memory start
 * @return pointer to the queue 
 */
ShMemWCQueue* ShMemWCQueue_Connect(void* _shmem);

/**  
 * @brief insert item to the queue
 * @param[in] _q - the queue
 * @param[in] _itemCont - content of the item 
 * @param[in] _itemSize - size of the item (in bytes)
 * @return 0 if OK  ,!=0 otherwise
 */
int ShMemWCQueue_Insert(ShMemWCQueue* _q, const void* _itemCont, size_t _itemSize);


/**  
 * @brief remove item from the queue
 * @param[in] _q - the queue
 * @param[in] _buff - buffer where to copy the item's content
 * @param[in] _buffSize - size of the buffer (in bytes) (at least as size of item)
 * @param[out] _itemSizePtr - the actual size of the item (in bytes)
 * @return 0 if OK  ,!=0 otherwise
 * @warning if _buffSize < actual size, the function fails!
 */
int ShMemWCQueue_Remove(ShMemWCQueue* _q, void* _buff, size_t _buffSize, size_t* _itemSizePtr);

/**  
 * @brief get the queue size (ITEMS !!!) 
 * @param[in] _q - the queue
 * @return the size of queue
 */
size_t ShMemWCQueue_GetSize(ShMemWCQueue* _q);





#endif /*__MSGQUEUE_H__*/





