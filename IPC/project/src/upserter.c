
/** 
 *  @file upserter.c
 *  @brief the upserter thread api
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

#include "upserter.h"
#include "dataStorageApi.h"
#include "commonStructs.h"




void* Upserter(void* _p)
{
	UpserterParams params ;
	DataStorageContext nextContext;
	struct 
	{
		long m_type;
		CDR nextCDR;
	} msgBuff;
	
	assert(NULL!=_p);
	
	memcpy(&params,_p,sizeof(UpserterParams));
	
	do
	{
		if(sizeof(CDR) > msgrcv(params.m_MsgQId, &msgBuff,
			sizeof(CDR),0,0))
		{
			fprintf(stderr,"Upserter 0x%lu has message fetching error.\n",pthread_self());
			return (void*)-1;
		}
		
		nextContext.m_storageManager = params.m_ssm;
		nextContext.m_data = &(msgBuff.nextCDR);
	
		if(0!=Aggregator_Upsert(params.m_sagg,(void*)(msgBuff.nextCDR.m_IMSI),&nextContext))
		{
			fprintf(stderr,"Upserter %lu has subscribers upsert error.\n",pthread_self());
			return (void*)-2;
		}
		
		nextContext.m_storageManager = params.m_osm;
		
		if(0!=Aggregator_Upsert(params.m_oagg,(void*)(msgBuff.nextCDR.m_MCCMNC),&nextContext))
		{
			fprintf(stderr,"Upserter %lu has operators upsert error.\n",pthread_self());
			return (void*)-3;
		}
	}while(1);
	
	return (void*)0;	
}











