
//INADDR_ANY !!!!!!!!


#define _ORIGINAL_SOURCE
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

#include <iostream>
using std::cout;
using std::endl;

//const char* LOCAL_HOST_IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const size_t BUFF_SIZE = 1024;
const char* const STOP_STRING = "SERVERSTOP";


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
	
	char buffer[BUFF_SIZE] = {0};
	
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons(atoi(argv[2]));
	
	int ret = inet_aton(argv[1],&address.sin_addr);
	if(! ret)
	{
		cout<<"inet_aton errro"<<"\n";
	}
		
	int res1 = bind(fd, (const struct sockaddr *)&address, sizeof(address));
	if(-1 == res1)
	{
		perror("bind error\n");
	}
	
	for(bool shouldRun=true; shouldRun;)
	{	
		struct sockaddr_in addressFrom = {0};
		size_t sockAddrSize = sizeof(addressFrom);
	
		ssize_t numOfBytes = recvfrom(fd, buffer, BUFF_SIZE, 0,
			(struct sockaddr *) &addressFrom, (socklen_t*) &sockAddrSize);
		cout<<"received "<< numOfBytes <<"\n";
		cout<<"The message is :"<<buffer<<"\n";
		cout<<inet_ntoa(addressFrom.sin_addr)<<"\n";
		cout<<ntohs(addressFrom.sin_port)<<endl;
	
		if(! strcmp(STOP_STRING, buffer))
		{
			shouldRun = false;
		}
				
		strcat(buffer," :) !!! :)\n");
		ssize_t numOfBytes2 = sendto(fd, buffer, strlen(buffer)+1, 0,
			(const struct sockaddr *) &addressFrom, sizeof(addressFrom));
		cout<<"sent "<< numOfBytes2 <<"\n"<<endl;

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




