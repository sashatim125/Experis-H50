#ifndef __DBCONNECTION_H__
#define __DBCONNECTION_H__

// 
//  @file DBConnection.h
//  @brief connection to mysql DB of the project
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>

#include <tr1/memory>
#include <string>

#include "DBConnectionConfig.h"


namespace advcpp
{

typedef std::tr1::shared_ptr<sql::Connection> Connect_sp;  

class DBConnection
{
public:
	explicit inline
	DBConnection(const DBConnectionConfig& _config);
	
	inline
	Connect_sp GetConnection();

private:

  sql::Driver *m_driver;
  
  Connect_sp m_connect;
};

typedef std::tr1::shared_ptr<DBConnection> DBConnection_sp;

}

using namespace advcpp;

inline
DBConnection::DBConnection(const DBConnectionConfig& _config)
try
:	m_driver(get_driver_instance())
,	m_connect(m_driver -> connect(_config.m_tcpAddress, _config.m_userName, _config.m_password))
{
	m_connect->setSchema("smart_building_project_test");
}
catch (sql::SQLException &_e)
{
	throw std::runtime_error(std::string("Can't setup connection to mysql DB : ")+_e.what());
}


inline
Connect_sp DBConnection::GetConnection()
{
	if(! m_connect->isValid())
	{
		m_connect->reconnect();
	}

	return m_connect;
}











#endif //__DBCONNECTION_H__

