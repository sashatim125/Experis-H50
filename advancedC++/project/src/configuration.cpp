

// 
//  @file configuration.cpp
//  @brief Configuration file info for an agent
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "configuration.h"

namespace advcpp
{

const std::string advcpp::Configuration::s_defaultLogName("default");


Configuration::Configuration(const IniFileSection& _section)
{
	SetConfiguration(_section);
}

Configuration::Configuration(sql::ResultSet& _resSet)
{
	m_id = _resSet.getString("a_id");
	
	m_type = _resSet.getString("a_type");
	
	m_floor = _resSet.getString("a_floor");
	
	m_room = _resSet.getString("a_room");
	
	std::string logStr = _resSet.getString("a_log");
	m_log = (!logStr.empty()) ? Zlog::GetLog(logStr) : Zlog::GetLog(s_defaultLogName);
	
	m_config = _resSet.getString("a_config");
}


void Configuration::SetConfiguration(const IniFileSection& _section)
{
	const std::map<std::string, std::string>& confMap = _section.m_varValPairs;
	std::map<std::string, std::string>::const_iterator it;
	const std::map<std::string, std::string>::const_iterator end =
		confMap.end();
	bool isOK = true;
	
	m_id = _section.m_sectionTitle;
	
	do
	{
		if(confMap.size() < 3 || confMap.size() > 5)
		{
			isOK = false;
			break;
		}
	
		if(end == (it = confMap.find("type")))
		{
			isOK = false;
			break;
		}
		m_type = (*it).second;
		
		if(end == (it = confMap.find("floor")))
		{
			isOK = false;
			break;
		}
		m_floor = (*it).second;
		
		if(end == (it = confMap.find("room")))
		{
			isOK = false;
			break;
		}
		m_room = (*it).second;
		
		if(end == (it = confMap.find("log")) ||
		((m_log = Zlog::GetLog((*it).second)) == 0))
		{
			m_log = Zlog::GetLog(s_defaultLogName);
		}
				
		if(end != (it = confMap.find("config")))
		{
			m_config = (*it).second;
		}
	}while(false);
	
	if(!isOK)
	{
		std::ostringstream os;
		os<<"Error in config section "<<m_id<<" missing and/or wrong fields! "<<std::endl;
		throw std::runtime_error(os.str());
	}
}

}//endof namespace advcpp

