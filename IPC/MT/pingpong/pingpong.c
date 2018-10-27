



/** 
 *  @file pingpong.c
 *  @brief PingPong Messsages in threads on waitable generic queue
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#define _GNU_SOURCE

#include "ppongPlayer.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_NUM_OF_MSG 5

#define DEFAULT_DELAY 1000l

#define DEFAULT_NUM_OF_PRODS 1

#define DEFAULT_NUM_OF_CONS 1


#define USAGE_NOTE do{\
	fprintf(stderr, "Usage: %s [-n] num_of_messages [-p] num_of_producers \
[-c] num_of_consumers [-s] delay_ms \n",_argv[0]);\
}while(0)

typedef struct Args
{
	long m_delay_ms;
	
	unsigned m_numOfProds;
	
	unsigned m_numOfCons;
	
	unsigned m_numOfMsgs;
} Args;


static int parseArgs(int _argc, char *_argv[], Args *_args)
{
	int opt;
	
	memset(_args,0,sizeof(Args));

    while ((opt = getopt(_argc, _argv, "n:p:c:s:")) != -1)
    {
    	switch(opt)
    	{
    		case 's':
    			sscanf(optarg,"%ld",&(_args->m_delay_ms));
    			break;
    		case 'n':
	    		sscanf(optarg,"%u",&(_args->m_numOfMsgs));
    			break;
    		case 'p':
    			sscanf(optarg,"%u",&(_args->m_numOfProds));
    			break;
    		case 'c':
    			sscanf(optarg,"%u",&(_args->m_numOfCons));
    			break;
    		
    		default:
    			USAGE_NOTE;
		    	exit(EXIT_FAILURE);
		}
    }
    
    if(0 == _args->m_numOfProds)
    {
    	_args->m_numOfProds = DEFAULT_NUM_OF_PRODS;
    }
     if(0 == _args->m_numOfCons)
    {
    	_args->m_numOfCons = DEFAULT_NUM_OF_CONS;
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



int main(int _argc, char *_argv[])
{
	Args arguments;
	
	PpongPlayer *player;	
	
    if(0 != parseArgs(_argc,_argv,&arguments))
    {
    	exit(EXIT_FAILURE);
    }
    
	player = PpongPlayer_Create(arguments.m_numOfProds, arguments.m_numOfCons, 
		arguments.m_numOfMsgs, arguments.m_delay_ms);
    
    if(NULL == player)
    {
    	exit(EXIT_FAILURE);
    }
    
    PpongPlayer_Run(player);
        
	PpongPlayer_Destory(player);

	return 0;
}


















