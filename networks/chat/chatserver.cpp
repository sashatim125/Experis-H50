

#include <unistd.h> //close()
#include <arpa/inet.h> //socket() htons() inet_aton() bind() listen() accept() recv() send()
#include <sys/epoll.h> //epoll API
#include <fcntl.h>//fcntl()

#include <errno.h> //errno
#include <cstring> //strerror() strcmp()
#include <cstdlib> //exit()

#include <vector>
#include <string>
#include <iostream>

#include "chatcommon.h"

using std::cout;
using std::endl;


#include <cstdio>//getchar()

//const char* LOCAL_HOST_IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;

const std::string STOP_STRING = "SERVERSTOP";
const size_t BUFF_SIZE = 1024;
const int BACKLOG = 10;
const size_t MAX_NUM_OF_CLIENTS = 2;
const size_t ERPPOLL_MAX_EVENTS = 10;

struct Client
{
	int m_fd;
	std::string m_name;//IP
};

bool SendToClient(Client& _client, Message& _message)
{
	errno=0;
	ssize_t numOfBytes = send(_client.m_fd, &_message, sizeof(struct Message)+_message.m_size, MSG_DONTWAIT|MSG_NOSIGNAL);
	if(-1 == numOfBytes)
	{
		std::cerr<<"send to client "<< _client.m_name <<" error: "<<strerror(errno)<<"\n"<<endl;
		return false;
	}
	return true;
}


