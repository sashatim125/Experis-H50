
 
#ifndef __PERIODIC_EXECUTOR_H__
#define __PERIODIC_EXECUTOR_H__

/** 
 *  @file PeriodicExecutor.h
 *  @brief Definitions of the Periodic Tasks Executor
 *			in single process/thread eviroment
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */

#define _POSIX_C_SOURCE 199309L

#include "PeriodicExecutorShared.h"

#include <time.h>

/** 
 * @brief The periodic executor type. 
 */
typedef struct PeriodicExecutor PeriodicExecutor;

/** 
 * @brief Create a periodic executor that will measure time using given clock. 
 * 
 * @params[in] _name - name of the priodic executor
 * @params[in] _clockId - specify the id of the system clock to be used. CLOCK_REALTIME, 
 * 			CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC and similar provided it’s 
 * 			supported by the underlying system
 * @returns a pointer to the created priodic executor.
 * @retval NULL on failure due to allocation failure or wrong parameters
 */
PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clockid_t _clockId);


/** 
 * @brief Destroy the periodic executor previously created.Clean all allocated memory and resources. 
 *
 * @params[in] _executor previously created periodic executor
 */
void PeriodicExecutor_Destroy(PeriodicExecutor* _executor);

/** 
 * @brief Adding task to the executor. 
 *
 * @params[in] _executor previously created periodic executor
 * @params[in] _task - function to be called with the _context when the task is executed
 * @params[in] _context is given to the called function _task
 * @params[in]_period_ms - a period of function call in millisecond
 * @returns status
 * @retval 0 on success of !=0 otherwise (like allocation error)
 * @warning _period_ms should be greater then 0
 */
int PeriodicExecutor_Add(PeriodicExecutor* _executor, Task _task,
						void* _context, size_t _period_ms);

/** 
 * @brief Start running the executor
 *
 * @details Start running the tasks previously added to the executor or resume
 *		a previously paused Executor.
 * 		This function will return in one of two cases: 
 *		1. The tasks were executed to completion. 
 *		2. The executor was paused 
 * @params[in] _executor - previously created periodic executor

 * @returns the number of tasks remaining inside the executor(0 in case of error). 
 */
size_t PeriodicExecutor_Run(PeriodicExecutor* _executor);


/** 
 * @brief Pause running the executor
 *
 * @details Pause the execution of the executor. If a task is currently being executed then pause after 
 *		it has been completed current cycle. 
 * @params[in] _executor - previously created periodic executor

 * @returns the number of tasks remaining inside the executor. 
 */
size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor);


#endif /*__PERIODIC_EXECUTOR_H__*/


