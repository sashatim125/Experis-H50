
// 
//  @file logConfig.cpp
//  @brief Configuration file info for a zlog4cpp
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include <sstream>
#include <stdexcept>

#include "logConfig.h"

using namespace advcpp;

#define X(arg) #arg
#define Y(arg) #arg
static
const char* __LogLevelsNames[] = {LOGLEVELSLIST};
#undef X
#undef Y

const std::vector<std::string> LogConfig::LogLevelsNames(__LogLevelsNames,
	__LogLevelsNames + sizeof(__LogLevelsNames)/sizeof(char*));


LogConfig::LogConfig(const IniFileSection& _section)
{
	SetConfiguration(_section);
}

void LogConfig::SetConfiguration(const IniFileSection& _section)
{
	const std::map<std::string, std::string>& confMap = _section.m_varValPairs;
	std::map<std::string, std::string>::const_iterator it;
	std::map<std::string, std::string>::const_iterator end =
		confMap.end();
	std::vector<std::string>::const_iterator levelsListEnd = LogLevelsNames.end();
	bool isOK = true;
	
	m_name = _section.m_sectionTitle;
	
	do
	{
		if(confMap.size() != 3)
		{
			isOK = false;
			break;
		}
	
		if(end == (it = confMap.find("Level")))
		{
			isOK = false;
			break;
		}
		int i=0 ;
		int vecSize = int(LogLevelsNames.size());
		for( ;i < vecSize; ++i)
		{
			if((*it).second == LogLevelsNames[i])
			{
				m_level = i;
				break;
			}
		}
		if(i >= vecSize)
		{
			isOK = false;
			break;
		}
		
		if(end == (it = confMap.find("Path")))
		{
			isOK = false;
			break;
		}
		std::ostringstream os;
		os<< (*it).second <<"/";
		
		if(end == (it = confMap.find("File")))
		{
			isOK = false;
			break;
		}
		os<< (*it).second;
		m_path = os.str();

	}while(false);
	
	if(!isOK)
	{
		std::ostringstream os;
		os<<"Error in config section "<<m_name<<" missing and/or wrong fields! "<<std::endl;
		throw std::runtime_error(os.str());
	}
}


