
/** 
 *  @file prod.c
 *  @brief Message producer
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#define _GNU_SOURCE

#include "prod.h"
#include "msg.h"


#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <fcntl.h>
#include <stdio.h> 



#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/


struct Producer
{
	int m_magicNum;
	
	int m_msgQueue;
	
	int m_ackQueue;
	
	int m_sem;
	
	int m_id;

};



Producer* prodCreate(int _msgQueue, int _ackQueue, int _sem, int _id)
{
	Producer *prod;
	
	if(NULL == (prod = malloc(sizeof(Producer))))
	{
		return NULL;
	}
	
	prod->m_msgQueue = _msgQueue;
	
	prod->m_ackQueue = _ackQueue;
	
	prod->m_sem = _sem;
	
	prod->m_id = _id;
	
	prod->m_magicNum = MAGIC_NUMBER;
	
	return prod;
}



void prodDestroy(Producer* _prod)
{
	if(NULL==_prod || MAGIC_NUMBER != _prod->m_magicNum)
	{
		return;
	}
	
	_prod->m_magicNum = -1;

	free(_prod);
}




int prodStart(Producer* _prod)
{
	struct sembuf semOps[1];
	
	if(NULL==_prod)
	{
		return -1;
	}
	
	semOps[0].sem_num = 1;
	semOps[0].sem_op = +1;
	semOps[0].sem_flg = 0;
	
	if(0!=semop(_prod->m_sem,semOps,1))
	{
		perror("");
		return -4;
	}
	
	printf("Prod %d started.\n",_prod->m_id);

	return 0;
}
	



int prodFinish(Producer* _prod)
{
	struct sembuf semOps[2];
	int n;
	
	if(NULL==_prod)
	{
		return -1;
	}
	
	n=semctl(_prod->m_sem,0,GETVAL);
	printf("Sem is %d before up for finish.\n",n);
	n=semctl(_prod->m_sem,1,GETVAL);
	printf("Sem producers is %d before up for finish.\n",n);

	semOps[0].sem_num = 0;
	semOps[0].sem_op = +1;
	semOps[0].sem_flg = IPC_NOWAIT;
	
	semOps[0].sem_num = 1;
	semOps[0].sem_op = -1;
	semOps[0].sem_flg = IPC_NOWAIT;

	
	if(0!=semop(_prod->m_sem,semOps,2))
	{
		perror("Producer finish error");
		return -3;
	}
	printf("%d get sem up after finish.\n",_prod->m_id);
	
	n=semctl(_prod->m_sem,0,GETVAL);
	printf("Sem is %d after up for finish.\n",n);
	n=semctl(_prod->m_sem,1,GETVAL);
	printf("Sem producers is %d after up for finish.\n",n);
	
	printf("Prod %d finished.\n",_prod->m_id);

	return 0;
}




int prodSendMsg(Producer* _prod, const char *_msgTxt)
{

	char buffer[MESSAGE_BUFFER_SIZE];
	size_t msgTxtLen;
	struct sembuf semOps[1];
	int n;
	
	if(NULL==_prod || NULL==_msgTxt)
	{
		return -1;
	}
	
	printf("Message to send by %d text is %s.\n",_prod->m_id,_msgTxt);
	
	if(0 != msgCreate(buffer,&msgTxtLen,getpid(),_msgTxt))
	{
		return -2;
	}
	
	if(0 != msgsnd(_prod->m_msgQueue,buffer,msgTxtLen,0))
	{
		perror("");
		return -3;
	}
	
	printf("Message sended by %d text is %s.\n",_prod->m_id,_msgTxt);
	
	semOps[0].sem_num = 0;
	semOps[0].sem_op = +1;
	semOps[0].sem_flg = 0;
	
	if(0!=semop(_prod->m_sem,semOps,1))
	{
		perror("");
		return -4;
	}
	n=semctl(_prod->m_sem,0,GETVAL);
	printf("Sem is %d after up after msg send.\n",n);
	
	printf("%d get sem up after send.\n",_prod->m_id);

	return 0;
}



int receiveAck(Producer* _prod)
{
	char buffer[128];

	if(NULL==_prod)
	{
		return -1;
	}

	if(0 > msgrcv(_prod->m_ackQueue,buffer,1,(long)(_prod->m_id),MSG_NOERROR))
	{
		perror("Ack rcv error");
		return -2;
	}
	
	printf("Ack received by %d.\n",_prod->m_id);

	return 0;
}








