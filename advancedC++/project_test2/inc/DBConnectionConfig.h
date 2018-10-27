#ifndef __DBCONNECTIONCONFIG_H__
#define __DBCONNECTIONCONFIG_H__

// 
//  @file DBConnectionConfig.h
//  @brief Configuration struct for connection to DB
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <string>

namespace advcpp
{

struct DBConnectionConfig
{
	inline
	DBConnectionConfig(const std::string& _tcpAddress, const std::string& _userName, const std::string& _password);

	std::string m_tcpAddress;	

	std::string m_userName;
	
	std::string m_password;
};

}

using namespace advcpp;

inline
DBConnectionConfig::DBConnectionConfig
	(const std::string& _tcpAddress, const std::string& _userName, const std::string& _password)
:	m_tcpAddress(_tcpAddress)
,	m_userName(_userName)
,	m_password(_password)
{}




#endif //__DBCONNECTIONCONFIG_H__

