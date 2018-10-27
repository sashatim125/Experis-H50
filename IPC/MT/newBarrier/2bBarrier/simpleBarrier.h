
#ifndef __SIMPLE_BARRIER_H__
#define __SIMPLE_BARRIER_H__

/** 
 *  @file simpleBarrier.h
 *  @brief Barrier API (fair)
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h>

typedef struct SimpleBarrier SimpleBarrier;

/**  
 * @brief create simple fair barrier
 * @param[in] _capacity - the barriers capacity
 * @return pointer to the newly created barrier
 * @warning _capacity should be >1
 */
SimpleBarrier* SimpleBarrier_Create(size_t _capacity);

/**  
 * @brief destroy the barrier
 * @param[in] _b - the barrier 
 * @warning DO NOT CALL if there are thereads doing SimpleBarrier_Wait
 */
void SimpleBarrier_Destroy(SimpleBarrier* _b);

/**  
 * @brief create the barrier
 * @details the thread wait until the barrier is full
 * and then it is realeased
 * @param[in] _b - the barrier
 * @warning DO NOT CALL SimpleBarrier_Destroy if there are thereads doing Barrier_Wait
 */
int SimpleBarrier_Wait(SimpleBarrier* _b);



#endif /*__SIMPLE_BARRIER_H__*/



