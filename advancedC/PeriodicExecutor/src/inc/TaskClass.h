
 
#ifndef __TASK_CLASS_H__
#define __TASK_CLASS_H__

/** 
 *  @file TaskClass.h
 *  @brief Definitions of the Task type used by the Periodic Executor
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
#include <stddef.h>



/** 
 * @brief The task details holding class. 
 */
typedef struct TaskClass TaskClass;


typedef enum TaskClass_Result
{
	TASKCLASS_SUCCESS=0,
	TASKCLASS_UNINITIALIZED_ERROR,
	TASKCLASS_GENERAL_ERROR
} TaskClass_Result;


/** 
 * @brief Compare 2 tasks scheduled times
 * 
 * @params[in] _theTask1 
 * @params[in] _theTask2
 *
 * @returns comparison value ; !=0 if _theTask1 is LATER then time of _theTask2,0 - otherwise
 * @warning calling without previously called TaskClass_Schedule on BOTH tasks is forbidden
 */
int TasksComparator(void* _theTask1, void* _theTask2);


/** 
 * @brief Create a periodic executor that will measure time using given clock. 
 * 
 * @params[in] _task - function to be called with the _context when the task is executed
 * @params[in] _context is given to the called function _task
 * @params[in]_period_ms - a period of function call in millisecond
 *
 * @returns a pointer to the created task object.
 * @retval NULL on failure due to allocation failure
 * @warning _period_ms should be greater then 0
 */
TaskClass* TaskClass_Create(Task _task, void* _context, size_t _period_ms);


/** 
 * @brief Destroy the task previously created.Clean all allocated memory and resources. 
 *
 * @params[in] _theTask previously created task object
 */
void TaskClass_Destroy(TaskClass* _theTask);


/** 
 * @brief Whait untill the next scheduled time (set by TaskClass_Schedule) and run the task
 *
 * @params[in] _theTask previously created task object
 * @params[out] _taskResult value returned by the Task function
 * @params[in] _clockId - specify the id of the system clock to be used. CLOCK_REALTIME, 
 * 			CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC and similar provided it’s 
 * 			supported by the underlying system
 * @returns status
 * @retval TASKCLASS_SUCCESS
 * @retval TASKCLASS_UNINITIALIZED_ERROR
 * @retval TASKCLASS_GENERAL_ERROR
 *
 * @warning calling without previously called TaskClass_Schedule is forbidden
 */
TaskClass_Result TaskClass_WaitAndRun(const TaskClass* _theTask,int *_taskResult, clockid_t _clockId);


/** 
 * @brief Schedule the task to run the period of time from now
 *
 * @params[in] _theTask previously created task object
 * @params[in] _clockId - specify the id of the system clock to be used. CLOCK_REALTIME, 
 * 			CLOCK_REALTIME_COARSE, CLOCK_MONOTONIC and similar provided it’s 
 * 			supported by the underlying system
 * @returns status
 * @retval TASKCLASS_SUCCESS
 * @retval TASKCLASS_UNINITIALIZED_ERROR
 * @retval TASKCLASS_GENERAL_ERROR
 */
TaskClass_Result TaskClass_Schedule(TaskClass* _theTask, clockid_t _clockId);


#endif /*__TASK_CLASS_H__*/

