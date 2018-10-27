
#ifndef __BARRIER_H__
#define __BARRIER_H__

/** 
 *  @file barrier.h
 *  @brief Barrier API (fair and with ability to execute callback function
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h>

typedef struct Barrier Barrier;

/**  
 * @brief create the barrier
 * @param[in] _capacity - the barriers capacity
 * @return pointer to the newly created barrier
 * @warning _capacity should be >1
 */
Barrier* Barrier_Create(size_t _capacity);


/**  
 * @brief destroy the barrier
 * @param[in] _b - the barrier 
 * @warning DO NOT CALL if there are thereads doing Barrier_Wait
 */
void Barrier_Destroy(Barrier* _b);


/**  
 * @brief create the barrier
 * @details the thread wait until the barrier is full
 * number of waiting threads are equal to capacity),
 * then all the threads are executing there function _callBack
 * with _context ,and only then it is realeased
 * @param[in] _b - the barrier
 * @param[in] _callBack - call back function of the waiting thread
 * @param[in] _context - parameter for the call back function of the waiting thread
 * @warning DO NOT CALL Barrier_Destroy if there are thereads doing Barrier_Wait
 */
int Barrier_Wait(Barrier* _b, void(*_callBack)(void*), void* _context);



#endif /*__BARRIER_H__*/
