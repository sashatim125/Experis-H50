#ifndef __AGENTSLOADER_H__
#define __AGENTSLOADER_H__

// 
//  @file agentsLoader.h
//  @brief Agents loader(from .so file)
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

extern "C"
{
#include <dlfcn.h>
}

#include <string>
#include <stdexcept>

#include "modelsFactory.h"

namespace advcpp
{

class AgentsLoader
:	public ModelsFactory
{
public:

	//throws runtime_error on wrong file's name/type
	explicit
	AgentsLoader(const std::string& _soFilePath);

	~AgentsLoader();
	
	//returns 0 if no such type
	virtual
	Agent* CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
	
	virtual
	void DestroyAgent(Agent*);

private:

	void* m_fileHandler;
	
	ModelsFactory* m_modelsFactory;
};


//Use with shared_ptr to be called from PThread
class AgentsDeleter
{
public:
	AgentsDeleter(AgentsLoader& _al)
	:	m_al(_al)
	{}
	
	void operator()(Runnable* _agent)
	{
		m_al.DestroyAgent(static_cast<Agent*>(_agent));
	}
	
private:
	AgentsLoader& m_al;
};

}











#endif //__AGENTSLOADER_H__

