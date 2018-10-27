
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>


int main()
{
	int shmid;
	char *shmemptr;
	key_t key;
	
	if(0 > (key = ftok("something",5)))
	{
		perror("ftok err");
		return -1;
	}
	
	if (-1 == (shmid = shmget(key,1024,IPC_CREAT|0644)))
	{
		perror("shmget err");
	}

	if(NULL==(shmemptr = shmat(shmid,NULL,0)))
	{
		perror("shmat");
	}
	
	sprintf(shmemptr,"Hello World !I am at %p\n",shmemptr);
	
	shmdt(shmemptr);





	return 0;
}
