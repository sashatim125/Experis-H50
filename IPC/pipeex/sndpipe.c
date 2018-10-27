
/** 
 *  @file sndpipe.c
 *  @brief program to send file through named pipe
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */
 
#define _POSIX_C_SOURCE 199309L

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "pipeComm.h"

#define USAGE_NOTE do{fprintf(stderr, "Usage: %s -f source_file_name -p pipe_name\n",\
		    		argv[0]);}while(0)


int main(int argc, char *argv[])
{

	char const *fileName;
	char const *pipeName;
	int opt;
	
	if(1==argc)
	{
		USAGE_NOTE;
		exit(EXIT_FAILURE);
	}

    while ((opt = getopt(argc, argv, "f:p:")) != -1)
    {
    	switch(opt)
    	{
    		case 'f':
    			fileName = optarg;
    			break;
    		case 'p':
    			pipeName = optarg;
    			break;
    		
    		default:
    			USAGE_NOTE;
		    	exit(EXIT_FAILURE);
		}
    }
    
    if(0 != sendFileToPipe(fileName,pipeName))
    {
    	return -1;
    }

	return 0;
}


