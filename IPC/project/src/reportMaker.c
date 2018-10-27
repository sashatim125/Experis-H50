

/** 
 *  @file reportMaker.c
 *  @brief the report maker api : snapshots and reports
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
#include <time.h>
#include <stdio.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include "reportMaker.h"
#include "subscrStorageManager.h"
#include "operStorageManager.h"
#include "formatedPrint.h"

#define MAX_TIME_STR_LENGTH	128


void* SnapshotMaker(void* _p)
{
	SnapshotMakerParams* params = (SnapshotMakerParams*)_p;
	SubscrStorageManager *ssm;
	OperStorageManager *osm;
	int fd;
	time_t rawtime;
	struct tm *currtime;
	char timestr[MAX_TIME_STR_LENGTH];
	char fileName[MAX_FILENAME_LENGTH];

	assert(NULL!=params->m_sm);
	
	time(&rawtime);
	currtime=localtime(&rawtime);
	strftime (timestr,MAX_TIME_STR_LENGTH,"%d-%m-%Y_%X",currtime);
	
	switch(params->m_adt)
	{
		case SUBSCRIBER :
			sprintf(fileName,"%s%s%s",SNAPSHOT_DIR,timestr,SUBSCRIBER_FILE_EXTENTION);
			sprintf(params->m_filename,"%s%s",timestr,SUBSCRIBER_FILE_EXTENTION);
			break;
		case OPERATOR :
			sprintf(fileName,"%s%s%s",SNAPSHOT_DIR,timestr,OPERATOR_FILE_EXTENTION);
			sprintf(params->m_filename,"%s%s",timestr,OPERATOR_FILE_EXTENTION);
			break;
	}
	fd = creat(fileName,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
	if(-1==fd)
	{
		perror("SnapshotMaker: create error\n");
		return (void*)-1;
	}
	
	switch(params->m_adt)
	{
		case SUBSCRIBER :
			ssm = (SubscrStorageManager*)params->m_sm;
			if(SubscrStorageManager_GetNumOfSubscribers(ssm) > 
				SubscrStorageManager_Save(ssm,fd))
			{
				fprintf(stderr,"SnapshotMaker: incomplete snapshot %s.\n",params->m_filename);
				close(fd);
				return (void*)-2;
			}
			break;
			
		case OPERATOR :
			osm = (OperStorageManager*)params->m_sm;
			if(OperStorageManager_GetNumOfOperators(osm) >
				OperStorageManager_Save(osm,fd))
			{
				fprintf(stderr,"SnapshotMaker: incomplete snapshot %s.\n",params->m_filename);
				close(fd);
				return (void*)-2;
			}
			break;	
	}
	
	close(fd);
	return (void*)0;
}



int ReportMaker(AggregatedDataType _reportType, const char* _fileName)
{
	FILE  *ssfile , *repfile;
	char snapshotFileName[MAX_FILENAME_LENGTH];
	char reportFileName[MAX_FILENAME_LENGTH];
	char buff[MAX_STRUCTURE_SIZE];
	
	assert(NULL!=_fileName);
	
	sprintf(snapshotFileName,"%s%s",SNAPSHOT_DIR,_fileName);
	sprintf(reportFileName,"%s%s",REPORT_DIR,_fileName);
	
	ssfile = fopen(snapshotFileName,"r");
	if(NULL==ssfile)
	{
		perror("ReportMaker: snapshot file open error\n");
		return -1;
	}
	
	repfile = fopen(reportFileName,"w");
	if(NULL==repfile)
	{
		perror("ReportMaker: create report file error\n");
		fclose(ssfile);
		return -2;
	}
	
	switch(_reportType)
	{
		case SUBSCRIBER:
			while(fread(buff,sizeof(AggSubscriberData),1,ssfile))
			{
				if(0!= PrintAggregatedDataReport(repfile,SUBSCRIBER,buff))
				{
					fprintf(stderr,"ReportMaker: writing to report file  %s error.\n",reportFileName);
					return -3;
				}
			}
			break;
		case OPERATOR:
			while(fread(buff,sizeof(AggOperatorData),1,ssfile))
			{
				if(0!= PrintAggregatedDataReport(repfile,OPERATOR,buff))
				{
					fprintf(stderr,"ReportMaker: writing to report file  %s error.\n",reportFileName);
					return -3;
				}
			}
			break;
	}

	fclose(ssfile);
	fclose(repfile);
	return 0;

}










