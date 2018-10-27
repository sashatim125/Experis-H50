

#define _GNU_SOURCE

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>



#define MSG_BUFFER_SIZE 1024

#define MSG_STRING "Msg for you !\n"

#define DEFAULT_READERS_NUM 15

typedef struct Params
{
	int* m_isMsg;

	char* m_msg; /*<< null terminated string*/
	
	pthread_mutex_t* m_isMsgMutex;
	
	pthread_cond_t* m_isMsgCond; 
	
	sem_t* m_readersSem;
		
} Params;



static void* Writer(void* _p)
{
	Params *params = (Params*)_p;
	
	if(0!=sem_wait(params->m_readersSem))
	{
		perror("sem wait for readers error\n");
		return (void*)(-1);
	}
	
	if(0!=pthread_mutex_lock(params->m_isMsgMutex))
	{
		fprintf(stderr,"Locking of writer error!\n");
		return (void*)(-3);
	}
	
	memcpy(params->m_msg,MSG_STRING,sizeof(MSG_STRING));
	
	*(params->m_isMsg) = 1;
	
	if(0!=pthread_mutex_unlock(params->m_isMsgMutex))
	{
		fprintf(stderr,"Unocking of writer error!\n");
		return (void*)(-3);
	}
	
	if(0!=pthread_cond_broadcast(params->m_isMsgCond))
	{
		fprintf(stderr,"Waking readers error!\n");
		return (void*)(-2);
	}
	
	return NULL;
}


static void* Reader(void* _p)
{
	Params *params = (Params*)_p;
	
	if(0!=sem_post(params->m_readersSem))
	{
		perror("sem post for readers error\n");
		return (void*)(-1);
	}
	
	if(0!=pthread_mutex_lock(params->m_isMsgMutex))
	{
		fprintf(stderr,"Locking of writer error!\n");
		return (void*)(-2);
	}
	
	if/*while*/ (!*(params->m_isMsg))
	{
		if(0!=pthread_cond_wait(params->m_isMsgCond,params->m_isMsgMutex))
		{
			fprintf(stderr,"Waiting for msgs error!\n");
			return (void*)(-3);
		}
	}
	
	printf("I am %lu params->m_isMsg is %d.\n",pthread_self(),*(params->m_isMsg));
	fprintf(stdout,"%s",params->m_msg);
	/*
	*(params->m_isMsg) = 0;
	*/
	if(0!=pthread_mutex_unlock(params->m_isMsgMutex))
	{
		fprintf(stderr,"Unocking of reader error!\n");
		return (void*)(-4);
	}
	
	return NULL;
}






int main()
{
	Params parStr;
	int isMsg;
	char buff[MSG_BUFFER_SIZE];
	pthread_mutex_t isMsgMutex;
	pthread_cond_t isMsgCond; 
	sem_t readersSem;
	int i, stat;
	void *res;
	int round=5,j;
	
	pthread_t writer;
	pthread_t *readers;
	
	
	parStr.m_isMsg = &isMsg;
	parStr.m_msg = buff;
	parStr.m_isMsgMutex = &isMsgMutex;
	parStr.m_isMsgCond = &isMsgCond;
	parStr.m_readersSem = &readersSem;
	
	for(j=0 ; j < round ; ++j)
	{
		isMsg = 0;
		pthread_mutex_init(&isMsgMutex,NULL);
		pthread_cond_init(&isMsgCond,NULL);
		sem_init(&readersSem,0,0);
	
		if(NULL == (readers = malloc(sizeof(pthread_t)*DEFAULT_READERS_NUM)))
		{
			fprintf(stderr,"malloc error!\n");
			return -1;
		}
	
		if(0!= (stat = pthread_create(&writer,NULL,Writer,&parStr)))
		{
			fprintf(stderr,"Writer thread create error #%d!\n",stat);
			free(readers);
			return -2;
		}
	
		for(i=0 ; i < DEFAULT_READERS_NUM ; ++i)
		{
			if(0!= (stat = pthread_create(readers+i,NULL,Reader,&parStr)))
			{
				fprintf(stderr,"Reader thread create error #%d!\n",stat);
				free(readers);
				return -2;
			}	
		}
	
		pthread_join(writer,&res);
		for(i=0 ; i < DEFAULT_READERS_NUM ; ++i)
		{
			pthread_join(readers[i],&res);	
		}
		sleep(1);
	}
	free(readers);
	return 0;
}



