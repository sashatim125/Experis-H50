
/** 
 *  @file barrierTestNew.c
 *  @brief Test the Barrier with multiple threads
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#define _GNU_SOURCE


#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "barrier.h"

#define DEFAULT_NUM_OF_THREADS 20
#define DEFAULT_CAPACITY 10;
#define DEFAULT_ROUNDS 10;

#define USAGE_NOTE do{\
	fprintf(stderr, "Usage: %s [-t] num_of_threads  [-c] capacity  [-r] num_of_rounds\n",_argv[0]);\
}while(0)

typedef struct Args
{
	unsigned long m_numOfThreads;
	unsigned long m_capacity;
	unsigned long m_rounds;

} Args;

static Barrier *g_barrier;
static unsigned long g_rounds;

static int parseArgs(int _argc, char *_argv[], Args *_args)
{
	int opt;
	
	memset(_args,0,sizeof(Args));

    while ((opt = getopt(_argc, _argv, "t:c:r:")) != -1)
    {
    	switch(opt)
    	{
    		case 't':
    			sscanf(optarg,"%lu",&(_args->m_numOfThreads));
    			break;
    			
    		case 'c':
    			sscanf(optarg,"%lu",&(_args->m_capacity));
    			break;
    		
    		case 'r':
    			sscanf(optarg,"%lu",&(_args->m_rounds));
    			break;
    		
    		default:
    			USAGE_NOTE;
		    	exit(EXIT_FAILURE);
		}
    }
    
    if(0 == _args->m_numOfThreads)
    {
    	_args->m_numOfThreads = DEFAULT_NUM_OF_THREADS;
    }
    if(0 == _args->m_capacity)
    {
    	_args->m_numOfThreads = DEFAULT_CAPACITY;
    }
    if(0 == _args->m_rounds)
    {
    	_args->m_rounds = DEFAULT_ROUNDS;
    }
    
    return 0;
}


static void InnerFunc(void *_id)
{
	sleep(1);
	printf("I am %lu in InnerFunc !\n",(unsigned long)_id);
	fflush(stdout);
}


static void* ThreadFunc(void* _id)
{
	unsigned long myID = (unsigned long)_id;
	unsigned long i,j;
	
	for(j=0 ; j < g_rounds ; ++j)
	{
		for(i=1 ; i <= myID ; ++i)
		{
			/*sleep((unsigned)i%2);*/;
		}
		printf("I am %lu before barrier in round %lu !\n",myID,j);
		fflush(stdout);
		if(0 != Barrier_Wait(g_barrier,InnerFunc,_id))
		{
			fprintf(stderr,"ThreadFunc: Barrier_Wait error!\n");
			return (void*)(-1);
		}
		printf("I am %lu after barrier in round %lu !\n",myID,j);
		fflush(stdout);
		sleep(2);
	}
	
	return NULL;
}



int main(int _argc, char *_argv[])
{
	pthread_t *threads;
	unsigned long j;
	void* res;
	int stat;
	Args arguments;	
	
    if(0 != parseArgs(_argc,_argv,&arguments))
    {
    	exit(EXIT_FAILURE);
    }
    
    g_rounds = arguments.m_rounds;
		
	if(NULL == (g_barrier = Barrier_Create(arguments.m_capacity)))
	{
		fprintf(stderr,"Main: Barrier_Create error!\n");
		return -1;
	}

	if(NULL == (threads = malloc(sizeof(pthread_t) * arguments.m_numOfThreads)))
	{
		fprintf(stderr,"Main: pthread_t malloc error!\n");
		return -3;
	}
	
	for(j=0 ; j < arguments.m_numOfThreads ; ++j)
	{	
		if(0!= (stat = pthread_create(&(threads[j]),NULL,ThreadFunc,(void*)j)))
		{
			fprintf(stderr,"Main: counter thread create error #%d!\n",stat);
			free(threads);
			Barrier_Destroy(g_barrier);
			return -5;
		}
	}

	for(j=0 ; j < arguments.m_numOfThreads ; ++j)
	{
		pthread_join(threads[j],&res);	
	}
	
	free(threads);
	Barrier_Destroy(g_barrier);
	
	return 0;
}












