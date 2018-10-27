
/** 
 *  @file confFileParserTest.c
 *  @brief Configuration file parser(of ini format) TEST
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
 
#include <stdio.h>
#include <string.h>

#include "confFileParser.h"

#define TEST_FILE_NAME "./test.ini"
#define SEC1  "section1"
#define SEC2  "section2"
#define SEC3  "section3"
#define SEC4  "section4"
#define SEC10 "section10"

#define BUFFER_LENGTH 1024

int main()
{
	FILE *f;
	char var[BUFFER_LENGTH] , val[BUFFER_LENGTH];
	
	if(NULL == (f = fopen(TEST_FILE_NAME,"r")))
	{
		fprintf(stderr,"File open error.\n");
		return -1;
	}
	
	if(0 != ConfFileParser_GetSection(f,SEC1))
	{
		fprintf(stderr,"Sec1 open error.\n");
		return -1;
	}
	
	while(0==ConfFileParser_GetNextPair(f,var,val))
	{
		printf("var is %s, val is %s.\n",var,val);	
	}
	
	if(0 != ConfFileParser_GetSection(f,SEC2))
	{
		fprintf(stderr,"Sec2 open error.\n");
		return -1;
	}
	
	while(0==ConfFileParser_GetNextPair(f,var,val))
	{
		printf("var is %s, val is %s.\n",var,val);	
	}

	if(0 != ConfFileParser_GetSection(f,SEC4))
	{
		fprintf(stderr,"Sec4 open error.\n");
		return -1;
	}
	
	while(0==ConfFileParser_GetNextPair(f,var,val))
	{
		printf("var is %s, val is %s.\n",var,val);	
	}

	if(0 != ConfFileParser_GetSection(f,SEC3))
	{
		fprintf(stderr,"Sec3 open error.\n");
		return -1;
	}
	
	while(0==ConfFileParser_GetNextPair(f,var,val))
	{
		printf("var is %s, val is %s.\n",var,val);	
	}


	fclose(f);

	return 0;
}


