#ifndef __SERVERSOCKET_H__
#define __SERVERSOCKET_H__


#include "socket.h"

namespace advcpp
{


class ServerSocket : public Socket
{
	
public:

	//create and bind (and listen for tcp)
	//throws
	ServerSocket(const SocketAddress& _adress, Socket::SocketType _type =UDP, unsigned short _backlog =0);
	
	~ServerSocket();
	
	
/*	
	//num of bytes sent is returned
	template <size_t SIZE>
	size_t Send(SimpleBuffer<SIZE>& _buffer);
	
	//num of bytes received is returned
	template <size_t SIZE>
	size_t Receive(SimpleBuffer<SIZE>& _buffer);
	
	//num of bytes received is returned
	template <size_t SIZE>
	size_t Receive(SimpleBuffer<SIZE>& _buffer, SocketAddress& _from);
*/	


private:
	//uncopyable objects
	ServerSocket(const ServerSocket&);
	const ServerSocket& operator=(const ServerSocket&);

};

inline
ServerSocket::ServerSocket(const SocketAddress& _adress, Socket::SocketType _type)
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
	
	int res = bind(m_fd, reinterpret_cast<const struct sockaddr*>(&_adress.Get_sockaddr()), sizeof(_adress.Get_sockaddr()));
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
#endif //__SERVERSOCKET_H__
