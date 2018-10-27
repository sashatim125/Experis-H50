#ifndef __CHATCOMMON_H__
#define __CHATCOMMON_H__




enum MessageType
{
	CLIENT_CONNECT_REQUEST,
	CLIENT_CONNECT_ACCEPTED,
	CLIENT_CONNECT_REFUSED,
	CLIENT_MESSAGE,
	SERVER_MESSAGE,
	CLIENT_CONNECT_STOP

};

struct Message
{
	MessageType	m_type;
	size_t 		m_size;
	char		m_buff[1];
};





















#endif //__CHATCOMMON_H__
