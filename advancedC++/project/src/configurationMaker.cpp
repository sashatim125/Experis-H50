
// 
//  @file configurationMaker.cpp
//  @brief Configuration list maker for agent's config
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//



#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "configurationMaker.h"

namespace advcpp
{

static const std::string s_agentsConfigFile("/agents_config.ini");
static const std::string s_agentsCreationQuery(
		"SELECT \
			a.name AS a_id, \
			atype.name AS a_type,\
			l.floor AS a_floor, \
	   		l.room AS a_room, \
			a.log AS a_log,\
			a.config AS a_config \
		FROM \
			agent AS a\
				JOIN\
			agent_type AS atype ON a.type_id = atype.id\
				JOIN\
			location AS l ON a.location_id = l.id;"
);


ConfigurationMaker::ConfigurationMaker(const std::string& _iniDir)
{
	IniFileParser iniParser(_iniDir+s_agentsConfigFile);	
	const std::map<std::string, IniFileSection>& agentsIniSections =
	iniParser.GetIniSections();
	std::map<std::string, IniFileSection>::const_iterator it = agentsIniSections.begin();
	std::map<std::string, IniFileSection>::const_iterator end = agentsIniSections.end();
	
	for(; it != end; ++it)
	{
		Configuration conf(it->second);
		m_configList.push_back(conf);
	}
}


ConfigurationMaker::ConfigurationMaker(const DBConnectionConfig& _config)
{
	try
	{
		DBConnection_sp dbconn(new DBConnection(_config));
		Connect_sp conn = dbconn->GetConnection();
		std::tr1::shared_ptr<sql::Statement> stmt(conn->createStatement());
	  	std::tr1::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
		  	s_agentsCreationQuery));
		
		while (res->next())
		{
			Configuration conf(*res);
			m_configList.push_back(conf);
		}
	}
	catch (sql::SQLException &_e)
	{
		throw std::runtime_error(std::string("Agent creation from DB failed : ")+_e.what());
	}
}

	
const std::list<Configuration>& ConfigurationMaker::GetConfigList() const
{
	return m_configList;
}


}//endof namespace advcpp




