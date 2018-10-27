
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


#include "cons.h"

#include <stdlib.h>
#include <stdio.h> 

#define STOP_MSG NULL


#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/



struct Consumer
{
	int m_magicNum;
	
	WaitQueue* m_msgQueue;
	
	WaitQueue* m_ackQueue;
	
	int m_id;

};



Consumer* Consumer_Create(WaitQueue* _msgQueue, WaitQueue* _ackQueue, int _id)
{
	Consumer *cons;
	
	if(NULL==_msgQueue || NULL==_ackQueue)
	{
		return NULL;
	}
	
	if(NULL == (cons = malloc(sizeof(Consumer))))
	{
		return NULL;
	}
	
	cons->m_msgQueue = _msgQueue;
	
	cons->m_ackQueue = _ackQueue;
	
	cons->m_id = _id;
	
	cons->m_magicNum = MAGIC_NUMBER;
	
	return cons;
}



void Consumer_Destroy(Consumer* _cons)
{
	if(NULL==_cons || MAGIC_NUMBER != _cons->m_magicNum)
	{
		return;
	}
	
	_cons->m_magicNum = -1;

	free(_cons);
}



int Consumer_RecieveAndAck(Consumer* _cons)
{
	void *msg;
	
	if(NULL==_cons)
	{
		return -1;
	}
	
	if(0!=WaitQueue_Remove(_cons->m_msgQueue,&msg))
	{
		fprintf(stderr,"Consumer %d had Consumer_RecieveAndAck(rec) error.\n",_cons->m_id);
		return -2;
	}
	printf("The message was received by %d.\n",_cons->m_id);
	
	if(STOP_MSG == msg)
	{
		if(0!=WaitQueue_Insert(_cons->m_msgQueue,STOP_MSG))
		{
			return -3;
		}
		
		printf("The consumer %d was stopped.\n",_cons->m_id);
		
		return CONS_STOPED;
	}
	
	if(0!=WaitQueue_Insert(_cons->m_ackQueue,msg))
	{
		fprintf(stderr,"Consumer %d had Consumer_RecieveAndAck(ack send) error.\n",_cons->m_id);
		return -4;
	}
	printf("The ack was sent by %d.\n",_cons->m_id);
	
	return 0;
}


int Consumer_StopThemAll(Consumer* _cons)
{	
	if(NULL==_cons)
	{
		return -1;
	}
	
	if(0!=WaitQueue_Insert(_cons->m_msgQueue,STOP_MSG))
	{
		return -2;
	}
	
	return 0;
}

















