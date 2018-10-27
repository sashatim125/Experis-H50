

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
	int fd = socket(AF_INET, SOCK_DGRAM, 0);
	
	if(-1 == fd)
	{
		cout<<strerror(errno);
	}else
	{
		cout<<"The fd of the socket is :"<<fd<<"\n";
	}
				
		struct sockaddr_in address = {0};
		address.sin_family = AF_INET;
		address.sin_port = htons(atoi(argv[2]));
	
		int ret = inet_aton(argv[1],&address.sin_addr);
		if(! ret)
		{
			cout<<"inet_aton error"<<"\n";
		}
	
		int ret1 = connect(fd,(const struct sockaddr *)&address, sizeof(address));
		if(ret1 == -1)
		{
			cout<<"connect error"<<"\n";
			perror("");
		}
	
	int fds[2];
	fds[0] = 0;
	fds[1] = fd;
	
	fd_set rfds;
	
	bool canRun =true;
	for(;canRun;)
	{
		char buffer[BUFF_SIZE] = {0};
	
		FD_ZERO(&rfds);
		int maxfd =-1;
		for(int i=0; i < 2; ++i)
		{
			FD_SET(fds[i], &rfds);
			if(fds[i] > maxfd)
			{
				maxfd = fds[i];
			}
		}
		
		int retval = select(maxfd+1, &rfds, 0,0,0);
		for(int i=0; i<2; ++i)
		{
			if(FD_ISSET(fds[i], &rfds))
			{
				if (fds[i] == 0)
				{
					fgets(buffer, BUFF_SIZE-1, stdin);
					if( !strcmp(buffer, STOP_STRING))
					{
						break;
					}
					ssize_t numOfBytes = send(fd, buffer, strlen(buffer)+1, 0);
					cout<<"sent "<< numOfBytes <<"bytes\n";
				}else if(fds[i] == fd)
				{
					struct sockaddr_in addressFrom = {0};
					size_t sockAddrSize = sizeof(addressFrom);
	
					ssize_t numOfBytes = recvfrom(fd, buffer, BUFF_SIZE, 0,
						(struct sockaddr *) &addressFrom, (socklen_t*) &sockAddrSize);
					cout<<"received "<< numOfBytes <<"\n";
					cout<<"The message is :"<<buffer<<"\n";
					cout<<inet_ntoa(addressFrom.sin_addr)<<"\n";
					cout<<ntohs(addressFrom.sin_port)<<endl;
				}else
				{
					canRun = false;				
				}
			}
		}
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




