
#include <unistd.h>
#include <stdio.h>









int main()
{
	pid_t pid;
	
	int pipefd[2];
	int pipefd2[2];
	
	char str[]  = "a good string from parent...\n";
	char str2[] = "a good string from child ...\n";
	char buff[100];
	
	if(0!= pipe(pipefd))
	{
		perror("Pipe error!\n");
	}
	
	if(0!= pipe(pipefd2))
	{
		perror("Pipe error!\n");
	}
	
	if (fork())
	{
		close(pipefd[0]);
		close(pipefd2[1]);
	
		printf("I am the parent and writing to the pipe\n");
		write(pipefd[1],str,29);
		
		printf("I am the parent and reading from the pipe\n");
		
		read(pipefd2[0],buff,29);
		write(1,buff,29);
	}else
	{
		close(pipefd[1]);
		close(pipefd2[0]);
	
		printf("I am the child and reading from the pipe\n");
		read(pipefd[0],buff,29);
		write(1,buff,29);
		
		printf("I am the child and writing to the pipe\n");
		write(pipefd2[1],str2,29);
	}

	return 0;
}



















