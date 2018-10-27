#ifndef __SETUPCONFIG_H__
#define __SETUPCONFIG_H__

// 
//  @file setupConfig.h
//  @brief Configuration info for the setup
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <string>

#include "DBConnection.h"

namespace advcpp
{

struct SetupConfig
{
	inline
	SetupConfig(
		const std::string& _iniDir,
		const std::string& _agentsLibDir,
		size_t _numOfInDispatchers,
		size_t _numOfOutDispatchers,
		const DBConnectionConfig* _config,
		bool _useDB);
	
	const std::string& m_iniDir;
	const std::string& m_agentsLibDir;
	size_t m_numOfInDispatchers;
	size_t m_numOfOutDispatchers;
	const DBConnectionConfig* m_config;
	bool m_useDB;
};

}
using advcpp::SetupConfig;

inline
SetupConfig::SetupConfig(
	const std::string& _iniDir,
	const std::string& _agentsLibDir,
	size_t _numOfInDispatchers,
	size_t _numOfOutDispatchers,
	const DBConnectionConfig* _config,
	bool _useDB)
:	m_iniDir(_iniDir)
,	m_agentsLibDir(_agentsLibDir)
,	m_numOfInDispatchers(_numOfInDispatchers)
,	m_numOfOutDispatchers(_numOfOutDispatchers)
,	m_config(_config)
,	m_useDB(_useDB)
{}





#endif //__SETUPCONFIG_H__

