


/** 
 *  @file queue.c
 *  @brief Message queues
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#define _GNU_SOURCE

#include "queue.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <stdio.h> 
#include <sys/stat.h>
#include <fcntl.h>

typedef enum
{
	MSG_QUEUE = 1,
	ACK_QUEUE= 2,
	SEMAPHORE = 3
} SysObjNum;


static int getQueue(SysObjNum _queueType)
{
	int mid;
	key_t key;
	
	if(0 > (key = ftok(KEY_FILE,_queueType)))
	{
		perror("");
		return -1;
	}
	
	if(0 > (mid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
		return -2;
	}

	return mid;
}

int getMsgQueue(void)
{
	return getQueue(MSG_QUEUE);
}


int getAckQueue(void)
{
	return getQueue(ACK_QUEUE);
}



int getSemaphore(void)
{
	int sid;
	key_t key;
	
	if(0 > (key = ftok(KEY_FILE,SEMAPHORE)))
	{
		perror("");
		return -1;
	}
	
	if(0 > (sid = semget(key,2,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
		return -2;
	}

	return sid;
}



















