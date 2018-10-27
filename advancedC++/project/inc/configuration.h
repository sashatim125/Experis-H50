#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

// 
//  @file configuration.h
//  @brief Configuration file info for an agent
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <string>
#include <cppconn/resultset.h>

#include "iniFileParser.h"
#include "zlog4cpp.h"
#include "DBConnection.h"

namespace advcpp
{

struct Configuration
{
private:
	static const std::string s_defaultLogName;

public:
	Configuration()
	{}
	
	//throw runtime_error on wrong and or missing mandatory section(s)
	explicit
	Configuration(const IniFileSection& _section);
	
	explicit
	Configuration(sql::ResultSet& _resSet);

	std::string m_id;		//mandatory

	std::string m_type;		//mandatory
	
	std::string m_floor;	//mandatory
	
	std::string m_room;		//mandatory
		
	Zlog*		m_log;		//optional
	
	std::string m_config;	//optional

private:
	void SetConfiguration(const IniFileSection& _section);
	
};

}//endof namespace advcpp






#endif //__CONFIGURATION_H__

