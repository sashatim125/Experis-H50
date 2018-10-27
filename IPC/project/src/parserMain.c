

/** 
 *  @file parserMain.c
 *  @brief parsing the CDR file and sending the structured data to the msgQ
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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
 
#include "parser.h"
#include "formatedPrint.h"
#include "commonStructs.h"


#define CDR_IN_DIR "./cdr_in/"
#define CDR_OUT_DIR "./cdr_out/"
#define MAX_CDR_FILE_NAME_LENGTH 256

/*
 * _argv[1] is a cdr file name
 */

int main(int _argc, char* _argv[])
{
	int mqid;
	key_t key;
	int res;
	char fileName1[MAX_CDR_FILE_NAME_LENGTH];
	char fileName2[MAX_CDR_FILE_NAME_LENGTH];
	
	assert(_argc==2);
	
	sprintf(fileName1,"%s%s",CDR_IN_DIR,_argv[1]);
	
	if(0 > (key = ftok("ParserUpserterKeyFile.key",1)))
	{
		perror("parserMain : ftok");
		return -1;
	}
	
	if(0 > (mqid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("parserMain : msgget");
		return -2;
	}
	
	if(0!= (res = ParseCDRFile(fileName1)))
	{
		fprintf(stderr,"parserMain : ParseCDRFile returned with error %d.\n",res);
		return res;
	}
	
	sprintf(fileName2,"%s%s",CDR_OUT_DIR,_argv[1]);
	
	if(0!=rename(fileName1,fileName2))
	{
		perror("parserMain : file remove error");
		return -3;
	}
	
	return 0;
}


