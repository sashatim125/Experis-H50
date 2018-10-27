
 

/** 
 *  @file PeriodicExecutor.c
 *  @brief Implementations of the Periodic Tasks Executor
 *			in single process/thread eviroment
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */

#include "PeriodicExecutorShared.h"
#include "PeriodicExecutor.h"
#include "TaskClass.h"
#include "heap.h"
#include "vector.h"
#include "list.h"

#include "zlog4c.h"

#include <sys/time.h>
#include <stdlib.h>
#include <string.h>


#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcd
#endif /*MAGIC_NUMBER*/

#ifndef TRUE
#define TRUE 1
#endif /*TRUE*/

#ifndef FALSE 
#define FALSE 0
#endif /*FALSE*/

#define NAME_SIZE 128
#define INITIAL_TASKS_NUMBER 100

struct PeriodicExecutor
{
	int m_magicNum;
	
	char m_name[NAME_SIZE];
	clockid_t m_clock;
	
	Heap*   m_tasksQueue;
	Vector* m_tasks;
	List*   m_unaddedTasks;
	
	int m_stopNow;
};


PeriodicExecutor* PeriodicExecutor_Create(const char* _name, clockid_t _clockId)
{
	struct timespec now;
	PeriodicExecutor *newPE;

	if(NULL==_name || 0 != clock_gettime(_clockId,&now))
	{
		return NULL;
	}
	
	if(NULL==(newPE = malloc(sizeof(PeriodicExecutor))))
	{
		return NULL;
	}

	strcpy(newPE->m_name,_name);
	newPE->m_clock = _clockId;
	
	if(NULL==(newPE->m_tasks = Vector_Create(INITIAL_TASKS_NUMBER,INITIAL_TASKS_NUMBER/2)))
	{
		free(newPE);
		return NULL;
	}
	
	newPE->m_tasksQueue = NULL;
	
	if(NULL==(newPE->m_unaddedTasks = List_Create()))
	{
		free(newPE);
		Vector_Destroy(&(newPE->m_tasks),NULL);
		return NULL;
	}
	
	newPE->m_stopNow = FALSE;
	
	newPE->m_magicNum = MAGIC_NUMBER;
	
	ZLOG("PeriodicExecutor",LOG_INFO,"PeriodicExecutor CREATED");

	return newPE;
}

static void TaskDestroyFunc(void *_theTask)
{
	TaskClass_Destroy((TaskClass*)_theTask);
}


void PeriodicExecutor_Destroy(PeriodicExecutor* _executor)
{
	if(NULL==_executor || MAGIC_NUMBER != _executor->m_magicNum)
	{
		return;
	}
	
	_executor->m_magicNum = -1;
	
	if(NULL != _executor->m_tasksQueue)
	{
		HeapDestroy(_executor->m_tasksQueue);
	}
	
	Vector_Destroy(&(_executor->m_tasks), TaskDestroyFunc);
	List_Destroy(&(_executor->m_unaddedTasks),NULL);
	
	free(_executor);
	
	ZLOG("PeriodicExecutor",LOG_INFO,"PeriodicExecutor DESTROYED");
}


int PeriodicExecutor_Add(PeriodicExecutor* _executor, Task _task,
						void* _context, size_t _period_ms)
{
	TaskClass *newTask;

	if(NULL==_executor || NULL==_task || 1 > _period_ms)
	{
		return -1;
	}
	
	if(NULL==(newTask = TaskClass_Create(_task,_context,_period_ms)))
	{
		return -2;
	}
	
	if(NULL == _executor->m_tasksQueue)
	{
		if(VECTOR_SUCCESS != Vector_Append(_executor->m_tasks,newTask))
		{
			free(newTask);
			return -3;
		}
	}else
	{
		if(LIST_SUCCESS != List_PushHead(_executor->m_unaddedTasks,newTask))
		{
			free(newTask);
			return -4;
		}
	}
	
	ZLOG("PeriodicExecutor",LOG_INFO,"New task added");
	
	return 0;
}



static int ScheduleTheTask(void* _theTask, size_t _index, void* _clockIdPtr)
{
	ZLOG("PeriodicExecutor",LOG_INFO,"a task is going to be scheduled");

	return TASKCLASS_SUCCESS == TaskClass_Schedule((TaskClass*)_theTask,*(clockid_t*)_clockIdPtr);
}


static int RunNextTask(Heap *_tasksQueue, clockid_t _clockId)
{
	TaskClass *nextTask;
	int taskRunDemand;
	
	if(HEAP_SUCCESS != HeapExtractMax(_tasksQueue,(void**)&(nextTask)))
	{
		return -1;
	}
	
	ZLOG("PeriodicExecutor",LOG_INFO,"got a task to run");
	
	if(TASKCLASS_SUCCESS != TaskClass_WaitAndRun(nextTask,&taskRunDemand,_clockId))
	{
		return -2;
	}
	
	ZLOG("PeriodicExecutor",LOG_INFO,"runned a task");
	ZLOG("PeriodicExecutor",LOG_INFO,"tests in queue %lu",HeapItemsNum(_tasksQueue));
	
	if(0 == taskRunDemand)
	{
		if(TASKCLASS_SUCCESS != TaskClass_Schedule(nextTask,_clockId))
		{
			return -3;
		}
		if(HEAP_SUCCESS != HeapInsert(_tasksQueue,nextTask))
		{
			return -4;
		}
		
		ZLOG("PeriodicExecutor",LOG_INFO,"a task scheduled and reinserted");
	}else
	{
		TaskClass_Destroy(nextTask);
	}
	
	ZLOG("PeriodicExecutor",LOG_INFO,"tests in queue %lu",HeapItemsNum(_tasksQueue));
	
	return 0;
}



size_t PeriodicExecutor_Run(PeriodicExecutor* _executor)
{
	void* nextTask;
	
	if(NULL==_executor)
	{
		return 0;
	}
	ZLOG("PeriodicExecutor",LOG_INFO,"the runner started");
	if(NULL==_executor->m_tasksQueue)
	{
		Vector_Size(_executor->m_tasks);
	
		Vector_ForEach(_executor->m_tasks,ScheduleTheTask,&(_executor->m_clock));
		
		if(NULL==(_executor->m_tasksQueue = HeapBuild(_executor->m_tasks,TasksComparator)))
		{
			return 0;
		}
		ZLOG("PeriodicExecutor",LOG_INFO,"heap(queue) was buid");
	}
	
	while(!_executor->m_stopNow && 0 < HeapItemsNum(_executor->m_tasksQueue))
	{
		while(LIST_SUCCESS == List_PopHead(_executor->m_unaddedTasks,&nextTask))
		{
			if(TASKCLASS_SUCCESS != TaskClass_Schedule(nextTask,_executor->m_clock))
			{
				return 0;
			}
			if(HEAP_SUCCESS != HeapInsert(_executor->m_tasksQueue,nextTask))
			{
				return 0;
			}
			ZLOG("PeriodicExecutor",LOG_INFO,"new task added after pause");
		}
		
		if(0 != RunNextTask(_executor->m_tasksQueue,_executor->m_clock))
		{
			_executor->m_stopNow = TRUE;
		}
		
	}
	_executor->m_stopNow = FALSE;
	
	ZLOG("PeriodicExecutor",LOG_INFO,"the runner finished(paused)");
	
	return HeapItemsNum(_executor->m_tasksQueue);
}


size_t PeriodicExecutor_Pause(PeriodicExecutor* _executor)
{

	if(NULL==_executor)
	{
		return 0;
	}
	
	_executor->m_stopNow = TRUE;
	
	return HeapItemsNum(_executor->m_tasksQueue);
}





