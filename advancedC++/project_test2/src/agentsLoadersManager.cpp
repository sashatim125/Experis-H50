
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

using namespace advcpp;


AgentsLoadersManager::AgentsLoadersManager(const std::string& _agentsLibDir)
:	m_unusedAgentsLoadersReleased(false)
{
	std::vector<std::string> agentsSOFileNames;
	ReadDir(_agentsLibDir, agentsSOFileNames);
	
	{
		size_t i=0, vecSize = agentsSOFileNames.size();
		for(; i < vecSize ; ++i)
		{
			std::ostringstream oss;
			oss<<_agentsLibDir<<"/"<<agentsSOFileNames[i];
			AgentsLoader* alPtr = new AgentsLoader(oss.str());
			/*temp*/m_agentsLoaders.push_back(AgentsLoader_sp(alPtr));		
		}
	}
}

void AgentsLoadersManager::ReleaseUnusedAgentsLoaders()
{
	std::set<AgntLoadrIter>::const_iterator it = m_usedAgentsLoaders.begin();
	std::set<AgntLoadrIter>::const_iterator endIt = m_usedAgentsLoaders.end();
	for(; it !=  endIt; ++it)
	{
		m_agentsLoaders.erase(*it);
	}
	
	m_usedAgentsLoaders.clear();
	m_unusedAgentsLoadersReleased = true;	
}



	
Runnable_sp AgentsLoadersManager::CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er)
{
	if(m_unusedAgentsLoadersReleased)
	{
		return Runnable_sp();
	}

	AgntLoadrIter it = m_agentsLoaders.begin() , end  = m_agentsLoaders.end();
	for(; it != end ; ++it)
	{
		Agent* agentPtr = (*it)->CreateAgent(_config,_r,_er);
		if(0 != agentPtr)
		{
			m_usedAgentsLoaders.insert(it);
			return Runnable_sp(agentPtr,AgentsDeleter(*(*it)));
		}
	}
	
	return Runnable_sp();	
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











