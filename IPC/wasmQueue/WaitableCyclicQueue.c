



/** 
 *  @file WaitableCyclicQueue.c
 *  @brief Waitable Cyclic Queue over shared memory
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
 
#define _GNU_SOURCE

#include "ShMemWCQueue.h"
#include "sysutils.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


#define DEFAULT_NUM_OF_MSG 5

#define DEFAULT_DELAY 1000l

#define MESSAGE_STRING "Message #"

#define MSG_BUFF_SIZE 1024

#define QUEUE_SIZE 8

#define CALC_DELAY do{\
	nanosec = _delay_ms * 1000000;\
	delay.tv_sec = nanosec / 1000000000;\
	delay.tv_nsec = nanosec % 1000000000;\
}while(0)


#define USAGE_NOTE do{\
	fprintf(stderr, "Usage: %s -n num_of_messages -p !or -c -q -s delay_ms \n",\
		_argv[0]);\
}while(0)

typedef struct Args
{
	long m_delay_ms;
	
	int m_isProd;
	
	int m_isCons;
	
	int m_shouldInit;
	
	int m_numOfMsgs;
} Args;


static int parseArgs(int _argc, char *_argv[], Args *_args)
{
	int opt;
	
	if(1==_argc)
	{
		USAGE_NOTE;
		return -1;
	}
	
	memset(_args,0,sizeof(Args));

    while ((opt = getopt(_argc, _argv, "n:pcs:q")) != -1)
    {
    	switch(opt)
    	{
    		case 's':
    			sscanf(optarg,"%ld",&(_args->m_delay_ms));
    			break;
    		case 'n':
	    		sscanf(optarg,"%d",&(_args->m_numOfMsgs));
    			break;
    		case 'p':
    			_args->m_isProd = 1;
    			break;
    		case 'c':
    			_args->m_isCons = 1;
    			break;
    		case 'q':
    			_args->m_shouldInit = 1;
    			break;
    		
    		default:
    			USAGE_NOTE;
		    	exit(EXIT_FAILURE);
		}
    }
    
    if(_args->m_isProd && _args->m_isCons)
    {
    	USAGE_NOTE;
		return -1;
    }
    if(0 == _args->m_delay_ms)
    {
    	_args->m_delay_ms = DEFAULT_DELAY;
    }
    if(0 == _args->m_numOfMsgs)
    {
    	_args->m_numOfMsgs = DEFAULT_NUM_OF_MSG;
    }
    
    return 0;
}

static int prodRun(ShMemWCQueue* _queue, long _delay_ms, int numOfMsgs)
{
	int i;
	struct timespec delay;
	long nanosec;
	char msgBuff[MSG_BUFF_SIZE];
	
	CALC_DELAY;
	
	for(i=0 ; i < numOfMsgs ; ++i)
	{
		sprintf(msgBuff,"%s%3d from %5d",MESSAGE_STRING,i,getpid());
		
		printf("Sending msg : %s.\n",msgBuff);
	
		if(0!=ShMemWCQueue_Insert(_queue,msgBuff,1+strlen(msgBuff)))
		{
			fprintf(stderr,"I am %d and I have insert error.\n",getpid());
			return -1;
		}
		
		printf("%lu messages left in the system.\n",ShMemWCQueue_GetSize(_queue));
		
		nanosleep(&delay,NULL);
	}
	return 0;
}

static int consRun(ShMemWCQueue* _queue, long _delay_ms, int numOfMsgs)
{
	int i;
	struct timespec delay;
	long nanosec;
	char msgBuff[MSG_BUFF_SIZE];
	size_t itemSize;
	
	CALC_DELAY;
	
	for(i=0 ; i < numOfMsgs ; ++i)
	{
	
		if(0!=ShMemWCQueue_Remove(_queue,msgBuff,MSG_BUFF_SIZE,&itemSize))
		{
			fprintf(stderr,"I am %d and I have remove error.\n",getpid());
			return -1;
		}
		
		printf("Msg received : %s.\n",msgBuff);
		
		printf("%lu messages left in the system.\n",ShMemWCQueue_GetSize(_queue));
		
		nanosleep(&delay,NULL);
	}
	return 0;
}


int main(int _argc, char *_argv[])
{
	Args arguments;
	
	void *shmem;
	int shmemID;
	ShMemWCQueue* queue;
	
    if(0 != parseArgs(_argc,_argv,&arguments))
    {
    	exit(EXIT_FAILURE);
    }
        
    shmemID = InitSharedMem();
/*    
    printf("shmem id is %d.\n",shmemID);
*/    
	shmem = AttachToSharedMem(shmemID);
/*	
	printf("shmem adress is %p.\n",shmem);
*/	
	    
    if(arguments.m_shouldInit)
    {
    	if(NULL == (queue = ShMemWCQueue_Init(shmem,SHARED_MEM_SIZE,QUEUE_SIZE)))
    	{
    		fprintf(stderr,"ShMemWCQueue_Init error.\n");
    		exit(EXIT_FAILURE);
    	}
    }else
    {
    	queue = ShMemWCQueue_Connect(shmem);
    }
    
    if(arguments.m_isProd)
    {
    	if(0!=prodRun(queue,arguments.m_delay_ms,arguments.m_numOfMsgs))
    	{
    		exit(EXIT_FAILURE);
    	}
    }
    
    if(arguments.m_isCons)
    {    	
    	if(0!=consRun(queue,arguments.m_delay_ms,arguments.m_numOfMsgs))
    	{
    		exit(EXIT_FAILURE);
    	}
    }

	return 0;
}


















