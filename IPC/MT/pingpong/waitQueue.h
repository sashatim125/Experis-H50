
#ifndef __WAIT_QUEUE_H__
#define __WAIT_QUEUE_H__

/** 
 *  @file waitQueue.h
 *  @brief Waitable generic cyclic queue 
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h>

typedef struct WaitQueue WaitQueue;

/**  
 * @brief creat the queue
 * @param[in] _qSize - size of the queue (in ITEMS)
 * @return pointer to the queue 
 */
WaitQueue* WaitQueue_Create(size_t _qSize);

/**  
 * @brief destroy the queue
 * @param[in] _q - the queue
 * @return pointer to the queue 
 * @warning make sure there are no waiting threads
 * @warning if any items left, they left untouched
 */
void WaitQueue_Destroy(WaitQueue* _q)
;
/**  
 * @brief insert item to the queue
 * @param[in] _q - the queue
 * @param[in] _item - the item to be inserted
 * @return 0 if OK  , !=0 otherwise
 */
int WaitQueue_Insert(WaitQueue* _q, void* _item);

/**  
 * @brief remove item from the queue
 * @param[in] _q - the queue
 * @param[out] _itemPtr - where to put the item
 * @return 0 if OK  ,!=0 otherwise
 */
int WaitQueue_Remove(WaitQueue* _q, void** _itemPtr);

/**  
 * @brief get the queue size (ITEMS !!!) 
 * @param[in] _q - the queue
 * @return the size of queue
 */
size_t WaitQueue_GetSize(WaitQueue* _q);





#endif /*__WAIT_QUEUE_H__*/





