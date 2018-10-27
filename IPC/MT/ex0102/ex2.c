


#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>

#define THREADS_NUM 100

/*int id_g=0;*/
/*pthread_mutex_t m_g = PTHREAD_MUTEX_INITIALIZER;*/


sem_t sem;

void *threadFunc(void* _arg)
{
	int id;
	/*pthread_mutex_lock(&m_g);*/
	
	id = *(int*)_arg;
	
	sem_post(&sem);
	
	printf("I am %d!\n",id);
	
	/*pthread_mutex_unlock(&m_g);*/

	return NULL;

}


int main()
{
	pthread_t threads[THREADS_NUM];
	void* res;
	int stat;
	int i;
	
	sem_init(&sem,0,0);
	
	
	for(i=0 ; i < THREADS_NUM ; ++i)
	{
		if(0!= (stat = pthread_create(threads+i,NULL,threadFunc,&i)))
		{
			fprintf(stderr,"Thread create error #%d!\n",stat);
			exit(EXIT_FAILURE);
		}
		sem_wait(&sem);
		
	}
	
	
	for(i=0 ; i < THREADS_NUM ; ++i)
	{	
		pthread_join(threads[i],&res);

	}

	return 0;
}





