
// 
//  @file agentsLoadersManager.cpp
//  @brief Agents Loaders Manager
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//



extern "C"
{
#include <sys/types.h>//dir_read
#include <dirent.h>
}

#include "agentsLoadersManager.h"

namespace advcpp
{


AgentsLoadersManager::AgentsLoadersManager(const std::string& _agentsLibDir)
:	m_typesLoadersMap(new std::map<std::string, AgentsLoader_sp>)
,	m_tempAgentsLoaders(new std::vector<AgentsLoader_sp>)
,	m_unusedAgentsLoadersReleased(false)
{
	std::vector<std::string> agentsSOFileNames;
	ReadDir(_agentsLibDir, agentsSOFileNames);

	size_t i=0, numOfSOFiles = agentsSOFileNames.size();
	m_tempAgentsLoaders->reserve(numOfSOFiles);
	
	std::list<std::string> typesList;
	
	for(; i < numOfSOFiles ; ++i)
	{
		std::ostringstream oss;
		oss<<_agentsLibDir<<"/"<<agentsSOFileNames[i];
		
		AgentsLoader_sp newAgentsLoader(new AgentsLoader(oss.str()));
		m_tempAgentsLoaders->push_back(newAgentsLoader);
		
		newAgentsLoader->GetModelsTypes(typesList);
		
		std::list<std::string>::iterator it = typesList.begin();
		std::list<std::string>::iterator end = typesList.end();
		for(; it != end; ++it)
		{
			(*m_typesLoadersMap)[*it] = newAgentsLoader;
		}
		typesList.clear();		
	}
}

void AgentsLoadersManager::ReleaseUnusedAgentsLoaders()
{
	if(not m_unusedAgentsLoadersReleased)
	{
		delete m_tempAgentsLoaders;
		delete m_typesLoadersMap;
		m_unusedAgentsLoadersReleased = true;
		
		//std::cout<<"num of open loaders "<<m_usedAgentsLoaders.size()<<std::endl;
	}
}



	
Runnable_sp AgentsLoadersManager::CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	if(m_unusedAgentsLoadersReleased)
	{
		return Runnable_sp();
	}

	std::map<std::string, AgentsLoader_sp>::iterator iter = m_typesLoadersMap->find(_config.m_type);	

	if (m_typesLoadersMap->end() == iter)
	{
		return Runnable_sp();
	}else
	{
		Runnable_sp newAgent((iter->second)->CreateAgent(_config,_r,_er), AgentsDeleter(*(iter->second)));

		if(0 != newAgent.get())
		{
			m_usedAgentsLoaders.insert(iter->second);
			
			return newAgent;
		}else
		{
			return Runnable_sp();
		}	
	}
}

void AgentsLoadersManager::ReadDir(const std::string& _dirName, std::vector<std::string>& _fileNames)
{
    DIR* dirp = opendir(_dirName.c_str());
    if(NULL == dirp)
    {
    	throw std::runtime_error("Wrong directory name for ReadDir!");
    }
    struct dirent * dp;
    
    while ((dp = readdir(dirp)) != NULL)
    {
    	if(0!= strcmp(dp->d_name, ".") && 0!= strcmp(dp->d_name, ".."))
    	{
        	_fileNames.push_back(dp->d_name);
        }
    }
    closedir(dirp);
}


}//endof namespace advcpp








