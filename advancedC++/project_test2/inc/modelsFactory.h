#ifndef __MODELSFACTORY_H__
#define __MODELSFACTORY_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file modelsFactory.h
//  @brief Models Factory (agents creator)
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "eventsReceiver.h"
#include "registrator.h"
#include "configuration.h"
#include "agent.h"


namespace advcpp
{

interface ModelsFactory
{
	virtual
	~ModelsFactory()
	{}

	//returns 0 if no such type
	virtual
	Agent* CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er) =0;
	
	virtual
	void DestroyAgent(Agent* _a) =0;
};


typedef Agent* (*CreateAgentFunctionType)
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);

}






#endif //__MODELSFACTORY_H__


