
// 
//  @file TestAgentsLib.cpp
//  @brief Test Agents Library
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//



#include <sstream>
#include <iostream>

#include <map>
#include <vector>

#include "sensor.h"
#include "controller.h"
#include "modelsFactory.h"
#include "simpleEvent.h"
#include "mutex.h"


////////////Custom Part/////////////////////////

///////// TestAgent ////////////////////////////
class TestAgent
:	public Sensor
,	public Controller
{
public:
	TestAgent(const Configuration& _config, Registrator& _r, EventsReceiver& _er);
	
//	virtual 
//	~TestAgent() {}
	
	virtual
	void Run();
	
	virtual
	void Stop() ;
	
	virtual
	void SetReceiver(EventsReceiver& _er);
	
	virtual
	void ReceiveEvent(Event_sp _event) ;

//Agent creating function (MANDATORY)////////////
	static 	
	Agent* CreateTestAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
/////////////////////////////////////////////////	
protected:
	
	virtual
	void SendEvent(Event_sp _event);
	
private:

	EventsReceiver& m_er;
	
	Configuration m_config;
	
	Mutex m_mutex;
	bool m_stopNow;

	Mutex m_mutex2;
	std::vector<int> m_vec;
};
///////////////////////////////////////////

TestAgent::TestAgent(const Configuration& _config, Registrator& _r, EventsReceiver& _er)
:	m_er(_er)
,	m_config(_config)
,	m_stopNow(false)
{
	Location loc(m_config.m_floor,m_config.m_room);
	Event* event = new SimpleEvent(m_config.m_id,loc,m_config.m_id);
	
	_r.Register(*this,Event_sp(event));
	
	std::istringstream iss(m_config.m_config);
	int start , finish;
	iss>>start;
	finish = start+999;
	
	for(int i=start; i<=finish; ++i)
	{
		m_vec.push_back(i);
	}
	
}
	
void TestAgent::Run()
{
	std::cout<<m_config.m_id<<" started !"<<std::endl;
	
	std::istringstream iss(m_config.m_config);
	int start , finish;
	iss>>start;
	finish = start+999;
	for(int i=start; i<=finish; ++i)
	{
		std::ostringstream os;
		os<<i;
		Location loc(m_config.m_floor,m_config.m_room);
		Event *event = new SimpleEvent(m_config.m_id,loc,m_config.m_id,os.str());
		SendEvent(Event_sp(event));
	}

	std::cout<<m_config.m_id<<" finished sending events !"<<std::endl;
	
	while(1)
	{
		{
			MutexGuard mg(m_mutex);
			if(m_stopNow)
			{
				break;
			}
		}
		{
			MutexGuard mg(m_mutex2);
			int sum,i;
			for(i=0, sum=0 ; i< 1000; ++i)
			{
				sum+=m_vec[i];
			}
			if(0 == sum)
			{
				break;
			}
		}
		sleep(1);	
	}
	
	std::cout<<m_config.m_id<<" finished receiving events !"<<std::endl;
}

void TestAgent::Stop()
{
	MutexGuard mg(m_mutex);
	m_stopNow = true;
}

void TestAgent::ReceiveEvent(Event_sp _event)
{	
	SimpleEvent* se = dynamic_cast<SimpleEvent*>(_event.get());
	if(0 == se)
	{
		return;
	}
	
	if(se->GetTopic() != m_config.m_id)
	{
		std::cout<<m_config.m_id<<" received wrong topic event !"<<std::endl;
	}
	
	std::istringstream iss(se->GetPayload());
	int payload;
	iss>>payload;
	
	std::istringstream iss2(m_config.m_config);
	int start , finish;
	iss2>>start;
	finish = start+999;
	
	MutexGuard mg(m_mutex2);
	if(	payload < start  ||
		payload > finish ||
		m_vec[payload-start] == 0)
	{
		std::cout<<m_config.m_id<<" received wrong payload event :"<<payload<<std::endl;
	}
	m_vec[payload-start] = 0;
}

void TestAgent::SetReceiver(EventsReceiver& _er)
{
	m_er = _er;
}
	
void TestAgent::SendEvent(Event_sp _event)
{
	m_er.ReceiveEvent(_event);
}

Agent* TestAgent::CreateTestAgent(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	return new TestAgent(_config, *_r, *_er);
}
//END OF /////// TestAgent ////////////////////////



//TODO add more devices
//in the format  :
//m_cfl["DEVICE_TYPE"] = DEVICE_CLASS::DEVICE_CREAT_FUNCTION;
///////////////////////
#define AGENTS_LIST do\
{\
	m_cfl["test_agent"] 	= TestAgent::CreateTestAgent;\
\
\
}while(false)

////////////////////////////////////////////////////
//////////////common part///////////////////////////
////////////////////////////////////////////////////
class AgentsModelsFactory
:	public ModelsFactory
{
public:

	AgentsModelsFactory();

	virtual
	Agent* CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
	
	virtual
	void DestroyAgent(Agent*);
	
private:

	static bool m_initiated;

	static std::map<std::string, CreateAgentFunctionType> m_cfl;
};

bool AgentsModelsFactory::m_initiated = false;
std::map<std::string, CreateAgentFunctionType> AgentsModelsFactory::m_cfl;

AgentsModelsFactory::AgentsModelsFactory()
{
	if(m_initiated)
	{
		return;
	}else
	{
		m_initiated = true;
	}
	
	AGENTS_LIST;
}

Agent* AgentsModelsFactory::CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	std::map<std::string, CreateAgentFunctionType>::iterator it;
	
	it = m_cfl.find(_config.m_type);
	return (it != m_cfl.end()) ? ((*it).second)(_config, _r, _er) : 0;
}

void AgentsModelsFactory::DestroyAgent(Agent* _agent)
{
	delete _agent;
}

////////////Entry function/////////////////////
//returns an object of SensorsModelsFactory////
///////////////////////////////////////////////
// DO NOT CHANGE THE FUNCTION NAME/SIGNATURE //
///////////////////////////////////////////////
extern "C"
ModelsFactory* GetModelsFactory()
{
	return new AgentsModelsFactory();
}
///////////////////////////////////////////////

















