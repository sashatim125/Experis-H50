

/** 
 *  @file sysutils.c
 *  @brief System utility functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#define _GNU_SOURCE

#include "sysutils.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h> 
#include <sys/stat.h>
#include <fcntl.h>


#define OPER_SEM(semArrNum,semNum,oper) do{\
	semOps[(semArrNum)].sem_num = (semNum);\
	semOps[(semArrNum)].sem_op = (oper);\
	semOps[(semArrNum)].sem_flg = 0;\
}while(0)

typedef enum
{
	SEMAPHORE = 1,
	SHAREDMEM = 2
} SysObjNum;

typedef enum
{
	FREE_SEM = 0,
	OCC_SEM = 1,
	BINARY_SEM = 2
} SemType;

typedef enum
{
	UP = +1,
	DOWN = -1
} SemOper;

int GetSemaphore(void)
{
	int sid;
	key_t key;
	
	if(0 > (key = ftok(KEY_FILE,SEMAPHORE)))
	{
		perror("");
		return -1;
	}
	
	if(0 > (sid = semget(key,3,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
		return -2;
	}

	return sid;
}


int InitSemaphore(int _sem, size_t _queueSize)
{
	if(0 != semctl(_sem,FREE_SEM,SETVAL,_queueSize) ||
    		semctl(_sem,OCC_SEM,SETVAL,0) ||
    		semctl(_sem,BINARY_SEM,SETVAL,1) )
    {
    	perror("Sem init error");
    	return -1;
    }
    
    return 0;
}



int InsertRequest(int _sem)
{
	struct sembuf semOps[3];
	
/*	int n;
*/
	OPER_SEM(0,FREE_SEM,DOWN);
	OPER_SEM(1,OCC_SEM,UP);
	OPER_SEM(2,BINARY_SEM,DOWN);
	
	if(0!=semop(_sem,semOps,3))
	{
		perror("Insert request failed");
		return -1;
	}
/*	
	n=semctl(_sem,0,GETVAL);
	printf("Free sem is %d after insert request.\n",n);
	n=semctl(_sem,1,GETVAL);
	printf("Occupied sem is %d after insert request.\n",n);
*/
	return 0;
}

int UndoInsertRequest(int _sem)
{
	struct sembuf semOps[3];
/*	
	int n;
*/
	OPER_SEM(0,FREE_SEM,UP);
	OPER_SEM(1,OCC_SEM,DOWN);
	OPER_SEM(2,BINARY_SEM,UP);
	
	if(0!=semop(_sem,semOps,3))
	{
		perror("Undo Insert request failed");
		return -1;
	}
/*	
	n=semctl(_sem,0,GETVAL);
	printf("Free sem is %d after undo insert request.\n",n);
	n=semctl(_sem,1,GETVAL);
	printf("Occupied sem is %d after undo insert request.\n",n);
*/
	return 0;
	return 0;
}


int RemoveRequest(int _sem)
{
	struct sembuf semOps[3];
/*	
	int n;
*/
	OPER_SEM(0,FREE_SEM,UP);
	OPER_SEM(1,OCC_SEM,DOWN);
	OPER_SEM(2,BINARY_SEM,DOWN);
	
	if(0!=semop(_sem,semOps,3))
	{
		perror("Remove request failed");
		return -1;
	}
/*	
	n=semctl(_sem,0,GETVAL);
	printf("Free sem is %d after remove request.\n",n);
	n=semctl(_sem,1,GETVAL);
	printf("Occupied sem is %d after remove request.\n",n);
*/
	return 0;
}

int UndoRemoveRequest(int _sem)
{
	struct sembuf semOps[3];
/*	
	int n;
*/
	OPER_SEM(0,FREE_SEM,DOWN);
	OPER_SEM(1,OCC_SEM,UP);
	OPER_SEM(2,BINARY_SEM,UP);
	
	if(0!=semop(_sem,semOps,3))
	{
		perror("Undo Remove request failed");
		return -1;
	}
/*	
	n=semctl(_sem,0,GETVAL);
	printf("Free sem is %d after undo remove request.\n",n);
	n=semctl(_sem,1,GETVAL);
	printf("Occupied sem is %d after undo remove request.\n",n);
*/
	return 0;
}


int ReleaseSem(int _sem)
{
	struct sembuf semOps[1];
/*	
	int n;
*/
	OPER_SEM(0,BINARY_SEM,UP);
	
	if(0!=semop(_sem,semOps,1))
	{
		perror("Release request failed");
		return -1;
	}
/*	
	n=semctl(_sem,0,GETVAL);
	printf("Free sem is %d after release request.\n",n);
	n=semctl(_sem,1,GETVAL);
	printf("Occupied sem is %d after release request.\n",n);
*/
	return 0;
}


int InitSharedMem(void)
{
	int shmid;
	key_t key;
	
	if(0 > (key = ftok(KEY_FILE,SHAREDMEM)))
	{
		perror("");
		return -2;
	}
	
	if (-1 == (shmid = shmget(key,SHARED_MEM_SIZE,IPC_CREAT|0644)))
	{
		perror("InitSharedMem error");
	}
	
	return shmid;
}


void* AttachToSharedMem(int _shmem)
{
	void *shmemptr;

	if(NULL==(shmemptr = shmat(_shmem,NULL,0)))
	{
		perror("AttachToSharedMem error");
	}

	return shmemptr;
}

int DetachFromSharedMem(void* _shmemPtr)
{
	if(0 != shmdt(_shmemPtr))
	{
		perror("DetachFromSharedMem error");
		return -1;
	}
	
	return 0;
}






