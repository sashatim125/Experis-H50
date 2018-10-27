
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif


#include <assert.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <pthread.h>
#include <unistd.h>

#include "formatedPrint.h"


int main()
{
	int mqid2;
	key_t key2;
	
	struct 
	{
		long m_type;
		char m_buff[MAX_STRUCTURE_SIZE];
	} msgBuff;


	if(0 > (key2 = ftok("QueryUIKeyFile.key",1)))
	{
		perror("");
	}
	
	if(0 > (mqid2 = msgget(key2,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
	}
	
	msgrcv(mqid2,&msgBuff,MAX_STRUCTURE_SIZE,0,0);
	PrintAggregatedDataReport(stdout,SUBSCRIBER,msgBuff.m_buff);
	PrintAggregatedDataReadable(stdout,SUBSCRIBER,msgBuff.m_buff);

	msgrcv(mqid2,&msgBuff,MAX_STRUCTURE_SIZE,0,0);
	PrintAggregatedDataReport(stdout,OPERATOR,msgBuff.m_buff);
	PrintAggregatedDataReadable(stdout,OPERATOR,msgBuff.m_buff);

	return 0;
}



