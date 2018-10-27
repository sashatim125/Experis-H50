

//#define _ORIGINAL_SOURCE
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <errno.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <fcntl.h>


#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;
using std::string;

//const char* LOCAL_HOST_IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const size_t BUFF_SIZE = 1024;
const char* const STOP_STRING = "SERVERSTOP";
const int BACKLOG = 10;


int main(int argc, char* argv[])
{
	std::vector<int> fds;	
	
	errno =0;
	fds.push_back(socket(AF_INET, SOCK_STREAM, 0));
	
	if(-1 == fds[0])
	{
		cout<<strerror(errno);
		exit(EXIT_FAILURE);
	}else
	{
		cout<<"The fd of the server's socket is :"<<fds[0]<<"\n";
	}
	
	char buffer[BUFF_SIZE] = {0};
	
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons((unsigned short)atoi(argv[2]));
	
	int res = inet_aton(argv[1],&address.sin_addr);
	if(! res)
	{
		cout<<"inet_aton error"<<"\n";
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	res = bind(fds[0], (const struct sockaddr *)&address, sizeof(address));
	if(-1 == res)
	{
		perror("bind error\n");
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	res  = listen(fds[0], BACKLOG);
	if(-1 == res)
	{
		cout<<"listen error :"<<strerror(errno)<<"\n";
		exit(EXIT_FAILURE);
	}
	
	fd_set rfds;
	FD_ZERO(&rfds);
	int maxfd =fds[0];
	FD_SET(fds[0], &rfds);

	for(bool shouldRun=true; shouldRun ;)
	{
		fd_set rfds_temp = rfds;
		
		errno=0;
		res = select(maxfd+1, &rfds_temp, 0, 0, 0);
		if(-1 == res)
		{
			cout<<"select error :"<<strerror(errno)<<"\n";
			break;
		}
	
		bool wasNewClient = false;	
		if(FD_ISSET(fds[0], &rfds_temp))
		{
			errno=0;
			fds.push_back(accept(fds[0], 0, 0));
			if(-1 == fds.back())
			{
				cout<<"accept error :"<<strerror(errno)<<"\n";
				fds.pop_back();
			}else
			{
				FD_SET(fds.back(), &rfds);
				if(fds.back() > maxfd)
				{
					maxfd = fds.back();
				}
				wasNewClient = true;
				cout<<"new client accepted\n"<<endl;
			}
		}
		
		size_t numOfClients = wasNewClient ? fds.size()-1 : fds.size();
		for(int i=1; i < numOfClients ; ++i)
		{
			if(FD_ISSET(fds[i], &rfds_temp))
			{
				errno=0;
				ssize_t numOfBytes = recv(fds[i], buffer, BUFF_SIZE, MSG_DONTWAIT);
		
				if(-1 == numOfBytes)
				{
					cout<<"receive error :"<<strerror(errno)<<"\n";
				}
				if(0 == numOfBytes || -1 == numOfBytes)
				{
					if(fds[i] == maxfd)
					{
						maxfd = 0;
						for(int j=0; j < fds.size(); ++j)
						{
							if(fds[j] > maxfd)
							{
								maxfd = fds[j];
							}
						}
					}
					close(fds[i]);
					FD_CLR(fds[i],&rfds);
					fds.erase(fds.begin()+i);
					cout<<"client left\n";
					continue;
				}
				
				cout<<"received "<< numOfBytes <<"\n";
				cout<<"The message is :"<<string(buffer, buffer+numOfBytes)<<"\n";
			
				if(! strcmp(STOP_STRING, buffer))
				{
					shouldRun = false;
					continue;
				}
				
				errno =0;
				ssize_t numOfBytes2 = send(fds[i], buffer, numOfBytes, 0);
				if(-1 == numOfBytes2)
				{
					cout<<"send error :"<<strerror(errno)<<"\n";
				}else
				{
					cout<<"sent "<< numOfBytes2 <<"bytes \n"<<endl;
				}
			}
		}
	}
	
	for(int i=0; i<fds.size(); ++i)
	{
		close(fds[i]);
	}

	return 0;
}