int main(int argc, char* argv[])
{

//args check
	if(argc != 3)
	{
		cout<<"Parameters error !\n";
		cout<<"Usage : chatserver [IP] [port]\n"<<endl;
		exit(EXIT_FAILURE);
	}

	std::vector<Client> fds;
//	fds.reserve(MAX_NUM_OF_CLIENTS+1);
	Client tempClient = {-1,argv[1]};

//initiating socket	
	
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons((unsigned short)atoi(argv[2]));
	
	int res = inet_aton(argv[1],&address.sin_addr);
	if(! res)
	{
		std::cerr<<"inet_aton error"<<"\n"<<endl;
		exit(EXIT_FAILURE);
	}
	
	errno =0;
	tempClient.m_fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(-1 == tempClient.m_fd)
	{
		std::cerr<<"socket error :"<<strerror(errno)<<"\n"<<endl;
		exit(EXIT_FAILURE);
	}else
	{
		std::cerr<<"The fd of the server's socket is :"<<tempClient.m_fd<<"\n"<<endl;
	}
	
	fds.push_back(tempClient);
		
	errno=0;
	res = bind(fds[0].m_fd, (const struct sockaddr *)&address, sizeof(address));
	if(-1 == res)
	{
		std::cerr<<"bind error :"<<strerror(errno)<<"\n"<<endl;
		close(fds[0].m_fd);
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	res  = listen(fds[0].m_fd, BACKLOG);
	if(-1 == res)
	{
		std::cerr<<"listen error :"<<strerror(errno)<<"\n"<<endl;
		close(fds[0].m_fd);
		exit(EXIT_FAILURE);
	}
	
	int epollFD = epoll_create(1/*unused*/);
	if(-1 == epollFD)
	{
		std::cerr<<"epoll_create error :"<<strerror(errno)<<"\n"<<endl;
		close(fds[0].m_fd);
		exit(EXIT_FAILURE);
	}
	struct epoll_event tempEvent = {0};
	tempEvent.data.fd = fds[0].m_fd;
	tempEvent.events = 0|EPOLLIN|EPOLLRDHUP|EPOLLERR|EPOLLHUP;
	
	errno=0;
	res = epoll_ctl(epollFD, EPOLL_CTL_ADD, fds[0].m_fd, &tempEvent);
	if(-1 == res)
	{
		std::cerr<<"epoll_ctl error :"<<strerror(errno)<<"\n"<<endl;
		close(fds[0].m_fd);
		close(epollFD);
		exit(EXIT_FAILURE);
	}
	
	char buffer[BUFF_SIZE] = {0};
	Message *message = (struct Message*)buffer;
	
	struct epoll_event epollEvents[ERPPOLL_MAX_EVENTS] = {};
	
	//server socket set to non_bloking
	int flag = fcntl(fds[0].m_fd, F_GETFL);
	if(-1 == fcntl(fds[0].m_fd, F_SETFL, flag | O_NONBLOCK))
	{
		std::cerr<<"fcntl error :"<<strerror(errno)<<"\n"<<endl;
		close(fds[0].m_fd);
		close(epollFD);
		exit(EXIT_FAILURE);
	}
	
	for(bool shouldRun=true; shouldRun ;)
	{	
		errno=0;
		res = epoll_wait(epollFD, epollEvents, ERPPOLL_MAX_EVENTS, -1/*inf wait*/);
		if(-1 == res)
		{
			std::cerr<<"epoll_wait error :"<<strerror(errno)<<"\n"<<endl;
			shouldRun = false;
			getchar();
			continue;
		}

		for(int i=0; i < res ; ++i)
		{
			//connection request
			if(epollEvents[i].data.fd == fds[0].m_fd)
			{
				if (!(epollEvents[i].events & EPOLLIN))
				{
					std::cerr<<"server event error "<<"\n"<<endl;
					shouldRun = false;
					break;
				} else
				{
					errno=0;
					size_t addrSize = sizeof(address);
					tempClient.m_fd = accept(fds[0].m_fd, (struct sockaddr*)&address, (socklen_t*)&addrSize);
			
					if(-1 == tempClient.m_fd)
					{
						std::cerr<<"accept error :"<<strerror(errno)<<"\n"<<endl;
					}else
					{//too many clients					
						if(fds.size()-1 == MAX_NUM_OF_CLIENTS)
						{
							std::cerr<<"too many clients\n"<<endl;
							
							message->m_type = CLIENT_CONNECT_REFUSED;
							message->m_size = 0;
							
							errno=0;
							SendToClient(tempClient, *message);
							close(tempClient.m_fd);
							continue;
						}
						//accept the client
						tempClient.m_name = std::string(inet_ntoa(address.sin_addr));
						fds.push_back(tempClient);
						
						tempEvent.data.fd = tempClient.m_fd;
						tempEvent.events = 0|EPOLLIN|EPOLLRDHUP|EPOLLERR|EPOLLHUP;
						res = epoll_ctl(epollFD, EPOLL_CTL_ADD, tempClient.m_fd, &tempEvent);
						if(-1 == res)
						{
							std::cerr<<"epoll_ctl error :"<<strerror(errno)<<"\n"<<endl;
							shouldRun = false;
							break;
						}
						
						message->m_type = CLIENT_CONNECT_ACCEPTED;
						message->m_size = 0;
						
						errno=0;
						if(! SendToClient(tempClient, *message))
						{
							fds.pop_back();
							close(tempClient.m_fd);
							continue;
						}
						
						std::string msg = tempClient.m_name + " new client joined\n";
						cout<<msg<<endl;
						message->m_type = SERVER_MESSAGE;
						message->m_size = msg.size();
						memcpy(message->m_buff, msg.c_str(), msg.size());
						for(size_t j=1; j<fds.size(); ++j)
						{
							SendToClient(fds[j], *message);
						}

					}
				}
				continue;
			}
			//get message from a client and multicast it
			bool wasError = false;
			do 
			{
				if(!(epollEvents[i].events & EPOLLIN))
				{
					wasError = true;
				}else
				{
					errno=0;
					ssize_t numOfBytes = recv(epollEvents[i].data.fd, message, BUFF_SIZE, MSG_DONTWAIT);
		
					if(0 == numOfBytes || -1 == numOfBytes)
					{
						if(-1 == numOfBytes)
						{
							std::cerr<<"receive error :"<<strerror(errno)<<"\n"<<endl;
						}
						wasError = true;
						continue;
					}
					
					if(STOP_STRING == std::string(message->m_buff, message->m_size))
					{
						shouldRun = false;
						continue;
					}
					
					std::vector<Client>::iterator it = fds.begin() ;
					for(; it != fds.end() && it->m_fd != epollEvents[i].data.fd ; ++it)
					{}
				
					std::string msg = it->m_name + std::string(message->m_buff, message->m_buff+message->m_size);
				
					cout<<msg<<endl;
					message->m_type = SERVER_MESSAGE;
					message->m_size = msg.size();
					memcpy(message->m_buff, msg.c_str(), msg.size());
					for(size_t j=1; j<fds.size(); ++j)
					{
						SendToClient(fds[j], *message);
					}

				}				
			}while(false);

			if(wasError)
			{
				close(epollEvents[i].data.fd);
				res = epoll_ctl(epollFD, EPOLL_CTL_DEL, epollEvents[i].data.fd, 0);
				
				std::vector<Client>::iterator it = fds.begin() ;
				for(; it != fds.end() && it->m_fd != epollEvents[i].data.fd ; ++it)
				{}
				std::string msg = it->m_name + " client left\n";
				
				fds.erase(it);
				
				cout << msg<<endl;
				message->m_type = SERVER_MESSAGE;
				message->m_size = msg.size();
				memcpy(message->m_buff, msg.c_str(), msg.size());
				for(size_t j=1; j<fds.size(); ++j)
				{
					SendToClient(fds[j], *message);
				}
			}
		}
	}

//disconnect all clients
	close(epollFD);
	for(int i=1; i<fds.size(); ++i)
	{
		std::string msg = "Server is going offline.\n";
		message->m_type = SERVER_MESSAGE;
		message->m_size = msg.size();
		memcpy(message->m_buff, msg.c_str(), msg.size());
		SendToClient(fds[i], *message);
		
		close(fds[i].m_fd);
		cout<<"client "<< fds[i].m_name<<" left\n"<<endl;
	}
	close(fds[0].m_fd);
	cout<<"server "<< fds[0].m_name<<" is closed"<<endl;
	
	exit(EXIT_SUCCESS);
}




