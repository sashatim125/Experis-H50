

/** 
 *  @file msgc
 *  @brief Message utility functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#include "msg.h"

#include <stdio.h>
#include <string.h>
#include <stddef.h>


#define MSG_FORMAT "TYPE=%d;TEXT=%s"
#define GET_TYPE_FORMAT "TYPE=%d;"


struct msgbuff
{
	long m_type;       /* message type, must be > 0 */
	char m_text[1];    /* message data */
};

int msgCreate(void* _newMsg, size_t* _newMsgTxtSize, int _prodId, const char* _msgTxt)
{
	struct msgbuff* msbuf = (struct msgbuff*)_newMsg;

	if(NULL==_newMsg || NULL==_newMsgTxtSize || NULL==_msgTxt)
	{
		return -1;
	}
	
	msbuf->m_type = (long)_prodId;

	sprintf(msbuf->m_text,MSG_FORMAT,_prodId,_msgTxt);
	*_newMsgTxtSize = strlen(msbuf->m_text)+1;
	
	return 0;
}


int msgAckCreate(void* _ackMsg, size_t* _ackMsgTxtSize, int* _prodId, const char* _msgTxt)
{
	struct msgbuff* ackMsgmsbuf = (struct msgbuff*)_ackMsg;
	struct msgbuff* msgTxtmsbuf = (struct msgbuff*)_msgTxt;

	if(NULL==_ackMsg || NULL==_ackMsgTxtSize || NULL==_msgTxt)
	{
		return -1;
	}
	
	printf("Msg for ack txt is %s.\n",msgTxtmsbuf->m_text);
	
	if(1 > sscanf(msgTxtmsbuf->m_text,GET_TYPE_FORMAT,_prodId))
	{
		return -2;
	}
	
	ackMsgmsbuf->m_type = (long)(*_prodId);
	ackMsgmsbuf->m_text[0] = '\0';
	
	_ackMsgTxtSize = 0;
	
	return 0;
}












