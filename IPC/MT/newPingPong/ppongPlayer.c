


/** 
 *  @file ppongPlayer.c
 *  @brief PingPong Player
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */
#define _GNU_SOURCE

#include "ppongPlayer.h"
#include "prod.h"
#include "cons.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>


#define CALC_DELAY(delayStr,delay_ms) do{\
	long nanosec;\
	nanosec = (delay_ms) * 1000000;\
	(delayStr).tv_sec = nanosec / 1000000000;\
	(delayStr).tv_nsec = nanosec % 1000000000;\
}while(0)

#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcdef
#endif /*MAGIC_NUMBER*/



typedef struct ProdConsRunStr
{
	PpongPlayer* m_player;
	unsigned m_Num;
	sem_t* m_sem;
} ProdConsRunStr;


struct PpongPlayer
{
	int m_magicNum;
	
	WaitQueue* m_msgQueue;
	WaitQueue* m_ackQueue;
	
	Producer** m_prods;
	Consumer** m_cons;
	
	unsigned m_numOfProds;
	unsigned m_numOfCons;
		
	unsigned m_numOfMsgs;
	
	struct timespec m_delay;
	
};


PpongPlayer* PpongPlayer_Create(unsigned _numOfProds, unsigned _numOfCons, unsigned _numOfMsgs, long _delay_ms)
{
	PpongPlayer* ppongPlayer;
	unsigned i,j;

	if(0 == _numOfProds || 0 == _numOfCons || 0 == _numOfMsgs)
	{
		return NULL;
	}
	
	
	if(NULL == (ppongPlayer = malloc(sizeof(PpongPlayer))))
	{
		return NULL;
	}
	if(NULL == (ppongPlayer->m_prods = malloc(sizeof(Producer*)*_numOfProds)))
	{
		free(ppongPlayer);
		return NULL;
	}
	if(NULL == (ppongPlayer->m_cons = malloc(sizeof(Consumer*)*_numOfCons)))
	{
		free(ppongPlayer->m_prods);
		free(ppongPlayer);
		return NULL;
	}
	
	if(NULL == (ppongPlayer->m_msgQueue = WaitQueue_Create(QUEUE_SIZE)))
	{
		free(ppongPlayer->m_prods);
		free(ppongPlayer->m_cons);
		free(ppongPlayer);
		return NULL;
	}
	if(NULL == (ppongPlayer->m_ackQueue = WaitQueue_Create(QUEUE_SIZE)))
	{
		WaitQueue_Destroy(ppongPlayer->m_msgQueue);
		free(ppongPlayer->m_prods);
		free(ppongPlayer->m_cons);
		free(ppongPlayer);
		return NULL;
	}
	
	ppongPlayer->m_numOfProds = _numOfProds;
	ppongPlayer->m_numOfCons = _numOfCons;
		
	for(i=0 ; i< ppongPlayer->m_numOfProds ; ++i)
	{
		if(NULL == ( (ppongPlayer->m_prods)[i] = Producer_Create(ppongPlayer->m_msgQueue,
			ppongPlayer->m_ackQueue, (int)i)))
		{
			break;
		}
	}
	if(i < ppongPlayer->m_numOfProds)
	{
		for(j=0 ; j < i ; ++j)
		{
			Producer_Destroy((ppongPlayer->m_prods)[j]);
		}
		WaitQueue_Destroy(ppongPlayer->m_msgQueue);
		WaitQueue_Destroy(ppongPlayer->m_ackQueue);
		free(ppongPlayer->m_prods);
		free(ppongPlayer->m_cons);
		free(ppongPlayer);
		return NULL;	
	}
	
	for(i=0 ; i< ppongPlayer->m_numOfCons ; ++i)
	{
		if(NULL == ( (ppongPlayer->m_cons)[i] = Consumer_Create(ppongPlayer->m_msgQueue,
			ppongPlayer->m_ackQueue, (int)i)))
		{
			break;
		}
	}
	if(i < ppongPlayer->m_numOfCons)
	{
		for(j=0 ; j < i ; ++j)
		{
			Consumer_Destroy((ppongPlayer->m_cons)[j]);
		}
		for(j=0 ; j < ppongPlayer->m_numOfProds ; ++j)
		{
			Producer_Destroy((ppongPlayer->m_prods)[j]);
		}
		WaitQueue_Destroy(ppongPlayer->m_msgQueue);
		WaitQueue_Destroy(ppongPlayer->m_ackQueue);
		free(ppongPlayer->m_prods);
		free(ppongPlayer->m_cons);
		free(ppongPlayer);
		return NULL;	
	}
		
	ppongPlayer->m_numOfMsgs = _numOfMsgs;
	
	CALC_DELAY(ppongPlayer->m_delay,_delay_ms);
	
	ppongPlayer->m_magicNum = MAGIC_NUMBER;

	return ppongPlayer;
}


