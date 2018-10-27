
// 
//  @file LgSensorsLib.cpp
//  @brief Lg Sensors Library
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
#include<signal.h>
//#include <pthread.h>
}
#include <cstdlib>//rand()
#include <sstream>

#include <map>

#include "sensor.h"
#include "modelsFactory.h"
#include "simpleEvent.h"
#include "mutex.h"

using namespace advcpp;

////////////Custom Part/////////////////////////

///////// LgTempSensor ////////////////////////////
class LgTempSensor
:	public Sensor
{
public:
	LgTempSensor(const Configuration& _config, EventsReceiver& _er);
	
//	virtual 
//	~LgTempSensor() {}
	
	virtual
	void Run();
	
	virtual
	void Stop() ;
	
	virtual
	void SetReceiver(EventsReceiver& _er);

//Agent(Sensor) creating function (MANDATORY)////
	static 	
	Agent* CreateLgTempSensor
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
};
///////////////////////////////////////////

LgTempSensor::LgTempSensor(const Configuration& _config, EventsReceiver& _er)
:	m_er(_er)
,	m_config(_config)
,	m_stopNow(false)
{}
	
void LgTempSensor::Run()
{
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"sensor's ON");
	}catch(...)
	{}

	while(true)
	{
		{
			MutexGuard mg(m_mutex);
			if(m_stopNow)
			{
				break;
			}	
		}
		sleep(12);
		std::ostringstream os;
		os<<(rand()%61-5);
		Location loc(m_config.m_floor,m_config.m_room);
		Event *event = new SimpleEvent(m_config.m_type,loc,m_config.m_id,os.str());
		Event_sp eventSp(event);
		SendEvent(eventSp);
		try
		{
			ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"new event was sent");
			ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE, static_cast<SimpleEvent*>(eventSp.get())->ToString());
		}catch(...)
		{}
	}
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"sensor's OFF");
	}catch(...)
	{}
}

void LgTempSensor::Stop()
{
	MutexGuard mg(m_mutex);
	m_stopNow = true;
}

void LgTempSensor::SetReceiver(EventsReceiver& _er)
{
	m_er = _er;
}
	
void LgTempSensor::SendEvent(Event_sp _event)
{
	m_er.ReceiveEvent(_event);
}

Agent* LgTempSensor::CreateLgTempSensor(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	return (0!=_er) ? new LgTempSensor(_config, *_er) : 0;
}
//END OF /////// LgTempSensor ////////////////////////


///////// LgFireSensor ////////////////////////////
class LgFireSensor
:	public Sensor
{
public:
	LgFireSensor(const Configuration& _config, EventsReceiver& _er);
	
//	virtual 
//	~LgFireSensor() {}
	
	virtual
	void Run();
	
	virtual
	void Stop() ;
	
	virtual
	void SetReceiver(EventsReceiver& _er);

//Agent(Sensor) creating function (MANDATORY)////
	static 	
	Agent* CreateLgFireSensor
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
	
	pthread_t m_myPthreadId;
};
////////////////////////////////////

LgFireSensor::LgFireSensor(const Configuration& _config, EventsReceiver& _er)
:	m_er(_er)
,	m_config(_config)
,	m_stopNow(false)
{}

static void DoNothing(int i)
{}
	
void LgFireSensor::Run()
{		
	m_myPthreadId = pthread_self();

	sigset_t sigset;
	int sig;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGUSR2);
	pthread_sigmask(SIG_UNBLOCK,&sigset,0);
	
	struct sigaction sigIgnore={0};
	sigIgnore.sa_handler = DoNothing;
	sigaction(SIGUSR2,&sigIgnore,0);

	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"sensor's ON");
	}catch(...)
	{}	

	while(true)
	{
		//sleep(rand()%11+5);
		sigwait(&sigset,&sig);
		{
			MutexGuard mg(m_mutex);
			if(m_stopNow)
			{
				break;
			}	
		}
		
		Location loc(m_config.m_floor,m_config.m_room);
		Event *event = new SimpleEvent("Fire_Detected",loc,m_config.m_id,"URGENT!!!");
		Event_sp eventSp(event);
		SendEvent(eventSp);
		
		try
		{
			ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"new event was sent");
			ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE, static_cast<SimpleEvent*>(eventSp.get())->ToString());
		}catch(...)
		{}
		
	}
	try
	{
		ZLOG(*(m_config.m_log),m_config.m_id, Zlog::LOG_TRACE,"sensor's OFF");
	}catch(...)
	{}
}

void LgFireSensor::Stop()
{
	{
		MutexGuard mg(m_mutex);
	
		m_stopNow = true;
	}
	pthread_kill(m_myPthreadId,SIGUSR2);
}

void LgFireSensor::SetReceiver(EventsReceiver& _er)
{
	m_er = _er;
}
	
void LgFireSensor::SendEvent(Event_sp _event)
{
	m_er.ReceiveEvent(_event);
}

Agent* LgFireSensor::CreateLgFireSensor(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	return (0!=_er) ? new LgFireSensor(_config, *_er) : 0;
}
//END OF /////// LgTempSensor ////////////////////////


//TODO add more devices
//in the format  :
//m_cfl["DEVICE_TYPE"] = DEVICE_CLASS::DEVICE_CREAT_FUNCTION;
///////////////////////
#define SENSORS_LIST do\
{\
	m_cfl["ambient_temp"] 	= LgTempSensor::CreateLgTempSensor;\
	m_cfl["TestFire"] 		= LgFireSensor::CreateLgFireSensor;\
\
\
}while(false)

////////////////////////////////////////////////////
//////////////common part///////////////////////////
////////////////////////////////////////////////////
class SensorsModelsFactory
:	public ModelsFactory
{
public:

	SensorsModelsFactory();

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

bool SensorsModelsFactory::m_initiated = false;
std::map<std::string, CreateAgentFunctionType> SensorsModelsFactory::m_cfl;

SensorsModelsFactory::SensorsModelsFactory()
{
	if(m_initiated)
	{
		return;
	}else
	{
		m_initiated = true;
	}
	
	SENSORS_LIST;
}

Agent* SensorsModelsFactory::CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	std::map<std::string, CreateAgentFunctionType>::iterator it;
	
	it = m_cfl.find(_config.m_type);
	return (it != m_cfl.end()) ? ((*it).second)(_config, _r, _er) : 0;
}

void SensorsModelsFactory::DestroyAgent(Agent* _agent)
{
	delete _agent;
}

void SensorsModelsFactory::GetModelsTypes(std::list<std::string>& _typesList)
{
	std::map<std::string, CreateAgentFunctionType>::const_iterator it = m_cfl.begin();
	std::map<std::string, CreateAgentFunctionType>::const_iterator end = m_cfl.end();
	for(; it != end; ++it)
	{
		_typesList.push_back(it->first);
	}
}

////////////Entry function/////////////////////
//returns an object of SensorsModelsFactory////
///////////////////////////////////////////////
// DO NOT CHANGE THE FUNCTION NAME/SIGNATURE //
///////////////////////////////////////////////
extern "C"
ModelsFactory* GetModelsFactory()
{
	return new SensorsModelsFactory();
}
///////////////////////////////////////////////

















