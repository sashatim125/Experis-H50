

#include <unistd.h> //close()
#include <arpa/inet.h> //socket() htons() inet_aton() recv() send()

#include <errno.h> //errno
#include <cstring> //strerror() strcmp()
#include <cstdlib> //exit()

#include <iostream>
#include <string>

#include "chatcommon.h"

using std::cout;
using std::endl;


//const char* IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const char* const STOP_STRING = "STOP";
const size_t BUFF_SIZE = 1024;

#define ERROR_EXIT do{close(fd); exit(EXIT_FAILURE);}while(false)

int main(int argc, char* argv[])
{
//args check
	if(argc != 3)
	{
		cout<<"Parameters error !\n";
		cout<<"Usage : chatclient [IP] [port]\n"<<endl;
		exit(EXIT_FAILURE);
	}

//making connection to the server
	errno = 0;
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	
	if(-1 == fd)
	{
		std::cerr<<strerror(errno)<<endl;
		exit(EXIT_FAILURE);
	}else
	{
		std::cerr<<"The fd of the socket is :"<<fd<<"\n"<<endl;
	}
				
	struct sockaddr_in address = {0};
	address.sin_family = AF_INET;
	address.sin_port = htons((unsigned short)atoi(argv[2]));
	
	int res = inet_aton(argv[1],&address.sin_addr);
	if(! res)
	{
		std::cerr<<"IP address error"<<"\n"<<endl;
		ERROR_EXIT;
	}
	errno = 0;
	res = connect(fd,(const struct sockaddr *)&address, sizeof(address));
	if(res == -1)
	{
		std::cerr<<"connect error :"<<strerror(errno)<<"\n"<<endl;
		ERROR_EXIT;
	}

//sending request message	
	char buffer[BUFF_SIZE] = {};
	
	Message *message = (struct Message*)buffer;
//	message->m_type = CLIENT_CONNECT_REQUEST;
//	message->m_size = 0;
	

//getting approval message
	errno=0;
	ssize_t numOfBytes = recv(fd, message, sizeof(struct Message), 0);
	if(-1 == numOfBytes)
	{
		std::cerr<<"connect acception error :"<<strerror(errno)<<"\n"<<endl;
		ERROR_EXIT;
	}
	if(CLIENT_CONNECT_ACCEPTED == message->m_type)
	{
		cout<<"Your connection was accepted !\n";
		cout<<"Welcome to the chat !\n"<<endl;
	}else if(CLIENT_CONNECT_REFUSED == message->m_type)
	{
		cout<<"Sorry, your connection was refused ...\n";
		cout<<"Try later ...\n"<<endl;
		ERROR_EXIT;
	}else
	{
		std::cerr<<"Server reply error !\n"<<endl;
		ERROR_EXIT;
	}
	
	
	for(;;)
	{
		fd_set rfds;
		FD_ZERO(&rfds);
		FD_SET(0, &rfds);
		FD_SET(fd, &rfds);
	
		cout<<"Enter the message :"<<endl;
		
		errno=0;
		res = select(fd+1, &rfds, 0, 0, 0);
		if(-1 == res)
		{
			std::cerr<<"select error :"<<strerror(errno)<<"\n"<<endl;
			ERROR_EXIT;
		}
		
		std::string str;
		//message from the keyboard
		if(FD_ISSET(0, &rfds))
		{
			std::getline(std::cin, str);
			
			if( !strcmp(str.c_str(), STOP_STRING))
			{	
				break;
			}
			
			message->m_type = CLIENT_MESSAGE;
			message->m_size = str.size();
			memcpy(message->m_buff, str.c_str(), str.size());
			
			numOfBytes = send(fd, message, sizeof(struct Message)+message->m_size-1, MSG_NOSIGNAL);
			if(-1 == numOfBytes)
			{
				std::cerr<<"sending message to the server error :"<<strerror(errno)<<"\n"<<endl;
				ERROR_EXIT;
			}
			continue;
		}
		//message from the server
		errno=0;
		numOfBytes = recv(fd,message, BUFF_SIZE, 0);
		if(-1 == numOfBytes || 0 == numOfBytes)
		{
			if(-1 == numOfBytes)
			{
				std::cerr<<"recv error :"<<strerror(errno)<<"\n"<<endl;
			}
			break;
		}
		message->m_buff[message->m_size] = '\0';
		cout<<"Message from server : "<<message->m_buff<<"\n"<<endl;
	}	
	
	//end of the session
	cout<<"Goodbye !!!\n"<<endl;
	close(fd);
	exit(EXIT_SUCCESS);
}




