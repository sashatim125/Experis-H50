

// 
//  @file logsHolder.cpp
//  @brief Logs Holder
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "logsHolder.h"

namespace advcpp
{


LogsHolder::LogsHolder(const std::string& _iniDir)
{
	IniFileParser logsParser(_iniDir+"/log_config.ini");
	const std::map<std::string, IniFileSection>& logSections =
		logsParser.GetIniSections();
	{
		std::map<std::string, IniFileSection>::const_iterator it = logSections.begin();
		std::map<std::string, IniFileSection>::const_iterator endIt = logSections.end();
		for (;it != endIt ; ++it)
		{
			LogConfig logConf(it->second);
			m_logs.push_back(Zlog_sp(new Zlog (logConf)));
		}
	}
}



}//endof namespace advcpp






