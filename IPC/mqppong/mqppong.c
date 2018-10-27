

/** 
 *  @file mqppong.c
 *  @brief Message queue ping-pong
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */



#define _GNU_SOURCE

#include "queue.h"
#include "prod.h"
#include "cons.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>



#define DEFAULT_NUM_OF_MSG 5
#define DEFAULT_DELAY 1000l

#define MESSAGE_STRING "Message #"


#define USAGE_NOTE do{fprintf(stderr, "Usage: %s -n num_of_messages -p !or -c -i -s delay_ms \n",\
		    		_argv[0]);}while(0)



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

    while ((opt = getopt(_argc, _argv, "n:pcs:i")) != -1)
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
    		case 'i':
    			_args->m_shouldInit = 1;
    			break;
    		
    		default:
    			USAGE_NOTE;
		    	exit(EXIT_FAILURE);
		}
    }
    
    if((_args->m_isProd && _args->m_isCons) || (!_args->m_isProd && !_args->m_isCons))
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

static int prodRun(Producer *_prod, long m_delay_ms, int numOfMsgs)
{
	int i;
	struct timespec delay;
	long nanosec;
	char msgBuff[1024];
	
	nanosec = m_delay_ms * 1000000;
	delay.tv_sec = nanosec / 1000000000;
	delay.tv_nsec = nanosec % 1000000000;
	
	if(0!=prodStart(_prod))
	{
		return -1;
	}
	
	for(i=0 ; i < numOfMsgs ; ++i)
	{
		sprintf(msgBuff,"%s%d",MESSAGE_STRING,i);
	
		if(0!=prodSendMsg(_prod,msgBuff))
		{
			return -2;
		}

		if(0!=receiveAck(_prod))
		{
			return -3;
		}
		
		nanosleep(&delay,NULL);
	}

	if(0!=prodFinish(_prod))
	{
		return -4;
	}

	return 0;
}





int main(int _argc, char *_argv[])
{
	Args arguments;

	int msgQueue;
	int ackQueue;
	int sem;
	Producer *prod;
	Consumer *cons;
	
    if(0 != parseArgs(_argc,_argv,&arguments))
    {
    	exit(EXIT_FAILURE);
    }
    
    msgQueue = getMsgQueue();
    ackQueue = getAckQueue();
    sem = getSemaphore();
    
    if(0>msgQueue || 0>ackQueue || 0>sem)
    {
    	exit(EXIT_FAILURE);
    }
    
    if(arguments.m_shouldInit)
    {
    	if(0 != semctl(sem,0,SETVAL,0) ||
    		semctl(sem,1,SETVAL,1))
    	{
    		exit(EXIT_FAILURE);
    	}
    }
    
    if(arguments.m_isProd)
    {
    	if(NULL==(prod = prodCreate(msgQueue,ackQueue,sem,getpid())))
    	{
    		exit(EXIT_FAILURE);
    	}
    	
    	if(0!=prodRun(prod,arguments.m_delay_ms,arguments.m_numOfMsgs))
    	{
    		prodDestroy(prod);
    		exit(EXIT_FAILURE);
    	}
    	prodDestroy(prod);
    }
    
    if(arguments.m_isCons)
    {
    	if(NULL==(cons = consCreate(msgQueue,ackQueue,sem,getpid())))
    	{
    		exit(EXIT_FAILURE);
    	}
    	
    	if(0!=recieveAndAck(cons))
    	{
    		consDestroy(cons);
    		exit(EXIT_FAILURE);
    	}
    	consDestroy(cons);
    }

	return 0;
}
















