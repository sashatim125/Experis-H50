

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <stdio.h> 
#include <string.h>

struct msgbuf
{
	long mtype;       /* message type, must be > 0 */
	char mtext[1];    /* message data */
}; 
 

 
int main()
{
	int mid;
	key_t key;
	struct msgbuf *msgBuff;
	
	char buffer[1024];
	
	if(0 > (key = ftok("myfile",5)))
	{
		perror(""); 
	}
	
	if(0 > (mid = msgget(key,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
	}
	
	msgBuff = (struct msgbuf*)buffer;

	
	if(0 >= msgrcv(mid,buffer,100,-4,MSG_NOERROR))
	{
		perror("");
	}
	printf("%s",msgBuff->mtext);


	return 0;
}

