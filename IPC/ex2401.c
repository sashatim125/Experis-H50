

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>

       
static void parent(pid_t _chldPID)
{
	printf("Hi !\nI'm %d (parent) and I am goint to sleep for 5 sec.\n",getpid());	
	
	sleep(5);
	
	printf("Hi !\nI'm %d (parent) and I am sending signal %d to %d (child)\n",getpid(),SIGUSR1,_chldPID);
	kill(_chldPID,SIGUSR1);
	
	printf("Hi !\nI'm %d (parent) and I am going to sleep for 200 sec.\n",getpid());
	sleep(200);
}

static void sayHi(int _sig, siginfo_t *_sinfo, void *_cont)
{
	char str[]="\nHi , I am signal handler; accepted signal and sending it back.\n";
	
	write(2,str,strlen(str));
	/*
	printf("\nHi , accepted signal %d from %d\n",_sig, _sinfo->si_pid);
	printf("and sending it back.\n");
	*/
	kill(_sinfo->si_pid, SIGUSR2);
}

static void child(void)
{
	struct sigaction sigIgnore={0};
	
	sigIgnore.sa_sigaction = sayHi;
	sigIgnore.sa_flags |=SA_SIGINFO;
	sigaction(SIGUSR1,&sigIgnore,NULL);
		
	printf("I am %d (child) and I am going to sleep for 20 sec.\n",getpid());
	sleep(20);
}

static void doFork(void)
{
	int i;
	pid_t thePID;

	thePID = fork();
	
	if(0 != thePID)
	{	
		parent(thePID);
	}
	else
	{
		child();	
	}

}


int main()
{
	doFork();
	
	return 0;
}



