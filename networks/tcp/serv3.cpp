

#include <unistd.h> //close()
#include <arpa/inet.h> //socket() htons() inet_aton() bind() listen() accept() recv() send()
#include <poll.h> //poll()

#include <errno.h> //errno
#include <cstring> //strerror() strcmp()
#include <cstdlib> //exit()

#include <vector>
#include <string>
#include <iostream>
using std::cout;
using std::endl;


//const char* LOCAL_HOST_IP_ADRESS = "127.0.0.1";
//const unsigned short PORT = 50000;
const size_t BUFF_SIZE = 1024;
const char* const STOP_STRING = "SERVERSTOP";
const int BACKLOG = 10;
const size_t MAX_NUM_OF_CLIENTS = 1024;


int main(int argc, char* argv[])
{

	//TODO check arguments !
	
	std::vector<struct pollfd> fds;	
	
	struct pollfd temp_pollfd = {0};
	
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
	temp_pollfd.fd = socket(AF_INET, SOCK_STREAM, 0);
	temp_pollfd.events = 0 | POLLIN;
	
	if(-1 == temp_pollfd.fd)
	{
		cout<<strerror(errno);
		exit(EXIT_FAILURE);
	}else
	{
		cout<<"The fd of the server's socket is :"<<temp_pollfd.fd<<"\n";
	}
	
	fds.push_back(temp_pollfd);
		
	errno=0;
	res = bind(fds[0].fd, (const struct sockaddr *)&address, sizeof(address));
	if(-1 == res)
	{
		cout<<"bind error :"<<strerror(errno)<<"\n";
		close(fds[0].fd);
		exit(EXIT_FAILURE);
	}
	
	errno=0;
	res  = listen(fds[0].fd, BACKLOG);
	if(-1 == res)
	{
		cout<<"listen error :"<<strerror(errno)<<"\n";
		close(fds[0].fd);
		exit(EXIT_FAILURE);
	}
	
	char buffer[BUFF_SIZE] = {0};
	
	for(bool shouldRun=true; shouldRun ;)
	{	
		errno=0;
		res = poll(&fds[0], (nfds_t)fds.size(), -1/*inf wait*/);
		if(-1 == res)
		{
			cout<<"poll error :"<<strerror(errno)<<"\n";
			continue;//*TODO check ???
		}
		//TODO check error if(fds[0].revents & !POLLIN) exit! 

		if(fds[0].revents & POLLIN)
		{
			errno=0;
			temp_pollfd.fd = accept(fds[0].fd, 0, 0);
			
			if(-1 == temp_pollfd.fd)
			{
				cout<<"accept error :"<<strerror(errno)<<"\n";
			}else
			{
				temp_pollfd.events = 0 | POLLIN ;
				temp_pollfd.revents = 0;

				if(fds.size() >= MAX_NUM_OF_CLIENTS)
				{
					cout<<"too many clients\n"<<endl;
					close(temp_pollfd.fd);
					continue;
				}else
				{
					fds.push_back(temp_pollfd);
				}

				cout<<"new client accepted\n"<<endl;
			}
			fds[0].revents = 0;
		}
		size_t numOfClients = fds.size();
		for(size_t i=1; i < numOfClients ; ++i)
		{
			bool wasError = false;
			do 
			{
				if(fds[i].revents & POLLIN)
				{
					errno=0;
					ssize_t numOfBytes = recv(fds[i].fd, buffer, BUFF_SIZE, MSG_DONTWAIT);
		
					if(0 == numOfBytes || -1 == numOfBytes)
					{
						if(-1 == numOfBytes)
						{
							cout<<"receive error :"<<strerror(errno)<<"\n";
						}
						continue;
					}
				
					cout<<"received "<< numOfBytes <<"\n";
					cout<<"The message is :"<<string(buffer, buffer+numOfBytes)<<"\n";
			
					if(! strcmp(STOP_std::string, buffer))
					{
						shouldRun = false;
						continue;
					}
				
					errno =0;
					ssize_t numOfBytes2 = send(fds[i].fd, buffer, numOfBytes, 0);
					if(-1 == numOfBytes2)
					{
						cout<<"send error :"<<strerror(errno)<<"\n";
						continue;
					}else
					{
						cout<<"sent "<< numOfBytes2 <<"bytes \n"<<endl;
					}
				
					fds[0].revents = 0;
				
				}
			}while(false);
			//ERROR TREATING CODE
			/*else if((fds[i].revents & POLLERR) || (fds[i].revents & POLLHUP)
				|| (fds[i].revents & POLLNVAL)) //no need to check ???
			*/
			if(wasError)
			{
					close(fds[i].fd);
					fds.erase(fds.begin()+i);
					cout<<"client left\n";
			}
		}
	}
	
	for(int i=1; i<fds.size(); ++i)
	{
		close(fds[i].fd);
		cout<<"client "<< fds[i].fd<<" left\n";
	}
	close(fds[0].fd);
	cout<<"server "<< fds[0].fd<<" is closed"<<endl;
	
	exit(EXIT_SUCCESS);
}




