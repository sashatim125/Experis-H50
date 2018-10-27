
#include <sys/ipc.h>
#include <sys/shm.h>

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int shmid = atoi(argv[1]);
	char *shmemptr;

	shmemptr = shmat(shmid,NULL,0);
	
	printf("%s",shmemptr);
	
	shmdt(shmemptr);


	return 0;
}
