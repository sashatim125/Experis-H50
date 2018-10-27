
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


#include "prod.h"

#include <stdlib.h>
#include <stdio.h> 



#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/


struct Producer
{
	int m_magicNum;
	
	WaitQueue* m_msgQueue;
	
	WaitQueue* m_ackQueue;
	
	int m_id;

};



Producer* Producer_Create(WaitQueue* _msgQueue, WaitQueue* _ackQueue, int _id)
{
	Producer *prod;
	
	if(NULL==_msgQueue || NULL==_ackQueue)
	{
		return NULL;
	}
	
	if(NULL == (prod = malloc(sizeof(Producer))))
	{
		return NULL;
	}
	
	prod->m_msgQueue = _msgQueue;
	
	prod->m_ackQueue = _ackQueue;
	
	prod->m_id = _id;
	
	prod->m_magicNum = MAGIC_NUMBER;
	
	return prod;
}



void Producer_Destroy(Producer* _prod)
{
	if(NULL==_prod || MAGIC_NUMBER != _prod->m_magicNum)
	{
		return;
	}
	
	_prod->m_magicNum = -1;

	free(_prod);
}


int Producer_SendMsg(Producer* _prod, void *_msg)
{

	if(NULL==_prod)
	{
		return -1;
	}
	
	if(0!=WaitQueue_Insert(_prod->m_msgQueue,_msg))
	{
		fprintf(stderr,"Producer %d had Producer_SendMsg error.\n",_prod->m_id);
		return -2;
	}
	
	printf("The message was sent by %d.\n",_prod->m_id);
	
	return 0;
}



int Producer_ReceiveAck(Producer* _prod)
{
	void *msg;

	if(NULL==_prod)
	{
		return -1;
	}
	
	if(0!=WaitQueue_Remove(_prod->m_ackQueue,&msg))
	{
		fprintf(stderr,"Producer %d had Producer_ReceiveAck error.\n",_prod->m_id);
		return -2;
	}
	
	printf("Ack was received by %d.\n",_prod->m_id);

	return 0;
}








