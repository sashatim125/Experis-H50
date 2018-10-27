
/** 
 *  @file confFileParser.c
 *  @brief Configuration file parser(of ini format)
 *	
 *  @warning The functions ARE NOT thread safe
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
 
#include <stdio.h>
#include <string.h>

#include "confFileParser.h"

#define LINE_BUFFER_LENGTH 1024



int ConfFileParser_GetSection(FILE* _filePtr, const char* _section)
{
	int res;
	char buff[1024];
	char secNameBuff[1024];
	char lineBuff[1024];

	if(NULL == _filePtr)
	{
		return -1;
	}

	sprintf(secNameBuff,"[%s]",_section);

	res = -1;
	
	rewind(_filePtr);
	
	while(NULL != fgets(buff,LINE_BUFFER_LENGTH,_filePtr))
	{
		sscanf(buff,"%s",lineBuff);
	
		if(0 == strcmp(lineBuff,secNameBuff))
		{
			res = 0;
			break;
		}
	}
	
	return res;
}


int ConfFileParser_GetNextPair(FILE* _filePtr, char* _var, char* _value)
{
	char buff[1024];
	
	if(NULL == fgets(buff,LINE_BUFFER_LENGTH,_filePtr))
	{
		return -1;
	}
	
	return (2 == sscanf(buff,"%s = %s",_var,_value)) ? 0 : -1;
}














