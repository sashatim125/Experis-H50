
/** 
 *  @file dataManagerMain.c
 *  @brief the main data managing API (temporary including UI)
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
#include "formatedPrint.h"


#define SUBSCR_AGGREGATOR_CAPACITY 100
#define SUBSCR_AGGREGATOR_NUM_OF_LOCKS 10

#define OPER_AGGREGATOR_CAPACITY 10
#define OPER_AGGREGATOR_NUM_OF_LOCKS 5

static void UI();

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

Aggregator *sagg , *oagg;
SubscrStorageManager *ssm;
OperStorageManager *osm;

int main()
{
	UpserterParams upParams;
	pthread_t upThreads[2];
	int mqid;
	key_t key;
	
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
	
	if(0 > (key = ftok("ParserUpserterKeyFile.key",1)))
	{
		perror("");
		return -1;
	}
	if(0 > (mqid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
		return -1;
	}
	
	upParams.m_MsgQId = mqid;
	upParams.m_sagg = sagg;
	upParams.m_oagg = oagg;
	upParams.m_ssm = ssm;
	upParams.m_osm = osm;
	
	if(0!=pthread_create(upThreads+0,NULL,Upserter,&upParams))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}
	if(0!=pthread_create(upThreads+1,NULL,Upserter,&upParams))
	{
		fprintf(stderr,"pthread_create error\n");
		return -1;
	}

	UI();
	
	pthread_cancel(upThreads[0]);
	pthread_cancel(upThreads[1]);
	pthread_join(upThreads[0],NULL);
	pthread_join(upThreads[1],NULL);

	Aggregator_Destroy(oagg);
	Aggregator_Destroy(sagg);
	OperStorageManager_Destroy(osm);
	SubscrStorageManager_Destroy(ssm);

	return 0;
}


static void UI()
{
	int choise, cont;
	IMSI_t subscrID;
	MCCMNC_t operID;
	
	int mqid;
	key_t key;
	QueryMakerParams qParams;
	pthread_t queryThread;
	void* res;
	
	SnapshotMakerParams ssmParams;
	pthread_t ssmThread;
	
	struct 
	{
		long m_type;
		char m_buff[MAX_STRUCTURE_SIZE];
	} msgBuff;
	
	
	cont=1;
	
	if(0 > (key = ftok("QueryUIKeyFile.key",1)))
	{
		perror("");
		return;
	}
	if(0 > (mqid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
		return;
	}

	printf("==========Welcome to the Cellular networks billing system!==========\n");
	
	while(cont)
	{
		printf("\nThis is a TEST version of the system.\n");
		printf("Please choose one of the following options :\n");
		printf("1: Make a subscriber query ;\n");
		printf("2: Make an operator query ;\n");
		printf("3: Make a subscibers report ;\n");	
		printf("4: Make an operators report ;\n");
		printf("5: Shutdown the system.\n");			
		
		scanf("%d",&choise);
		switch (choise)
		{
			case 1:
				printf("Please enter the subscriber's IMSI :");
				scanf("%lu",&subscrID);
					
				qParams.m_MsgQId=mqid;
				qParams.m_msgType=1;
				qParams.m_key=(void*)subscrID;
				qParams.m_queryType=SUBSCRIBER;
				qParams.m_agg=sagg;
				qParams.m_sm=ssm;
				if(0!=pthread_create(&queryThread,NULL,QueryMaker,&qParams))
				{
					fprintf(stderr,"querry pthread_create error\n");
					break;
				}
				pthread_join(queryThread,&res);
				if((void*)0!=res)
				{
					fprintf(stderr,"wrong query\n");
					break;
				}
				msgrcv(mqid,&msgBuff,MAX_STRUCTURE_SIZE,0,0);
				PrintAggregatedDataReadable(stdout,SUBSCRIBER,msgBuff.m_buff);
				break;
				
			case 2:
				printf("Please enter the operator's MCCMNC :");
				scanf("%lu",&operID);
	
				qParams.m_MsgQId=mqid;
				qParams.m_msgType=1;
				qParams.m_key=(void*)operID;
				qParams.m_queryType=OPERATOR;
				qParams.m_agg=oagg;
				qParams.m_sm=osm;
				if(0!=pthread_create(&queryThread,NULL,QueryMaker,&qParams))
				{
					fprintf(stderr,"querry pthread_create error\n");
					break;
				}
				pthread_join(queryThread,&res);
				if((void*)0!=res)
				{
					fprintf(stderr,"wrong query\n");
					break;
				}
				msgrcv(mqid,&msgBuff,MAX_STRUCTURE_SIZE,0,0);
				PrintAggregatedDataReadable(stdout,OPERATOR,msgBuff.m_buff);
				break;
				
			case 3:
				ssmParams.m_adt = SUBSCRIBER;
				ssmParams.m_sm = ssm;
				if(0!=pthread_create(&ssmThread,NULL,SnapshotMaker,&ssmParams))
				{
					fprintf(stderr,"snapshot pthread_create error\n");
					break;
				}
				pthread_join(ssmThread,&res);
				printf("Just created snapshot named %s.\n",ssmParams.m_filename);
		
				if(0!= ReportMaker(SUBSCRIBER,ssmParams.m_filename))
				{
					fprintf(stderr,"UI: ReportMaker has error.\n");
					break;
				}else
				{
					printf("Report %s has been successfully made.\n",ssmParams.m_filename);
				}
				break;
			
			case 4:
				ssmParams.m_adt = OPERATOR;
				ssmParams.m_sm = osm;
				if(0!=pthread_create(&ssmThread,NULL,SnapshotMaker,&ssmParams))
				{
					fprintf(stderr,"snapshot pthread_create error\n");
					break;
				}
				pthread_join(ssmThread,&res);
				printf("Just created snapshot named %s.\n",ssmParams.m_filename);
		
				if(0!= ReportMaker(OPERATOR,ssmParams.m_filename))
				{
					fprintf(stderr,"UI: ReportMaker has error.\n");
					break;
				}else
				{
					printf("Report %s has been successfully made.\n",ssmParams.m_filename);
				}
				break;

			case 5:
			default:
				cont=0;
				break;
		}
	}

	printf("==========Thank you for using our system!==========\n");
}















