#ifndef __CONFIGURATIONMAKER_H__
#define __CONFIGURATIONMAKER_H__

// 
//  @file configurationMaker.h
//  @brief Configuration list maker for agent's config
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <string>

#include "configuration.h"
#include "DBConnection.h"

namespace advcpp
{

class ConfigurationMaker
{
public:

	//throws runtime_error on wrong dir
	explicit
	ConfigurationMaker(const std::string& _iniDir);
	
	//throws runtime_error on wrong configuration
	explicit
	ConfigurationMaker(const DBConnectionConfig& _config);
	
	const std::list<Configuration>& GetConfigList() const;
	
private:

	std::list<Configuration> m_configList;


};

}//endof namespace advcpp






#endif //__CONFIGURATIONMAKER_H__

