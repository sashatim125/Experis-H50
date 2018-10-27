
// 
//  @file DBLogLib.cpp
//  @brief DB Log Library
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <iostream>//TODO TEST

#include <map>
#include <sstream>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <stdexcept>

#include "controller.h"
#include "modelsFactory.h"
#include "stopEvent.h"
#include "simpleEvent.h"
#include "eventsWaitableQueue.h"
#include "DBConnection.h"

////////////Custom Part/////////////////////////

///////// DBLog //////////////
class DBLog
:	public Controller
{
public:
	DBLog(const Configuration& _config, Registrator& _r);
	
//	virtual 
//	~DBLog() {}
	
	virtual
	void Run();
	
	virtual
	void Stop();
	
	virtual
	void ReceiveEvent(Event_sp _event);
	
//Agent(Controller) creating function (MANDATORY)////
	static 	
	Agent* CreateDBLog
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
/////////////////////////////////////////////////	
	
private:

	Configuration m_config;
	
	DBConnection_sp m_dbconn;

	EventsWaitableQueue m_q;
};
////////////////////////////////////////////////

DBLog::DBLog(const Configuration& _config, Registrator& _r)
:	m_config(_config)

{	
	//TODO TEST
	//std::cout<<m_config.m_config<<std::endl;

	std::string comma(","), emptyStr;
	size_t firstComma = m_config.m_config.find_first_of(comma);
	size_t secondComma = m_config.m_config.find_last_of(comma);
		
	DBConnectionConfig dbconnConf
		(m_config.m_config.substr(0,firstComma),
		 m_config.m_config.substr(firstComma+1,secondComma-firstComma-1),
		 m_config.m_config.substr(secondComma+1));
	
	m_dbconn = DBConnection_sp(new DBConnection(dbconnConf));
	
	Location loc(emptyStr,emptyStr);
	Event* event = new SimpleEvent(emptyStr,loc,m_config.m_id);
	_r.Register(*this,Event_sp(event));
}
	
void DBLog::Run()
{
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"DB logger's ON");
	}catch(...)
	{}

	for(;;)
	{
		Event_sp event(m_q.Dequeue());
		
		if(dynamic_cast<StopEvent*>(event.get()))
		{
			for(;;)
			{			
				try
				{
					Event_sp esp(m_q.TryDequeue());
					//TEST
					//std::cout<<esp->GetTopic()<<std::endl;
				}
				catch(std::runtime_error re)
				{
					break;
				}
			}
			break;
		}
		
		try
		{
			std::ostringstream os1;
	
			os1<<event->GetTimestamp().ToString()<<"; ";
			os1<<event->GetTopic()<<"; ";
			os1<<event->GetLocation();
		
			Connect_sp conn = m_dbconn->GetConnection();
	
			std::ostringstream os2;
	
			os2<<
			"SELECT\
				id AS agent_id\
			FROM\
				agent\
			WHERE\
				name = '" << event->GetSenderID() <<"';";  
			//TEST
			//std::cout<<  os2.str() <<std::endl;
	
			std::tr1::shared_ptr<sql::Statement> stmt1(conn->createStatement());
		  	std::tr1::shared_ptr<sql::ResultSet> res1(stmt1->executeQuery(os2.str()));
		  	res1->next();
		  	int a_id = res1->getInt("agent_id");
		  	//TEST
		  	//std::cout<<  a_id <<std::endl;
		  	
		  	if (!a_id)
		  	{
		  		throw std::runtime_error("Can't write event to mysql DB ");
		  	}
		  	
		  	std::ostringstream os3;
		  	
		  	os3<<"INSERT INTO events (agent_id, time, description) VALUES" 
				<<"("<<a_id<<", now(),'"<< os1.str() << "');";
		  	//TEST
			//std::cout<<  os3.str() <<std::endl;
		  	
		  	std::tr1::shared_ptr<sql::Statement> stmt2(conn->createStatement());
		  	stmt2->execute(os3.str());

		}
		catch (sql::SQLException &_e)
		{
			throw std::runtime_error(std::string("Can't write event to mysql DB : ")+_e.what());
		}
	}
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"DB logger's OFF");
	}catch(...)
	{}
}

void DBLog::Stop()
{
	Event_sp stopEvent(new StopEvent("STOP!!!"));

	m_q.Enqueue(stopEvent);
}

void DBLog::ReceiveEvent(Event_sp _event)
{
	m_q.Enqueue(_event);
}
	

Agent* DBLog::CreateDBLog
	(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	return (0!=_er) ? new DBLog(_config, *_r) : 0;
}
//END OF /////// DBLog ////////////////////////







//TODO add more devices
//in the format  :
//m_cfl["DEVICE_TYPE"] = DEVICE_CLASS::DEVICE_CREAT_FUNCTION;
///////////////////////
#define CONTROLLERS_LIST do\
{\
	m_cfl["DBLog"] = DBLog::CreateDBLog;\
\
\
}while(false)

////////////////////////////////////////////////////
//////////////common part///////////////////////////
////////////////////////////////////////////////////
class ControllersModelsFactory
:	public ModelsFactory
{
public:

	ControllersModelsFactory();

	virtual
	Agent* CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
	
	virtual
	void DestroyAgent(Agent*);
	
private:

	static bool m_initiated;

	static std::map<std::string, CreateAgentFunctionType> m_cfl;
};

bool ControllersModelsFactory::m_initiated = false;
std::map<std::string, CreateAgentFunctionType> ControllersModelsFactory::m_cfl;

ControllersModelsFactory::ControllersModelsFactory()
{
	if(m_initiated)
	{
		return;
	}else
	{
		m_initiated = true;
	}
	
	CONTROLLERS_LIST;
}

Agent* ControllersModelsFactory::CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	std::map<std::string, CreateAgentFunctionType>::iterator it;
	
	it = m_cfl.find(_config.m_type);
	return (it != m_cfl.end()) ? ((*it).second)(_config, _r, _er) : 0;
}

void ControllersModelsFactory::DestroyAgent(Agent* _agent)
{
	delete _agent;
}

////////////Entry function/////////////////////////
//returns an object of ControllersModelsFactory////
///////////////////////////////////////////////////
// DO NOT CHANGE THE FUNCTION NAME/SIGNATURE //////
///////////////////////////////////////////////////
extern "C"
ModelsFactory* GetModelsFactory()
{
	return new ControllersModelsFactory();
}
//////////////////////////////////////////////////

















