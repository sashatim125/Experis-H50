#ifndef __AGENT_H__
#define __AGENT_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file agent.h
//  @brief Agent Interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <tr1/memory>

#include "runnable.h"
#include "stopable.h"

namespace advcpp
{

interface Agent
:	public Runnable
,	public Stopable
{
	virtual
	~Agent() {}
	
//	virtual
//	void Run() =0;

//	virtual
//	void Stop() =0;
};

typedef std::tr1::shared_ptr<Agent> Agent_sp; 

}//end of namespace advcpp








#endif //__AGENT_H__

