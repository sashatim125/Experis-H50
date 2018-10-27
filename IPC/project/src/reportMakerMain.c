

/** 
 *  @file reportMakerMain.c
 *  @brief make a report file from the given snapshot file
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "reportMaker.h"

/*
 * _argv[1] is a snapshot file name
 */

int main(int _argc, char* _argv[])
{
	AggregatedDataType adt;
	
	assert(_argc==2);

	if (NULL!=strstr(_argv[1],SUBSCRIBER_FILE_EXTENTION))
	{
		adt = SUBSCRIBER;
	}else if (NULL!=strstr(_argv[1],OPERATOR_FILE_EXTENTION))
	{
		adt = OPERATOR;
	}else
	{
		fprintf(stderr,"ReportMakerMain: snapshot filename %s has error.\n",_argv[1]);
		return -1;
	}

	if(0!= ReportMaker(adt,_argv[1]))
	{
		fprintf(stderr,"ReportMakerMain: ReportMaker has error.\n");
		return -2;
	}

	return 0;
}


