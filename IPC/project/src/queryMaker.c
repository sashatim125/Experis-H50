

/** 
 *  @file queryMaker.c
 *  @brief the query maker thread api
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "queryMaker.h"
#include "dataStorageApi.h"


void* QueryMaker(void* _p)
{
	QueryMakerParams params ;
	DataStorageContext nextContext;
	struct 
	{
		long m_type;
		char m_buff[MAX_STRUCTURE_SIZE];
	} msgBuff;
	
	size_t msgSize;
	
	assert(NULL!=_p);
	
	memcpy(&params,_p,sizeof(QueryMakerParams));
	
	msgBuff.m_type = params.m_msgType;
	
	nextContext.m_data = &(msgBuff.m_buff);
	switch (params.m_queryType)
	{
		case SUBSCRIBER:
			msgSize = sizeof(AggSubscriberData);
			nextContext.m_storageManager = (SubscrStorageManager*)params.m_sm;
			if(0!=Aggregator_Read(params.m_agg,params.m_key,&nextContext))
			{
				fprintf(stderr,"QueryMaker %lu has subscribers read error.\n",pthread_self());
				return (void*)-1;
			}
			break;
		case OPERATOR:
			msgSize = sizeof(AggOperatorData);
			nextContext.m_storageManager = (OperStorageManager*)params.m_sm;
			if(0!=Aggregator_Read(params.m_agg,params.m_key,&nextContext))
			{
				fprintf(stderr,"QueryMaker %lu has operators read error.\n",pthread_self());
				return (void*)-2;
			}
			break;
	
	}

	if(0!= msgsnd(params.m_MsgQId,&msgBuff,msgSize,0))
	{
		fprintf(stderr,"QueryMaker 0x%lu has message sending error.\n",pthread_self());
		return (void*)-3;
	}
	
	return (void*)0;	
}
























