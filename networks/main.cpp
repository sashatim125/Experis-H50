

#include "socket.h"

#include <cstring>
#include <iostream>






using std::cout;

using namespace advcpp;


int main()
{

	SocketAddress sa(LOCAL_HOST,50000);
	{
		Socket sock(sa,Socket::UDP);
	
		SimpleBuffer<256> sb;
	
		const char* str = "Hello, World TCP!\n";	
		strcpy(sb.m_address, str);
		sb.m_size = strlen(str+1);
		sock.Send(sb);

		SocketAddress from;
	
		size_t bytes = sock.Receive(sb, from);
		
		cout<<"received "<< bytes << " bytes from "<< from.ToString() <<"\n";
		cout<<"the message is :"<< sb.m_address;
	}

/*	{
		Socket sock(sa,Socket::TCP);
	
		SimpleBuffer<256> sb;
	
		const char* str = "Hello, World TCP!\n";	
		strcpy(sb.m_address, str);
		sb.m_size = strlen(str+1);
		sock.Send(sb);

		SocketAddress from;
	
		size_t bytes = sock.Receive(sb, from);
		
		cout<<"received "<< bytes << " bytes from "<< from.ToString() <<"\n";
		cout<<"the message is :"<< sb.m_address;
	
	}
*/
	
	










	return 0;
}

