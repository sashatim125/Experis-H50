
// 
//  @file agentsManager.cpp
//  @brief Agents Manager
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "agentsManager.h"


using namespace advcpp;


AgentsManager::AgentsManager(
	const std::string& _iniDir,
	AgentsLoadersManager& _alm,
	Registrator* _r,
	EventsReceiver* _er)
{
	IniFileParser iniParser(_iniDir+"/agents_config.ini");	
	const std::map<std::string, IniFileSection>& agentsIniSections =
	iniParser.GetIniSections();
	std::map<std::string, IniFileSection>::const_iterator it = agentsIniSections.begin();
	std::map<std::string, IniFileSection>::const_iterator end = agentsIniSections.end();
	
	for(; it != end; ++it)
	{
		Configuration conf(it->second);
		m_agents.push_back(PThread_sp(new PThread(_alm.CreateAgent(conf,_r,_er))));
	}
}



AgentsManager::AgentsManager(
	const DBConnectionConfig& _config,
	AgentsLoadersManager& _alm,
	Registrator* _r,
	EventsReceiver* _er)
{
	try
	{
		DBConnection_sp dbconn(new DBConnection(_config));
		Connect_sp conn = dbconn->GetConnection();
		std::tr1::shared_ptr<sql::Statement> stmt(conn->createStatement());
	  	std::tr1::shared_ptr<sql::ResultSet> res(stmt->executeQuery(
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
			location AS l ON a.location_id = l.id;"));
		
		while (res->next())
		{
			Configuration conf(*res);
			m_agents.push_back(PThread_sp(new PThread(_alm.CreateAgent(conf,_r,_er))));
		}
	}
	catch (sql::SQLException &_e)
	{
		throw std::runtime_error(std::string("Agent creation from DB failed : ")+_e.what());
	}
}

void AgentsManager::Start()
{
	size_t i=0 , vecSize = m_agents.size();
	for(; i < vecSize ; ++i)
	{
		m_agents[i]->Start();
	}
}



	
void AgentsManager::StopAndWait()
{
	size_t i=0 , vecSize = m_agents.size();
	//TODO TEST
	//std::cout<<"Num of agents "<<vecSize<<"\n"<<std::endl;
	Agent *nextAgent;
	for(; i < vecSize ; ++i)
	{
		nextAgent = static_cast<Agent*>(((m_agents[i])->GetRunnable()).get());
		nextAgent->Stop();
	}
	
	//TODO TEST
	//std::cout<<"Agents stopped !\n"<<std::endl;
	for(i=0; i < vecSize ; ++i)
	{
		m_agents[i]->Join();
	}
	//TODO TEST
	//std::cout<<"Agents joined !\n"<<std::endl;
}













