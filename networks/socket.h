#ifndef __SOCKET_H__
#define __SOCKET_H__


#include <unistd.h>

#include <errno.h>
#include <cstring>

#include "socketAddress.h"

namespace advcpp
{

template <size_t SIZE>
struct SimpleBuffer
{
	char m_address[SIZE];
	size_t m_size;
};


class ServerSocket;

class Socket
{
//	friend class ServerSocket;
	
public:

	enum SocketType {TCP, UDP};

	//create and connect
	//throws
	Socket(const SocketAddress& _adress, SocketType _type =UDP);
	
	~Socket();
	
	//num of bytes sent is returned
	template <size_t SIZE>
	size_t Send(SimpleBuffer<SIZE>& _buffer);
	
	//num of bytes received is returned
	template <size_t SIZE>
	size_t Receive(SimpleBuffer<SIZE>& _buffer);
	
	//num of bytes received is returned
	template <size_t SIZE>
	size_t Receive(SimpleBuffer<SIZE>& _buffer, SocketAddress& _from);
	
protected:
	//for ServerSocket use only
	explicit Socket(int _fd);
	
	int m_fd;

private:
	//uncopyable objects
	Socket(const Socket&);
	const Socket& operator=(const Socket&);
};

inline
Socket::Socket(const SocketAddress& _adress, SocketType _type)
{
	int curtype;
	
	switch (_type)
	{
		case TCP:
			curtype = SOCK_STREAM;
			break;
			
		case UDP:
			curtype = SOCK_DGRAM;
			break;
				
		default:
			throw std::invalid_argument("wrong socket type!");
	}

	errno = 0;	
	m_fd = socket(AF_INET, curtype, 0);
	
	if(-1 == m_fd)
	{
		throw std::runtime_error(strerror(errno));
	}
	
	int res = connect(m_fd, reinterpret_cast<const struct sockaddr*>(&_adress.Get_sockaddr()), sizeof(_adress.Get_sockaddr()));
	if(res == -1)
	{
		close(m_fd);
		throw std::runtime_error(strerror(errno));
	}
}
	
inline
Socket::~Socket()
{
	close(m_fd);
}

inline
Socket::Socket(int _fd)
:	m_fd(_fd)
{}


template <size_t SIZE> inline
size_t Socket::Send(SimpleBuffer<SIZE>& _buffer)
{
	errno=0;
	ssize_t numOfBytes = send(m_fd, _buffer.m_address, _buffer.m_size, 0);
	
	if(-1 == numOfBytes)
	{
		throw std::runtime_error(strerror(errno));
	}else
	{
		return static_cast<size_t>(numOfBytes);
	}
}

template <size_t SIZE>
size_t Socket::Receive(SimpleBuffer<SIZE>& _buffer)
{
	SocketAddress& from;
	return Receive(_buffer, from);
}
	

template <size_t SIZE>
size_t Socket::Receive(SimpleBuffer<SIZE>& _buffer, SocketAddress& _from)
{
	errno=0;
	size_t addressSize = sizeof(_from.Get_sockaddr());
	
	ssize_t numOfBytes = recvfrom(m_fd, _buffer.m_address, SIZE, 0,
			reinterpret_cast<struct sockaddr*>(&_from.Get_sockaddr()),
			reinterpret_cast<socklen_t*> (&addressSize));
	
	if(-1 == numOfBytes)
	{
		throw std::runtime_error(strerror(errno));
	}else
	{
		return static_cast<size_t>(numOfBytes);
	}
}
























}//namespace advcpp
#endif //__SOCKET_H__
