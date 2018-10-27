
/** 
 *  @file barrierTest.c
 *  @brief Test the Barrier with conters/summarizer threads
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

#define DEFAULT_ROUNDS 5;
#define DEFAULT_COUNTERS 10;

#define USAGE_NOTE do{\
	fprintf(stderr, "Usage: %s [-c] num_of_counters [-r] num_of_rounds \n",_argv[0]);\
}while(0)

typedef struct Args
{
	unsigned long m_counters;
	
	unsigned long m_rounds;

} Args;

typedef struct Params
{
	unsigned long m_myId;
	
	unsigned long m_numOfRounds;
	
	unsigned long m_numOfCounters;
	
	unsigned long* m_counters;
	
	unsigned long m_sum;
	
	sem_t m_idSafeSem;
	
	Barrier* m_barrier;
		
} Params;



static int parseArgs(int _argc, char *_argv[], Args *_args)
{
	int opt;
	
	memset(_args,0,sizeof(Args));

    while ((opt = getopt(_argc, _argv, "c:r:")) != -1)
    {
    	switch(opt)
    	{
    		case 'r':
    			sscanf(optarg,"%lu",&(_args->m_rounds));
    			break;
    		case 'c':
	    		sscanf(optarg,"%lu",&(_args->m_counters));
    			break;
    		
    		default:
    			USAGE_NOTE;
		    	exit(EXIT_FAILURE);
		}
    }
    
    if(0 == _args->m_rounds)
    {
    	_args->m_rounds = DEFAULT_ROUNDS;
    }
     if(0 == _args->m_counters)
    {
    	_args->m_counters = DEFAULT_COUNTERS;
    }
    
    return 0;
}


static void SummFunc(void *_p)
{
	Params *params = (Params*)_p;
	unsigned long i;
	
	params->m_sum = 0;
	for(i=0 ; i < params->m_numOfCounters ; ++i)
	{
		params->m_sum += params->m_counters[i];
	}
	printf("I know ! The sum is %lu !\n",params->m_sum);
}



static void* Summarizer(void* _p)
{
	Params *params = (Params*)_p;
	unsigned long j, correctSum, problemRounds;
	
	correctSum = (params->m_numOfCounters)*(params->m_numOfCounters-1)/2;
	
	problemRounds = 0;
	for(j=0 ; j < params->m_numOfRounds ; ++j)
	{	
		
		if(0 != Barrier_Wait(params->m_barrier,SummFunc,_p))
		{
			fprintf(stderr,"Summarizer: Barrier_Wait error!\n");
			return (void*)(-1);
		}
		
		if(params->m_sum != correctSum)
		{
			fprintf(stderr,"On round %lu we have incorrect sum of %lu \
instead of %lu.\n",j,params->m_sum,correctSum);
			++problemRounds;
		}else
		{
			printf("Round %lu - everything OK!.\n",j);
		}
	}
	printf("There were %lu problematic rounds.\n",problemRounds);
	
	return NULL;
}

static void* Counter(void* _p)
{
	Params *params = (Params*)_p;
	unsigned long myId = params->m_myId;
	unsigned long i,j;
	
	sem_post(&(params->m_idSafeSem));
	
	for(j=0 ; j < params->m_numOfRounds ; ++j)
	{
		params->m_counters[myId] = 0;

		for(i=1 ; i <= myId ; ++i)
		{
			params->m_counters[myId] += 1;
			sleep((unsigned)i%2);
		}
		
		if(0 != Barrier_Wait(params->m_barrier,NULL,NULL))
		{
			fprintf(stderr,"Counter: Barrier_Wait on summarizer  error!\n");
			return (void*)(-1);
		}
	}
	
	return NULL;
}



int main(int _argc, char *_argv[])
{
	Params parStruct;
	pthread_t summarizerTread;
	pthread_t *counterThreads;
	unsigned long j;
	void* res;
	int stat;
	Args arguments;	
	
    if(0 != parseArgs(_argc,_argv,&arguments))
    {
    	exit(EXIT_FAILURE);
    }
	
	parStruct.m_numOfCounters = arguments.m_counters;
	parStruct.m_numOfRounds = arguments.m_rounds;
		
	if(NULL == ( parStruct.m_barrier = Barrier_Create(arguments.m_counters+1)))
	{
		fprintf(stderr,"Main: Barrier_Create error!\n");
		return -1;
	}
	if( 0 != sem_init(&(parStruct.m_idSafeSem),0,0))
	{
		fprintf(stderr,"Main: Sem init error!\n");
		return -2;
	}
	if(NULL == (counterThreads = malloc(sizeof(pthread_t) * arguments.m_counters)))
	{
		fprintf(stderr,"Main: pthread_t malloc error!\n");
		return -3;
	}
	if(NULL == (parStruct.m_counters = calloc(1,sizeof(*(parStruct.m_counters))* arguments.m_counters)))
	{
		fprintf(stderr,"Main: counters malloc error!\n");
		free(counterThreads);
		Barrier_Destroy(parStruct.m_barrier);
		return -4;
	}
	for(j=0 ; j < arguments.m_counters ; ++j)
	{	
		parStruct.m_myId = j;
	
		if(0!= (stat = pthread_create(&(counterThreads[j]),NULL,Counter,&parStruct)))
		{
			fprintf(stderr,"Main: counter thread create error #%d!\n",stat);
			free(counterThreads);
			free(parStruct.m_counters);
			Barrier_Destroy(parStruct.m_barrier);
			return -5;
		}
		sem_wait(&(parStruct.m_idSafeSem));
	}

	if(0!= (stat = pthread_create(&summarizerTread,NULL,Summarizer,&parStruct)))
	{
		fprintf(stderr,"Summarizer thread create error #%d!\n",stat);
		free(counterThreads);
		free(parStruct.m_counters);
		Barrier_Destroy(parStruct.m_barrier);
		return -6;
	}

	pthread_join(summarizerTread,&res);
	for(j=0 ; j < arguments.m_counters ; ++j)
	{
		pthread_join(counterThreads[j],&res);	
	}
	
	free(counterThreads);
	free(parStruct.m_counters);
	Barrier_Destroy(parStruct.m_barrier);
	
	return 0;
}












