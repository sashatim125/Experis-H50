

//MAN 2 SOCKET !!!!!!!!!!!
//MAN 2 CLOSE !!!!!!!!!!!!!!
//MAN 7 IP !!!!!!!!!!!!!

#define _ORIGINAL_SOURCE
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>
using std::cout;
using std::endl;

//const char* IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const size_t BUFF_SIZE = 1024;
const char* const STOP_STRING = "STOP";


int main(int argc, char* argv[])
{
	errno = 0;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(-1 == fd)
	{
		cout<<strerror(errno);
		exit(EXIT_FAILURE);
	}else
	{
		cout<<"The fd of the socket is :"<<fd<<"\n";
	}
	
	bool canRun = true;
				
		struct sockaddr_in address = {0};
		address.sin_family = AF_INET;
		address.sin_port = htons((unsigned short)atoi(argv[2]));
	
		int ret = inet_aton(argv[1],&address.sin_addr);
		if(! ret)
		{
			cout<<"inet_aton error"<<"\n";
			canRun = false;
		}
	
		int ret1 = connect(fd,(const struct sockaddr *)&address, sizeof(address));
		if(ret1 == -1)
		{
			cout<<"connect error :"<<strerror(errno)<<"\n";
			canRun = false;
		}
	
	for(;canRun ;)
	{	
		char buffer[BUFF_SIZE] = {0};
		cout<<"Enter the message :";
		std::cin>>buffer;
		
		if( !strcmp(buffer, STOP_STRING))
		{
			break;
		}
		ssize_t numOfBytes = send(fd, buffer, strlen(buffer)+1, 0);
	
	/*	
		ssize_t numOfBytes = sendto(fd, buffer, strlen(buffer)+1, 0,
			(const struct sockaddr *) &address, sizeof(address));
	*/		
		cout<<"sent "<< numOfBytes <<"\n";
	
		ssize_t numOfBytes2 = recv(fd, buffer, BUFF_SIZE, 0);
		cout<<"received "<< numOfBytes2 <<"\n";
		cout<<"The message is :"<<buffer<<"\n";
	}	
	
	errno = 0;
	int res = close(fd);
	if(0 != res)
	{
		cout<<"Error :"<<errno<<"\n";
		perror("");
	}else
	{
		cout<<"The res of the socket closing is :"<<res<<"\n";
	}

	return 0;
}




