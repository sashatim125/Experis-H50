#ifndef __AGENTSLOADERMANAGER_H__
#define __AGENTSLOADERMANAGER_H__

// 
//  @file agentsLoadersManager.h
//  @brief Agents Loaders Manager
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "agentsLoader.h"
#include <vector>
#include <set>

namespace advcpp
{

class AgentsLoadersManager
{
public:

	//throws runtime_error on wrong file's name/type
	explicit
	AgentsLoadersManager(const std::string& _agentsLibDir);

//	~AgentsLoader();
	
	//returns Runnable_sp() (with 0 inside) if no such type
	//or if ReleaseUnusedAgentsLoaders was called
	Runnable_sp CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
	
	void ReleaseUnusedAgentsLoaders();

private:
	AgentsLoadersManager(const AgentsLoadersManager&);
	AgentsLoadersManager& operator=(const AgentsLoadersManager&);


	typedef std::tr1::shared_ptr<AgentsLoader> AgentsLoader_sp;
	
	std::vector<AgentsLoader_sp> m_agentsLoaders;
	
//	std::vector<AgentsLoader_sp> m_tempAgentsLoaders;
	typedef std::vector<AgentsLoader_sp>::iterator AgntLoadrIter;
	std::set<AgntLoadrIter> m_usedAgentsLoaders;
//	std::set<size_t> m_usedAgentsLoaders;
	bool m_unusedAgentsLoadersReleased;
	
	//throw runtime_error if wrong _dirName
	static
	void ReadDir(const std::string& _dirName, std::vector<std::string>& _fileNames);
};

}











#endif //__AGENTSLOADERMANAGER_H__

