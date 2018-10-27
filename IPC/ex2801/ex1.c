

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
	
	if(0 > (mid = msgget(key,IPC_CREAT|S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)))
	{
		perror("");
	}

	msgBuff = (struct msgbuf*)buffer;
	
	msgBuff->mtype = 1;
	
	strcpy(msgBuff->mtext,"Hello 1!!!\n");
	
	if(0 != msgsnd(mid,msgBuff,strlen(msgBuff->mtext)+1,0))
	{
		perror("");
	}
	
	strcpy(msgBuff->mtext,"Hello 2!!!\n");
	
	if(0 != msgsnd(mid,msgBuff,strlen(msgBuff->mtext)+1,0))
	{
		perror("");
	}



	return 0;
}

