

//MAN 2 SOCKET !!!!!!!!!!!
//MAN 2 CLOSE !!!!!!!!!!!!!!
//MAN 7 IP !!!!!!!!!!!!!

extern "C"
{
#include <sys/socket.h>
#include <unistd.h>
}
#include <errno.h>
#include <cstdio>

#include <iostream>
using std::cout;





int main()
{

	errno = 0;
	int fd = socket(AF_INET, SOCK_DGRAM, -5);
	
	if(-1 == fd)
	{
		cout<<"Error :"<<errno<<"\n";
		perror("");
	}else
	{
		cout<<"The fd of the socket is :"<<fd<<"\n";
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




