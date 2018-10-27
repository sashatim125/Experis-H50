
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <string.h>

#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>

#include "commonStructs.h"
#include "aggregator.h"
#include "subscrStorageManager.h"
#include "operStorageManager.h"
#include "dataStorageApi.h"
#include "upserter.h"
#include "queryMaker.h"
#include "reportMaker.h"


#define SUBSCR_AGGREGATOR_CAPACITY 10
#define SUBSCR_AGGREGATOR_NUM_OF_LOCKS 8

#define OPER_AGGREGATOR_CAPACITY 10
#define OPER_AGGREGATOR_NUM_OF_LOCKS 8




static size_t SubscrHashFunc(const void* _IMSI)
{
	return (size_t)_IMSI;

}

static int IMSIEqFunc(const void* _IMSI_1, const void* _IMSI_2)
{
	return (IMSI_t)_IMSI_1 == (IMSI_t)_IMSI_2;
}


static size_t OperHashFunc(const void* _MCCMNC)
{
	return (size_t)_MCCMNC;

}

static int MCCMNCEqFunc(const void* _MCCMNC_1, const void* _MCCMNC_2)
{
	return (MCCMNC_t)_MCCMNC_1 == (MCCMNC_t)_MCCMNC_2;
}

static void PrintAggSubscriberData(AggSubscriberData* _asd)
{
	printf("\
IMSI = %lu\n\
Call durations :\n\
Outcall within	= %lu\n\
Incall within	= %lu\n\
Outcall outside	= %lu\n\
Incall outside	= %lu\n\
Number of SMS :\n\
Sent within     = %lu\n\
Received within = %lu\n\
Sent outside	= %lu\n\
Received outside= %lu\n\
Number of Mb :\n\
Downloaded      = %lu\n\
Uploaded        = %lu\n\n",
	_asd->m_IMSI,	
	_asd->m_outWithin,
	_asd->m_inWithin,
	_asd->m_outOutside,
	_asd->m_inOutside,
	_asd->m_sendWithin,
	_asd->m_recWithing,
	_asd->m_sendOutside,
	_asd->m_recOutside,
	_asd->m_down,
	_asd->m_up);
}


static void PrintAggOperatoData(AggOperatorData* _aod)
{
	printf("\
MCCMNC          = %lu\n\
Brand Name      = %s\n\
Call durations :\n\
Incall      	= %lu\n\
Outcall     	= %lu\n\
Number of SMS :\n\
Sent            = %lu\n\
Received        = %lu\n\n",
	_aod->m_MCCMNC,	
	_aod->m_operBrand,
	_aod->m_in,
	_aod->m_out,
	_aod->m_send,
	_aod->m_rec);
}






