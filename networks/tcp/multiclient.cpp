

//MAN 2 SOCKET !!!!!!!!!!!
//MAN 2 CLOSE !!!!!!!!!!!!!!
//MAN 7 IP !!!!!!!!!!!!!

#define _ORIGINAL_SOURCE
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::vector;

//const char* IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const size_t BUFF_SIZE = 1024;

const int CONNECT_PERSENT = 30;
const int DISCONNECT_PERCENT = 5;
const int SEND_PERSENT = 30;

bool ConnectClient(int* _fd, const char* _ip, const char* _port)
{
	errno = 0;
	*_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(-1 == *_fd)
	{
		cout<<strerror(errno);
		return false;
	}else
	{
		cout<<"The fd of the socket is :"<<*_fd<<"\n";
	}
				
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons((unsigned short)atoi(_port));
	
	int res = inet_aton(_ip,&address.sin_addr);
	if(! res)
	{
		cout<<"inet_aton error"<<"\n";
		close(*_fd);
		*_fd = -1;
		return false;
	}
	
	res = connect(*_fd,(const struct sockaddr *)&address, sizeof(address));
	if(res == -1)
	{
		cout<<"connect error :"<<strerror(errno)<<"\n";
		close(*_fd);
		*_fd = -1;
		return false;
	}
	return true;
}

bool SendRecvFromClient(int _fd)	
{		
	char buffer[BUFF_SIZE] = {0};

	sprintf(buffer,"Message from %d !",_fd);

	errno=0;
	ssize_t numOfBytes = send(_fd, buffer, strlen(buffer)+1, MSG_NOSIGNAL);
	if(-1 == numOfBytes)
	{
		cout<<"send error :"<<strerror(errno)<<"\n";
		return false;
	}
		
	cout<<"sent "<< numOfBytes <<"\n";

	errno=0;
	numOfBytes = recv(_fd, buffer, BUFF_SIZE, 0);
	if(-1 == numOfBytes)
	{
		cout<<"recv error :"<<strerror(errno)<<"\n";
		return false;
	}
	cout<<"received "<< numOfBytes <<"bytes\n";
	cout<<"The message is :"<<buffer<<"\n";
	
	return true;
}

bool CloseClient(int *_fd)
{
	errno = 0;
	int res = close(*_fd);
	if(0 != res)
	{
		cout<<"close error :"<<strerror(errno)<<"\n";
		*_fd = -1;
		return false;
	}
	*_fd = -1;

	return true;
}


void MultiClient(const char* _ip, const char* _port, size_t _numOfClients =10)
{
	vector<int> clients(_numOfClients, -1);
	
	srand (time(0));
	
	for(;;)
	{
		for(size_t i=0; i < clients.size(); ++i)
		{
			int randNum = rand()%100 +1;
			if(-1 == clients[i])
			{
				if(randNum <= CONNECT_PERSENT)
				{
					ConnectClient(&clients[i], _ip, _port);
				}
				continue;
			}
			
			if(randNum <= SEND_PERSENT)
			{
				SendRecvFromClient(clients[i]);
			}else if(randNum <= SEND_PERSENT+DISCONNECT_PERCENT)
			{
				CloseClient(&clients[i]);
			}
		}
	}
}
	
void Ignore(int _sig)
{
	int k;
	
	std::cout<<"\n\n\n\n\n";
	std::cout<<"signal "<<_sig<<" received.\n";
	std::cout<<"\n\n\n\n\n";
	
	std::cin>>k;
}	


int main(int argc, char* argv[])
{
	if(argc < 3)
	{
		cout<<"Too few parameters !\n";
		return -1;
	}
	struct sigaction sa={};
	sa.sa_handler = Ignore;
	int res = sigaction(SIGPIPE,&sa,0);
	
	if(argc == 3)
	{
		MultiClient(argv[1], argv[2]);
	}else
	{
		MultiClient(argv[1], argv[2], atoi(argv[3]));
	}

	return 0;
}

