void PpongPlayer_Destory(PpongPlayer* _ppongPlayer)
{
	unsigned j;
	
	if(NULL==_ppongPlayer || MAGIC_NUMBER != _ppongPlayer->m_magicNum)
	{
		return;
	}
	
	_ppongPlayer->m_magicNum = -1;

	for(j=0 ; j < _ppongPlayer->m_numOfProds ; ++j)
	{
		Producer_Destroy((_ppongPlayer->m_prods)[j]);
	}
	for(j=0 ; j < _ppongPlayer->m_numOfCons ; ++j)
	{
		Consumer_Destroy((_ppongPlayer->m_cons)[j]);
	}
	
	WaitQueue_Destroy(_ppongPlayer->m_msgQueue);
	WaitQueue_Destroy(_ppongPlayer->m_ackQueue);
	
	free(_ppongPlayer->m_prods);
	free(_ppongPlayer->m_cons);
	free(_ppongPlayer);	
}


static void* ProducerRun(void* _params)
{
	long i;
	PpongPlayer *player;
	unsigned id;
	ProdConsRunStr* prodRun = (ProdConsRunStr*)_params;
	
	player = prodRun->m_player;
	id = prodRun->m_Num;
	
	sem_post(prodRun->m_sem);
	
	for(i=0 ; i < player->m_numOfMsgs ; ++i)
	{	
		if(0 != Producer_SendMsg((player->m_prods)[id],(void*)(i+1)))
		{
			fprintf(stderr,"I am %u and I have msg sending error.\n",id);
			return (void*)-1;
		}
		if(0 !=  Producer_ReceiveAck((player->m_prods)[id]))
		{
			fprintf(stderr,"I am %u and I have ack receiving error.\n",id);
			return (void*)-2;
		}
		
		printf("%lu acks left in the system.\n",
			WaitQueue_GetSize(player->m_ackQueue));
		
		nanosleep(&(player->m_delay),NULL);
	}
	return NULL;
}

static void* ConsumerRun(void* _params)
{
	int res;
	PpongPlayer *player;
	unsigned id;
	ProdConsRunStr* consRun = (ProdConsRunStr*)_params;
	
	player = consRun->m_player;
	id = consRun->m_Num;
	
	sem_post(consRun->m_sem);
		
	do
	{	
		res=Consumer_RecieveAndAck((player->m_cons)[id]);
		if(CONS_STOPED == res )
		{
			break;
		}
		if(0!=res)
		{
			fprintf(stderr,"I am %u and I have msg receive and ack error.\n",id);
			return (void*)-1;
		}
		
		printf("%lu messages left in the system.\n",
			WaitQueue_GetSize(player->m_msgQueue));
		/*
		nanosleep(&(player->m_delay),NULL);
		*/
	}while(1);
	
	return NULL;
}


int PpongPlayer_Run(PpongPlayer* _ppongPlayer)
{
	unsigned i;
	int stat;
	pthread_t *prodThreads;
	pthread_t *consThreads;
	sem_t sem;
	ProdConsRunStr pcrStr;
	void* res;
		
	if(NULL==_ppongPlayer)
	{
		return -1;
	}
	
	if(NULL == (prodThreads = malloc(sizeof(pthread_t)*_ppongPlayer->m_numOfProds)))
	{
		return -2;
	}
	if(NULL == (consThreads = malloc(sizeof(pthread_t)*_ppongPlayer->m_numOfCons)))
	{
		free(prodThreads);
		return -3;
	}
	
	pcrStr.m_player = _ppongPlayer;
	pcrStr.m_sem = &sem;
	sem_init(&sem,0,0);
	
	for(i=0 ; i < _ppongPlayer->m_numOfProds ; ++i)
	{
		pcrStr.m_Num = i;
		if(0!= (stat = pthread_create(prodThreads+i,NULL,ProducerRun,&pcrStr)))
		{
			fprintf(stderr,"Prod thread create error #%d!\n",stat);
			free(prodThreads);
			free(consThreads);
			return -4;
		}
		sem_wait(&sem);
	}
	for(i=0 ; i < _ppongPlayer->m_numOfCons ; ++i)
	{
		pcrStr.m_Num = i;
		if(0!= (stat = pthread_create(consThreads+i,NULL,ConsumerRun,&pcrStr)))
		{
			fprintf(stderr,"Cons thread create error #%d!\n",stat);
			free(prodThreads);
			free(consThreads);
			return -5;
		}
		sem_wait(&sem);
	}
	
	for(i=0 ; i < _ppongPlayer->m_numOfProds ; ++i)
	{	
		pthread_join(prodThreads[i],&res);
	}
	
	Consumer_StopThemAll((_ppongPlayer->m_cons)[0]);
	for(i=0 ; i < _ppongPlayer->m_numOfCons ; ++i)
	{	
		pthread_join(consThreads[i],&res);
	}
	
	free(prodThreads);
	free(consThreads);

	return 0;
}































