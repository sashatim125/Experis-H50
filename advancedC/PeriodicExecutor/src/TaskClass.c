

/** 
 *  @file TaskClass.c
 *  @brief Implementation of the Task type used bu the Periodic Executoy
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */

#include "PeriodicExecutorShared.h"
#include "TaskClass.h"
#include "TimeUtils.h"

#include "zlog4c.h"

#include <stdlib.h>
#include <unistd.h>


#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcd
#endif /*MAGIC_NUMBER*/


struct TaskClass
{
	int m_magicNum;
	
	Task	m_task;
	void*	m_context;
	size_t	m_period_ms;
	Timespec m_nextRunTime;
};


int TasksComparator(void* _theTask1, void* _theTask2)
{
	return IsLater(((TaskClass*)_theTask1)->m_nextRunTime,((TaskClass*)_theTask2)->m_nextRunTime);
}


TaskClass* TaskClass_Create(Task _task, void* _context, size_t _period_ms)
{
	TaskClass *newTask;

	if(NULL==_task || 1 > _period_ms)
	{
		return NULL;
	}

	if(NULL==(newTask = malloc(sizeof(TaskClass))))
	{
		return NULL;
	}
	
	newTask->m_task			= _task;
	newTask->m_context		= _context;
	newTask->m_period_ms	= _period_ms;
	
	newTask->m_magicNum 	= MAGIC_NUMBER;
	
	ZLOG("TaskClass",LOG_INFO,"new task CREATED");
	
	return newTask;
}


void TaskClass_Destroy(TaskClass* _theTask)
{
	if(NULL==_theTask || MAGIC_NUMBER != _theTask->m_magicNum)
	{
		return;
	}
	
	_theTask->m_magicNum = -1;
	
	free(_theTask);
	ZLOG("TaskClass",LOG_INFO,"a task DESTROYED");
}


TaskClass_Result TaskClass_WaitAndRun(const TaskClass* _theTask,int *_taskResult, clockid_t _clockId)
{
	Timespec now, diffTime;

	if(NULL==_theTask || NULL==_taskResult)
	{
		return TASKCLASS_UNINITIALIZED_ERROR;
	}
	
	if(0 != clock_gettime(_clockId, &now))
	{
		return TASKCLASS_GENERAL_ERROR;
	}
	
	diffTime = TimeDiff(now,_theTask->m_nextRunTime);
	if(!(0 > diffTime.tv_sec || 0 > diffTime.tv_nsec))
	{	
		ZLOG("TaskClass",LOG_INFO,"entering to sleep");
		
		if (0 != nanosleep(&diffTime,NULL))
		{
			return TASKCLASS_GENERAL_ERROR;
		}
		
		ZLOG("TaskClass",LOG_INFO,"returned from sleep");
	}
	
	*_taskResult = _theTask->m_task(_theTask->m_context);
	
	
	ZLOG("TaskClass",LOG_INFO,"runned the user function %d",*(int*)(_theTask->m_context));
	
	return TASKCLASS_SUCCESS;
}


TaskClass_Result TaskClass_Schedule(TaskClass* _theTask, clockid_t _clockId)
{
	Timespec now;

	if(NULL==_theTask)
	{
		return TASKCLASS_UNINITIALIZED_ERROR;
	}
	
	if(0 != clock_gettime(_clockId, &now))
	{
		return TASKCLASS_GENERAL_ERROR;
	}
	
	_theTask->m_nextRunTime = TimeAfterDelay(now,_theTask->m_period_ms);
	
	ZLOG("TaskClass",LOG_INFO,"a task is scheduled %d",*(int*)(_theTask->m_context));
	
	return TASKCLASS_SUCCESS;
}













