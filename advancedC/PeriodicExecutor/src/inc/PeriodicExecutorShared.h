
#ifndef __PERIODIC_EXECUTOR_SHARED_H__
#define __PERIODIC_EXECUTOR_SHARED_H__



/** 
 *  @file PeriodicExecutorShared.h
 *  @brief Shared definitions of the Periodic Tasks Executor
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */


/** 
 * @brief User defined function that is executed by the periodic executor. 
 * 
 * @params[in] _context - to work on
 * @returns a demand to be executed next time.
 * @retval 	0 : The function should be called again after the interval has passed. 
 *			any other value : The function should be removed from the executor. 
 */
typedef int(*Task)(void *_context) ;




#endif /*__PERIODIC_EXECUTOR_SHARED_H__*/

