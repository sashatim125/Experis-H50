

// 
//  @file DBLog.cpp
//  @brief log events to DB
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <stdexcept>

#include "DBLog.h"
#include "stopEvent.h"

using namespace advcpp;

DBLog::DBLog(const DBConnectionConfig& _config)
:	m_dbconn(_config)
{}

void DBLog::Run()
{
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
		
			Connect_sp conn = m_dbconn.GetConnection();
	
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
}

void DBLog::WriteToLog(Event_sp _event)
{
	m_q.Enqueue(_event);
}



