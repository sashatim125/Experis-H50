
/** 
 *  @file parser.c
 *  @brief parsing the CDR file and sending the structured data to the msgQ
 *	
 *  @details  see comments
 *  
 *  @author Alexander Timoshenko sashatim125@gmail.com
 *
 * 
 */

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "commonStructs.h"

#define DELIMITER "|"

#define CALL_TYPE_STR_LENGTH 64

int ParseCDR(char* _buff, int _msgQID)
{
	char* nextField;
	CDR *cdr;
	struct 
	{
		long m_type;
		CDR m_buff;
	} msgBuff;
	char callTypeStr[CALL_TYPE_STR_LENGTH];
	
	cdr = &(msgBuff.m_buff);
	
	memset(cdr,0,sizeof(CDR));
	
	if(NULL == (nextField = strtok (_buff,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_IMSI))
	{
		return -1;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_MSISDN))
	{
		return -2;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_IMEI))
	{
		return -3;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		NULL==strncpy(cdr->m_operBrand,nextField,OPERATOR_BRANDNAME_SIZE-1))
	{
		return -4;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_MCCMNC))
	{
		return -5;
	}
	
	
	if(NULL == (nextField = strtok (NULL,DELIMITER)))
	{
		return -6;
	}
	if(1!=sscanf(nextField,"%s",callTypeStr))
	{
		return -6;
	}
	if(0==strcmp(callTypeStr,"MOC"))
	{
		cdr->m_callType = MOC;
	}else if(0==strcmp(callTypeStr,"MTC"))
	{
		cdr->m_callType = MTC;
	}else if(0==strcmp(callTypeStr,"SMS-MO"))
	{
		cdr->m_callType = SMS_MO;
	}else if(0==strcmp(callTypeStr,"SMS-MT"))
	{
		cdr->m_callType = SMS_MT;
	}else if(0==strcmp(callTypeStr,"GPRS"))
	{
		cdr->m_callType = GPRS;
	}else
	{
		return -6;
	}
	
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		NULL==strncpy(cdr->m_callDate,nextField,DATE_SIZE-1))
	{
		return -7;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		NULL==strncpy(cdr->m_callTime,nextField,TIME_SIZE-1))
	{
		return -8;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_dur))
	{
		return -9;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_down))
	{
		return -10;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_up))
	{
		return -11;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_partyMSISDN))
	{
		return -12;
	}
	if(NULL == (nextField = strtok (NULL,DELIMITER)) ||
		1!=sscanf(nextField,"%lu",&cdr->m_partyMCCMNC))
	{
		return -13;
	}
	
	msgBuff.m_type = 1;
	
	if(0!= msgsnd(_msgQID,&msgBuff,sizeof(CDR),0))
	{
		perror("");
		fprintf(stderr,"ParseCDR %d has message sending error.\n",getpid());
		return -14;
	}

	return 0;
}



int ParseCDRFile(const char* _fileName)
{
	int mqid;
	key_t key;
	FILE *cdrFile;
	char buff[MAX_CDR_STRING_SIZE];
	
	assert(NULL!=_fileName);
	
	if(NULL == (cdrFile = fopen(_fileName,"r")))
	{
		fprintf(stderr,"ParseCDRFile : file %s open error.\n",_fileName);
		return -1;
	}
	
	if(0 > (key = ftok("ParserUpserterKeyFile.key",1)))
	{
		perror("ParseCDRFile : ftok");
		fclose(cdrFile);
		return -2;
	}
	
	if(0 > (mqid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("ParseCDRFile : msgget");
		fclose(cdrFile);
		return -3;
	}

	while(NULL != fgets(buff,MAX_CDR_STRING_SIZE,cdrFile))
	{
		if(0!= ParseCDR(buff,mqid))
		{
			fclose(cdrFile);
			return -4;
		}
	}

	fclose(cdrFile);
	return 0;
}

















