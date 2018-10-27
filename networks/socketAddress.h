#ifndef __SOCKETADDRESS_H__
#define __SOCKETADDRESS_H__

#include <netinet/in.h>
#include <arpa/inet.h>

#include <string>
#include <stdexcept>
#include <sstream>


namespace advcpp
{

using std::string;

const string LOCAL_HOST = "127.0.0.1";

typedef unsigned short Port_T;

class Socket;
class ServerSocket;


class SocketAddress
{
	friend class Socket;
	friend class ServerSocket;

public:

	//to be filled later
	SocketAddress();

	//throws
	SocketAddress(const string& _ipAddress, const Port_T& _port);
	
	string GetIpAddress() const;

	const Port_T& GetPort() const;
	
	string ToString() const;

private:

	struct sockaddr_in& Get_sockaddr();
	const struct sockaddr_in& Get_sockaddr() const;

	struct sockaddr_in m_address;
};

////////////////////////////////////////

inline
SocketAddress::SocketAddress()
:	m_address()
{}

inline
SocketAddress::SocketAddress(const string& _ipAddress, const Port_T& _port)
:	m_address()
{
		m_address.sin_family = AF_INET;
		m_address.sin_port = htons(_port);
	
		int res = inet_aton(_ipAddress.c_str(), &m_address.sin_addr);
		if(! res)
		{
			throw std::invalid_argument("wrong inet address!");
		}
}

inline
struct sockaddr_in& SocketAddress::Get_sockaddr()
{
	return m_address;
}

inline
const struct sockaddr_in& SocketAddress::Get_sockaddr() const
{
	return m_address;
}

inline
string SocketAddress::GetIpAddress() const
{
	return inet_ntoa(m_address.sin_addr);
}

inline
const Port_T& SocketAddress::GetPort() const
{
	return m_address.sin_port;
}



inline
string SocketAddress::ToString() const
{
	std::ostringstream oss;
	oss<< GetIpAddress() << ":" << GetPort();
	
	return oss.str();
}











}//namespace advcpp
#endif //__SOCKETADDRESS_H__
