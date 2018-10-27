
// 
//  @file agentsLoader.cpp
//  @brief Agent Interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "agentsLoader.h"


namespace advcpp
{

AgentsLoader::AgentsLoader(const std::string& _soFilePath)
{
	if(0 == (m_fileHandler = dlopen(_soFilePath.c_str(), RTLD_LAZY)))
	{
		throw std::runtime_error("Can't open the file :"+_soFilePath);
	}
	
	ModelsFactory*(*GetFactory)();
	
//	*(void **)(&GetFactory) = dlsym(m_fileHandler,"GetModelsFactory");
	GetFactory = reinterpret_cast<ModelsFactory* (*)()>(dlsym(m_fileHandler,"GetModelsFactory"));
	
	const char* dlsym_error = dlerror();
	if (dlsym_error) 
	{
		dlclose(m_fileHandler);
		throw std::runtime_error("Wrong file type :"+std::string(dlsym_error));
    }
    
    m_modelsFactory = GetFactory();
}


AgentsLoader::~AgentsLoader()
{
	delete m_modelsFactory;
	dlclose(m_fileHandler);
}


Agent* AgentsLoader:: CreateAgent
	(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	return m_modelsFactory->CreateAgent(_config, _r, _er);
}


void AgentsLoader::DestroyAgent(Agent* _a)
{
	m_modelsFactory->DestroyAgent(_a);
}


void AgentsLoader::GetModelsTypes(std::list<std::string>& _typesList)
{
	m_modelsFactory->GetModelsTypes(_typesList);
}


}//endof namespace advcpp





