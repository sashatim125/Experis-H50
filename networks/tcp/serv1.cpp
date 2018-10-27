
//INADDR_ANY !!!!!!!!


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
#include <fcntl.h>

#include <iostream>
using std::cout;
using std::endl;

//const char* LOCAL_HOST_IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const size_t BUFF_SIZE = 1024;
const char* const STOP_STRING = "SERVERSTOPSTOPSTOP";
const int BACKLOG = 0;


void PrintFDOptions(int _fd)
{
	int options;
	socklen_t len = sizeof(options);

	int res = getsockopt(_fd, SOL_SOCKET,SO_DOMAIN, &options, &len);
	if(-1 == res)
	{
		cout<<strerror(errno);
		exit(EXIT_FAILURE);
	}
	cout<<"FD = "<<_fd<<"\n";
	cout<<"Domain is :"<<options;
	if(options&AF_LOCAL)
	{
		cout << "Local";
	}else if(options&AF_INET)
	{
		cout << "inet";
	}else
	{
		cout<< "unknown";
	}
	cout<<std::endl;
	
	res = getsockopt(_fd, SOL_SOCKET,SO_TYPE, &options, &len);
	if(-1 == res)
	{
		cout<<strerror(errno);
		exit(EXIT_FAILURE);
	}	
	
	cout<<"type :"<<options;
	if(options&SOCK_STREAM)
	{
		cout << "tcp";
	}else if(options&SOCK_DGRAM)
	{
		cout << "udp";
	}else
	{
		cout<< "unknown";
	}
	cout<<std::endl;
}



int main(int argc, char* argv[])
{
	
	errno =0;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(-1 == fd)
	{
		cout<<strerror(errno);
		exit(EXIT_FAILURE);
	}else
	{
		cout<<"The fd of the socket is :"<<fd<<"\n";
	}
	
	char buffer[BUFF_SIZE] = {0};
	
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons((unsigned short)atoi(argv[2]));
	
	int res = inet_aton(argv[1],&address.sin_addr);
	if(! res)
	{
		cout<<"inet_aton errro"<<"\n";
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	res = bind(fd, (const struct sockaddr *)&address, sizeof(address));
	if(-1 == res)
	{
		perror("bind error\n");
		exit(EXIT_FAILURE);
	}
	
	PrintFDOptions(fd);
	
	errno=0;
	res  = listen(fd, BACKLOG);
	if(-1 == res)
	{
		perror("listen error\n");
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	int client_fd = accept(fd, 0, 0);
	if(-1 == res)
	{
		perror("accept error\n");
		exit(EXIT_FAILURE);
	}	

	cout<<"\n\n"<<std::endl;
	PrintFDOptions(client_fd);

	int flag = fcntl(client_fd, F_GETFL);
	if(-1 == fcntl(client_fd, F_SETFL, flag | O_NONBLOCK))
	{
		perror("fcntl error\n");
		exit(EXIT_FAILURE);
	}
	
	for(bool shouldRun=true; shouldRun;)
	{	
	
		ssize_t numOfBytes = recv(client_fd, buffer, BUFF_SIZE, 0/*|MSG_DONTWAIT*/);
		
		if(-1 == numOfBytes)
		{
			if(EWOULDBLOCK == errno)
			{
				sleep(1);
				cout<<".";
				flush(cout);
				continue;
			}
		}else
		if(0 == numOfBytes)
		{
			break;
		}
		
		
		cout<<"received "<< numOfBytes <<"\n";
		cout<<"The message is :"<<buffer<<"\n";
			
		if(! strcmp(STOP_STRING, buffer))
		{
			shouldRun = false;
		}
				
		strcat(buffer," :) !!! :)\n");
		ssize_t numOfBytes2 = send(client_fd, buffer, strlen(buffer)+1, 0);
		cout<<"sent "<< numOfBytes2 <<"\n"<<endl;

	}
	
	close(client_fd);
	
	errno = 0;
	res = close(fd);
	if(0 != res)
	{
		cout<<"Error :"<<errno<<"\n";
		perror("");
		exit(EXIT_FAILURE);
	}else
	{
		cout<<"The res of the socket closing is :"<<res<<"\n";
	}
	

	

	return 0;
}




