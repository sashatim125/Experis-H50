
/** 
 *  @file cons.c
 *  @brief Message consumer
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#define _GNU_SOURCE

#include "cons.h"
#include "msg.h"


#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <stdio.h> 
#include "errno.h"


#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/

#define UP_SEM \
{\
	int n;\
	semOps[0].sem_num = 0;\
	semOps[0].sem_op = +1;\
	semOps[0].sem_flg = 0;\
	\
	if(0!=semop(_cons->m_sem,semOps,1))\
	{\
		perror("Consumer sem_up fail");\
		errNum = -3;\
		break;\
	}\
	n=semctl(_cons->m_sem,0,GETVAL);\
	printf("Sem is %d before up.\n",n);\
}

#define DOWN_SEM \
{\
	int n;\
	n=semctl(_cons->m_sem,0,GETVAL);\
	printf("Sem is %d before down.\n",n);\
	semOps[0].sem_num = 0;\
	semOps[0].sem_op = -1;\
	semOps[0].sem_flg = 0;\
	\
	if(0!=semop(_cons->m_sem,semOps,1))\
	{\
		perror("Consumer sem_down fail");\
		errNum = -2;\
		break;\
	}\
}

#define CHECK_FOR_PRODUCERS \
{\
int n;\
	printf("%d check for producers.\n",_cons->m_id);\
	\
	 n=semctl(_cons->m_sem,1,GETVAL);\
	printf("There are %d producers.\n",n);\
	if(1 ==n)\
	{\
		printf("%d knows there are NO producers and get sem up.\n",_cons->m_id);\
		UP_SEM;\
		break;\
	}\
}

struct Consumer
{
	int m_magicNum;
	
	int m_msgQueue;
	
	int m_ackQueue;
	
	int m_sem;
	
	int m_id;

};



Consumer * consCreate(int _msgQueue, int _ackQueue, int _sem, int _id)
{
	Consumer *cons;
	
	if(NULL == (cons = malloc(sizeof(Consumer))))
	{
		return NULL;
	}
	
	cons->m_msgQueue = _msgQueue;
	
	cons->m_ackQueue = _ackQueue;
	
	cons->m_sem = _sem;
	
	cons->m_id = _id;
	
	cons->m_magicNum = MAGIC_NUMBER;
	
	return cons;
}



void consDestroy(Consumer* _cons)
{
	if(NULL==_cons || MAGIC_NUMBER != _cons->m_magicNum)
	{
		return;
	}
	
	_cons->m_magicNum = -1;

	free(_cons);
}





int recieveAndAck(Consumer* _cons)
{
	char buffer[MESSAGE_BUFFER_SIZE];
	char ackBuff[MESSAGE_BUFFER_SIZE];
	size_t ackMsgTxtSize;
	int prodId;
	struct sembuf semOps[2];
	
	int errNum=0;
	
	if(NULL==_cons)
	{
		return -1;
	}
	
	printf("Cons %d started.\n",_cons->m_id);
	
	while(1)
	{
		DOWN_SEM;
		
		CHECK_FOR_PRODUCERS;
		
		printf("%d knows there are producers .\n",_cons->m_id);
		
		printf("%d receiving message.\n",_cons->m_id);
		
		if(0 >= msgrcv(_cons->m_msgQueue,buffer,MESSAGE_BUFFER_SIZE,0,MSG_NOERROR|IPC_NOWAIT))
		{
			if(EAGAIN == errno)
			{
				printf("%d checked and there are no msgs.\n",_cons->m_id);
				continue;
			}else
			{
				perror("Consumer msgrcv error");
				errNum = -4;
				break;
			}
		}
		
		printf("Message received :%s\n",buffer+sizeof(long));
	
		if(0 != msgAckCreate(ackBuff, &ackMsgTxtSize, &prodId, buffer))
		{
			perror("Consumer msgAckCreate error");
			errNum = -5;
			break;
		}
	
		if(0 != msgsnd(_cons->m_ackQueue,ackBuff,ackMsgTxtSize,0))
		{
			perror("Consumer msgsnd error");
			errNum = -6;
			break;
		}
		
		printf("%d sended ack.\n",_cons->m_id);
	}
	
	printf("Cons %d finished.\n",_cons->m_id);
	
	return errNum;
}




















