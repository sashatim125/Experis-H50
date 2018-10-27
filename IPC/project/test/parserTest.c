

/** 
 *  @file parserTest.c
 *  @brief test for parsing the CDR file and sending the structured data to the msgQ
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

#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
 
#include "parser.h"
#include "formatedPrint.h"
#include "commonStructs.h"

static void PrintCDR(CDR* _cdr)
{
	printf("\
IMSI = %lu\n\
MSISDN = %lu\n\
IMEI = %lu\n\
operBrand = %s\n\
MCCMNC = %lu\n\
callType = %d\n\
callDate = %s\n\
callType = %s\n\
Call duration = %lu\n\
Number of Mb :\n\
Downloaded      = %lu\n\
Uploaded        = %lu\n\
partyMSISDN = %lu\n\
partyMCCMNC = %lu\n\n",
	_cdr->m_IMSI,
	_cdr->m_MSISDN,
	_cdr->m_IMEI,
	_cdr->m_operBrand,
	_cdr->m_MCCMNC,
	_cdr->m_callType,
	_cdr->m_callDate,
	_cdr->m_callTime,
	_cdr->m_dur,
	_cdr->m_down,
	_cdr->m_up,
	_cdr->m_partyMSISDN,
	_cdr->m_partyMCCMNC);
}

int main(int _argc, char* _argv[])
{
	/*char cdrString[][1024]={
	"1|111|999|pelephone|45202|MOC|01.01.2018|12:15:16|10|0|0|879|45202",
	"2|111|999|cellcom|45203|MOC|01.01.2018|10:16:16|17|0|0|125|45202",
	"3|111|999|parthner|45204|MOC|01.01.2018|11:15:16|25|0|0|925|45203",
	"2|111|999|pelephone|45202|SMS-MO|01.01.2018|10:15:16|0|0|0|125|45202",
	"2|111|999|pelephone|45202|SMS-MT|01.01.2018|14:15:17|0|0|0|125|45202",
	"2|111|999|pelephone|45202|GPRS|01.01.2018|14:15:18|0|15|25|125|45202"
	};
	*/
	int mqid;
	key_t key;
	int i;
	
	struct 
	{
		long m_type;
		char m_buff[MAX_STRUCTURE_SIZE];
	} msgBuff;
	
	if(0 > (key = ftok("ParserUpserterKeyFile.key",1)))
	{
		perror("parserMain : ftok");
		return -2;
	}
	
	if(0 > (mqid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("parserMain : msgget");
		return -3;
	}
	/*
	for(i=0 ; i<6 ; ++i)
	{
		printf("ParseCDR result is %d\n",ParseCDR(cdrString[i],mqid));
	}
	*/
	/*
	ParseCDRFile(_argv[1]);
	*/
	for(i=0 ; i<6 ; ++i)
	{
		msgrcv(mqid,&msgBuff,sizeof(CDR),0,0);
		PrintCDR((CDR*)&msgBuff.m_buff);
	}
	
	
	













	return 0;
}


