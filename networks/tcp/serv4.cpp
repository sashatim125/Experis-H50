

#include <unistd.h> //close()
#include <arpa/inet.h> //socket() htons() inet_aton() bind() listen() accept() recv() send()
#include <sys/epoll.h> //epoll API
#include <fcntl.h>//fcntl()

#include <errno.h> //errno
#include <cstring> //strerror() strcmp()
#include <cstdlib> //exit()

#include <vector>
#include <string>
#include <algorithm> //find()
#include <iostream>
using std::cout;
using std::endl;


#include <cstdio>//getchar()

//const char* LOCAL_HOST_IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const size_t BUFF_SIZE = 1024;
const char* const STOP_STRING = "SERVERSTOP";
const int BACKLOG = 10;
const size_t MAX_NUM_OF_CLIENTS = 2;
const size_t ERPPOLL_MAX_EVENTS = 10;


int main(int argc, char* argv[])
{

	//TODO check arguments !
	
	std::vector<int> fds;	
	int tempFD = -1;
	
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons((unsigned short)atoi(argv[2]));
	
	int res = inet_aton(argv[1],&address.sin_addr);
	if(! res)
	{
		cout<<"inet_aton error"<<"\n";
		exit(EXIT_FAILURE);
	}
	
	errno =0;
	tempFD = socket(AF_INET, SOCK_STREAM, 0);
	
	if(-1 == tempFD)
	{
		cout<<"socket error :"<<strerror(errno)<<"\n";
		exit(EXIT_FAILURE);
	}else
	{
		cout<<"The fd of the server's socket is :"<<tempFD<<"\n";
	}
	
	fds.push_back(tempFD);
		
	errno=0;
	res = bind(fds[0], (const struct sockaddr *)&address, sizeof(address));
	if(-1 == res)
	{
		cout<<"bind error :"<<strerror(errno)<<"\n";
		close(fds[0]);
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	res  = listen(fds[0], BACKLOG);
	if(-1 == res)
	{
		cout<<"listen error :"<<strerror(errno)<<"\n";
		close(fds[0]);
		exit(EXIT_FAILURE);
	}
	
	int epollFD = epoll_create(1/*unused*/);
	if(-1 == epollFD)
	{
		cout<<"epoll_create error :"<<strerror(errno)<<"\n";
		close(fds[0]);
		exit(EXIT_FAILURE);
	}
	struct epoll_event tempEvent = {0};
	tempEvent.data.fd = fds[0];
	tempEvent.events = 0|EPOLLIN|EPOLLRDHUP|EPOLLERR|EPOLLHUP;
	
	errno=0;
	res = epoll_ctl(epollFD, EPOLL_CTL_ADD, fds[0], &tempEvent);
	if(-1 == res)
	{
		cout<<"epoll_ctl error :"<<strerror(errno)<<"\n";
		close(fds[0]);
		exit(EXIT_FAILURE);
	}
	
	char buffer[BUFF_SIZE] = {0};
	struct epoll_event epollEvents[ERPPOLL_MAX_EVENTS] = {};
	
	//server socket set to non_bloking
	int flag = fcntl(fds[0], F_GETFL);
	if(-1 == fcntl(fds[0], F_SETFL, flag | O_NONBLOCK))
	{
		cout<<"fcntl error :"<<strerror(errno)<<"\n";
		close(fds[0]);
		close(epollFD);
		exit(EXIT_FAILURE);
	}
	
	
	for(bool shouldRun=true; shouldRun ;)
	{	
		errno=0;
		res = epoll_wait(epollFD, epollEvents, ERPPOLL_MAX_EVENTS, -1/*inf wait*/);
		if(-1 == res)
		{
			cout<<"epoll_wait error :"<<strerror(errno)<<"\n";
			getchar();
			continue;//TODO check ???
		}

		for(int i=0; i < res ; ++i)
		{
			if(epollEvents[i].data.fd == fds[0])
			{
				if (!(epollEvents[i].events & EPOLLIN))
				{
					cout<<"server event error "<<"\n";
					shouldRun = false;
					break;
				} else
				{
					errno=0;
					tempFD = accept(fds[0], 0, 0);
			
					if(-1 == tempFD)
					{
						cout<<"accept error :"<<strerror(errno)<<"\n";
					}else
					{
						if(fds.size()-1 > MAX_NUM_OF_CLIENTS)
						{
							cout<<"too many clients\n"<<endl;
							close(tempFD);
							continue;
						}
						
						tempEvent.data.fd = tempFD;
						tempEvent.events = 0|EPOLLIN|EPOLLRDHUP|EPOLLERR|EPOLLHUP;
						fds.push_back(tempFD);
						res = epoll_ctl(epollFD, EPOLL_CTL_ADD, tempFD, &tempEvent);
						cout<<"new client accepted\n"<<endl;
					}
				}
				continue;
			}
			bool wasError = false;
			do 
			{
				if(!(epollEvents[i].events & EPOLLIN))
				{
					wasError = true;
				}else
				{
					errno=0;
					ssize_t numOfBytes = recv(epollEvents[i].data.fd, buffer, BUFF_SIZE, MSG_DONTWAIT);
		
					if(0 == numOfBytes || -1 == numOfBytes)
					{
						if(-1 == numOfBytes)
						{
							cout<<"receive error :"<<strerror(errno)<<"\n";
						}
						wasError = true;
						continue;
					}
				
					cout<<"received "<< numOfBytes <<"\n";
					cout<<"The message is :"<<std::string(buffer, buffer+numOfBytes)<<"\n";
			
					if(! strcmp(STOP_STRING, buffer))
					{
						shouldRun = false;
						continue;
					}
				
					errno =0;
					ssize_t numOfBytes2 = send(epollEvents[i].data.fd, buffer, numOfBytes, 0);
					if(-1 == numOfBytes2)
					{
						cout<<"send error :"<<strerror(errno)<<"\n";
						wasError = true;
					}else
					{
						cout<<"sent "<< numOfBytes2 <<"bytes \n"<<endl;
					}
				}				
			}while(false);

			if(wasError)
			{
					close(epollEvents[i].data.fd);
					res = epoll_ctl(epollFD, EPOLL_CTL_DEL, epollEvents[i].data.fd, 0);
					
					std::vector<int>::iterator it = find(fds.begin(), fds.end(), epollEvents[i].data.fd);
					fds.erase(it);
					
					cout<<"client left\n";
			}
		}
	}
	
	close(epollFD);
	for(int i=1; i<fds.size(); ++i)
	{
		close(fds[i]);
		cout<<"client "<< fds[i]<<" left\n";
	}
	close(fds[0]);
	cout<<"server "<< fds[0]<<" is closed"<<endl;
	
	exit(EXIT_SUCCESS);
}




