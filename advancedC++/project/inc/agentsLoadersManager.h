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
private:
	typedef std::tr1::shared_ptr<AgentsLoader> AgentsLoader_sp;
//	typedef std::vector<AgentsLoader_sp>::iterator AgntLoadrIter;

public:

	//throws runtime_error on wrong file's name/type/permission
	explicit
	AgentsLoadersManager(const std::string& _agentsLibDir);

//	~AgentsLoader();
	
	//returns Runnable_sp() (with 0 inside) if no such type
	//or if ReleaseUnusedAgentsLoaders was called
	Runnable_sp CreateAgent
		(const Configuration& _config, Registrator* _r, EventsReceiver* _er);
	
	void ReleaseUnusedAgentsLoaders();

private:
	//uncopyable objects
	AgentsLoadersManager(const AgentsLoadersManager&);
	AgentsLoadersManager& operator=(const AgentsLoadersManager&);

	std::map<std::string, AgentsLoader_sp> *m_typesLoadersMap;
	
	std::vector<AgentsLoader_sp> *m_tempAgentsLoaders;
	
	std::set<AgentsLoader_sp> m_usedAgentsLoaders;
	
	bool m_unusedAgentsLoadersReleased;
	
	//throw runtime_error if wrong _dirName
	static void ReadDir
		(const std::string& _dirName, std::vector<std::string>& _fileNames);
};

}//endof namespace advcpp











#endif //__AGENTSLOADERMANAGER_H__