int main()/*int _argc , char* argv[])*/
{
	Aggregator *sagg , *oagg;
	SubscrStorageManager *ssm;
	OperStorageManager *osm;
	int i;
	CDR cdrs[6] = 
	{
	{1,111,999,"pelephone",45202,MOC   ,"01.01.2018","12:15:16",10,0,0,879,45202},
	{2,111,999,"cellcom"  ,45203,MOC   ,"01.01.2018","10:16:16",17,0,0,125,45202},
	{3,111,999,"parthner" ,45204,MOC   ,"01.01.2018","11:15:16",25,0,0,925,45203},
	{2,111,999,"pelephone",45202,SMS_MO,"01.01.2018","10:15:16",0 ,0,0,125,45202},
	{2,111,999,"pelephone",45202,SMS_MT,"01.01.2018","14:15:17",0 ,0,0,125,45202},
	{2,111,999,"pelephone",45202,SMS_MT,"01.01.2018","14:15:18",0 ,0,0,125,45202}
	};
	AggSubscriberData asd[3];
	AggOperatorData aod[3];
	DataStorageContext nextContext;
	
	
	int mqid;
	key_t key;
	/*
	struct 
	{
		long m_type;
		CDR nextCDR;
	} msgBuff;
	*/
	UpserterParams upParams;
	pthread_t threads[2];
	void *res;
	
	int mqid2;
	key_t key2;
	QueryMakerParams qParams;
	pthread_t queryThread;
	
	char snapshotFileName[MAX_FILENAME_LENGTH];
	ReportMakerParams rmp;
	pthread_t repThread;
	
	
	if(0 > (key = ftok("ParserUpserterKeyFile.key",1)))
	{
		perror("");
	}
	
	if(0 > (mqid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
	}
	
	if(NULL == (ssm = SubscrStorageManager_Create(2)))
	{
		return -1;
	}
	
	if(NULL == (osm = OperStorageManager_Create(2)))
	{
		return -1;
	}
	
	if(NULL == (sagg = Aggregator_Create(SUBSCR_AGGREGATOR_NUM_OF_LOCKS,
		SUBSCR_AGGREGATOR_CAPACITY,
		SubscrHashFunc, IMSIEqFunc,
		SubscrStorageManager_UpdateFunction,
		SubscrStorageManager_InsertFunction,
		SubscrStorageManager_ReadFunction)))
	{
		return -1;
	}
	
	if(NULL == (oagg = Aggregator_Create(OPER_AGGREGATOR_NUM_OF_LOCKS,
		OPER_AGGREGATOR_CAPACITY,
		OperHashFunc, MCCMNCEqFunc,
		OperStorageManager_UpdateFunction,
		OperStorageManager_InsertFunction,
		OperStorageManager_ReadFunction)))
	{
		return -1;
	}
	
	upParams.m_MsgQId = mqid;
	upParams.m_sagg = sagg;
	upParams.m_oagg = oagg;
	upParams.m_ssm = ssm;
	upParams.m_osm = osm;
	
	if(0!=pthread_create(threads+0,NULL,Upserter,&upParams))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}
	/*
	if(0!=pthread_create(threads+1,NULL,Upserter,&upParams))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}
	*/
	/*
	for(i=0 ; i<6; ++i)
	{
		msgBuff.m_type = 1;
		memcpy(&(msgBuff.nextCDR),cdrs + i,sizeof(CDR));
		
		if(0 != msgsnd(mqid,&msgBuff,sizeof(CDR),0))
		{
			perror("");
		}
		
		sleep(1);
		
	
		printf("Num of subscrs is %lu.\n",SubscrStorageManager_GetNumOfSubscribers(ssm));	
		printf("Num of opers is %lu.\n",OperStorageManager_GetNumOfOperators(osm));
	}
	*/
	/*
	pthread_join(threads[0],&res);
	*/
	sleep(3);

	/*

	for(i=0 ; i<3 ; ++i)
	{	
		nextContext.m_storageManager = ssm;
		nextContext.m_data = asd + i;
	
		assert(0==Aggregator_Read(sagg,(void*)(cdrs[i].m_IMSI),&nextContext));
		PrintAggSubscriberData(asd+i);
		
		nextContext.m_storageManager = osm;
		nextContext.m_data = aod + i;
		
		assert(0==Aggregator_Read(oagg,(void*)(cdrs[i].m_MCCMNC),&nextContext));
		PrintAggOperatoData(aod+i);
	}

	printf("Num of subscrs is %lu.\n",SubscrStorageManager_GetNumOfSubscribers(ssm));
	printf("Num of opers is %lu.\n",OperStorageManager_GetNumOfOperators(osm));
	*/
	
	
	SnapshotMaker(SUBSCRIBER,ssm,snapshotFileName);
	printf("Just created snapshot named %s.\n",snapshotFileName);
	
	
	rmp.m_reportType = SUBSCRIBER;
	strcpy(rmp.m_fileName,snapshotFileName);
	if(0!=pthread_create(&repThread,NULL,ReportMaker,&rmp))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}
	pthread_join(repThread,&res);
	
	
	
	SnapshotMaker(OPERATOR,osm,snapshotFileName);
	printf("Just created snapshot named %s.\n",snapshotFileName);
	
	
	rmp.m_reportType = OPERATOR;
	strcpy(rmp.m_fileName,snapshotFileName);
	if(0!=pthread_create(&repThread,NULL,ReportMaker,&rmp))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}
	pthread_join(repThread,&res);
	
	
	
	
	/*
	
	if(0 > (key2 = ftok("QueryUIKeyFile.key",1)))
	{
		perror("");
	}
	
	if(0 > (mqid2 = msgget(key2,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
	}
	
	
	qParams.m_MsgQId=mqid2;
	qParams.m_msgType=1;
	qParams.m_key=(void*)2;
	qParams.m_queryType=SUBSCRIBER;
	qParams.m_agg=sagg;
	qParams.m_sm=ssm;
	if(0!=pthread_create(&queryThread,NULL,QueryMaker,&qParams))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}
	pthread_join(queryThread,&res);
	
	
	qParams.m_MsgQId=mqid2;
	qParams.m_msgType=1;
	qParams.m_key=(void*)45202;
	qParams.m_queryType=OPERATOR;
	qParams.m_agg=oagg;
	qParams.m_sm=osm;
	if(0!=pthread_create(&queryThread,NULL,QueryMaker,&qParams))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}
	pthread_join(queryThread,&res);

	*/

	Aggregator_Destroy(oagg);
	Aggregator_Destroy(sagg);
	OperStorageManager_Destroy(osm);
	SubscrStorageManager_Destroy(ssm);


	return 0;
}




