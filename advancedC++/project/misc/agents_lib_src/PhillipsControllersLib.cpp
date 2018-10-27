
// 
//  @file PhillipsControllersLib.cpp
//  @brief Phillips Controllers Library
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

extern "C"
{
#include <unistd.h>
}

//#include <iostream>//TODO TEST

#include <map>

#include "controller.h"
#include "modelsFactory.h"
#include "simpleEvent.h"
#include "mutex.h"

using namespace advcpp;

////////////Custom Part/////////////////////////

///////// PhillipsHVACController //////////////
class PhillipsHVACController
:	public Controller
{
public:
	PhillipsHVACController(const Configuration& _config, Registrator& _r);
	
//	virtual 
//	~PhillipsHVACController() {}
	
	virtual
	void Run();
	
	virtual
	void Stop();
	
	virtual
	void ReceiveEvent(Event_sp _event);
	
//Agent(Controller) creating function (MANDATORY)////
	static 	
	Agent* CreatePhillipsHVACController
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
/////////////////////////////////////////////////	
	
private:

	Configuration m_config;
	
	Mutex m_mutex;
	bool m_stopNow;
};
////////////////////////////////////////////////

PhillipsHVACController::PhillipsHVACController(const Configuration& _config, Registrator& _r)
:	m_config(_config)
,	m_stopNow(false)
{
	
	Location loc(m_config.m_floor,"");
	Event* event = new SimpleEvent("Fire_Detected",loc,m_config.m_id);
	
	_r.Register(*this,Event_sp(event));
	
	loc = Location(m_config.m_floor,m_config.m_room);
	event = new SimpleEvent("ambient_temp",loc,m_config.m_id);
	
	_r.Register(*this,Event_sp(event));

}
	
void PhillipsHVACController::Run()
{
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"controller's ON");
	}catch(...)
	{}
	
	while(true)//doing nothing
	{
		sleep(1);
		{
			MutexGuard mg(m_mutex);
			if(m_stopNow)
			{
				break;
			}
		}
	}
	
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"controller's OFF");
	}catch(...)
	{}
}

void PhillipsHVACController::Stop()
{
	MutexGuard mg(m_mutex);
	m_stopNow = true;
}

void PhillipsHVACController::ReceiveEvent(Event_sp _event)
{
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"new event received");
	}catch(...)
	{}
	
	SimpleEvent* se = dynamic_cast<SimpleEvent*>(_event.get());
	if(0 == se)
	{
		return;
	}

	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE, se->ToString());
	}catch(...)
	{}
}
	

Agent* PhillipsHVACController::CreatePhillipsHVACController
	(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	return (0!=_er) ? new PhillipsHVACController(_config, *_r) : 0;
}
//END OF /////// PhillipsHVACController ////////////////////////


///////// PhillipsSprinklerController //////////////
class PhillipsSprinklerController
:	public Controller
{
public:
	PhillipsSprinklerController(const Configuration& _config, Registrator& _r);
	
//	virtual 
//	~PhillipsSprinklerController() {}
	
	virtual
	void Run();
	
	virtual
	void Stop();	
	
	virtual
	void ReceiveEvent(Event_sp _event);
	
//Agent(Controller) creating function (MANDATORY)////
	static 	
	Agent* CreatePhillipsSprinklerController
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
/////////////////////////////////////////////////	
	
private:

	Configuration m_config;
	
	Mutex m_mutex;
	bool m_stopNow;
};
////////////////////////////////////////////////////

PhillipsSprinklerController::PhillipsSprinklerController(const Configuration& _config, Registrator& _r)
:	m_config(_config)
,	m_stopNow(false)
{
	Location loc(m_config.m_floor,m_config.m_room);
	Event* event = new SimpleEvent("Fire_Detected",loc,m_config.m_id);
	
	_r.Register(*this,Event_sp(event));
	
	event = new SimpleEvent("Smoke_Detected",loc,m_config.m_id);
	
	_r.Register(*this,Event_sp(event));
}
	
void PhillipsSprinklerController::Run()
{
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"controller's ON");
	}catch(...)
	{}
	
	while(true)//doing nothing
	{
		sleep(1);
		{
			MutexGuard mg(m_mutex);
			if(m_stopNow)
			{
				break;
			}
		}
	}
	
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"controller's OFF");
	}catch(...)
	{}
}

void PhillipsSprinklerController::Stop()
{
	MutexGuard mg(m_mutex);
	m_stopNow = true;
}

void PhillipsSprinklerController::ReceiveEvent(Event_sp _event)
{
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"new event received");
	}catch(...)
	{}
	
	SimpleEvent* se = dynamic_cast<SimpleEvent*>(_event.get());
	if(0 == se)
	{
		return;
	}

	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE, se->ToString());
	}catch(...)
	{}
}
	

Agent* PhillipsSprinklerController::CreatePhillipsSprinklerController
	(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	return (0!=_er) ? new PhillipsSprinklerController(_config, *_r) : 0;
}
//END OF /////// PhillipsSprinklerController ////////////////////////



//TODO add more devices
//in the format  :
//m_cfl["DEVICE_TYPE"] = DEVICE_CLASS::DEVICE_CREAT_FUNCTION;
///////////////////////
#define CONTROLLERS_LIST do\
{\
	m_cfl["TestHVAC"]		= PhillipsHVACController::CreatePhillipsHVACController;\
	m_cfl["TestSprinkler"]	= PhillipsSprinklerController::CreatePhillipsSprinklerController;\
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
	
	virtual
	void GetModelsTypes(std::list<std::string>& _typesList);
	
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

void ControllersModelsFactory::GetModelsTypes(std::list<std::string>& _typesList)
{
	std::map<std::string, CreateAgentFunctionType>::const_iterator it = m_cfl.begin();
	std::map<std::string, CreateAgentFunctionType>::const_iterator end = m_cfl.end();
	for(; it != end; ++it)
	{
		_typesList.push_back(it->first);
	}
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

















