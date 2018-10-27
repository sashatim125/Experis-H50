


 #include <pthread.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <unistd.h>




void *foo(void* _ard)
{
	sleep(2);
	
	printf("I am foo!\n");

	return NULL;

}


int main()
{
	pthread_t thread;
	void* res;
	int stat;

	if(0!= (stat = pthread_create(&thread,NULL,foo,NULL)))
	{
		fprintf(stderr,"Thread create error !\n");
		exit(EXIT_FAILURE);
	}

	pthread_join(thread,&res);

	return 0;
}





