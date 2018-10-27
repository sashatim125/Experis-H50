#ifndef __LOGCONFIG_H__
#define __CONFIGURATION_H__

// 
//  @file logConfig.h
//  @brief Configuration file info for a zlog4cpp
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include <vector>

#include "iniFileParser.h"

namespace advcpp
{

#define LOGLEVELSLIST \
	X(LOG_TRACE),	/**< Trace message usually very detailed			*/\
	Y(LOG_DEBUG),	/**< A message useful for debugging					*/\
	Y(LOG_INFO),	/**< Informative message							*/\
	Y(LOG_WARNING),	/**< Warning										*/\
	Y(LOG_ERROR),	/**< An error occurred								*/\
	Y(LOG_CRITICAL),/**< Critical error									*/\
	Y(LOG_SEVERE),	/**< Server error requiring immediate intervention	*/\
	Y(LOG_FATAL),	/**< Fatal error signaling an emergency				*/\
	Y(LOG_NONE)		/**< Used only in configuration file				*/


struct LogConfig
{	
	//throw runtime_error on wrong and or missing mandatory section(s)
	explicit
	LogConfig(const IniFileSection& _section);
	
	void SetConfiguration(const IniFileSection& _section);

	std::string m_name;	//mandatory

	int			m_level;//mandatory
	
	std::string m_path;	//mandatory
	
	static
	const std::vector<std::string> LogLevelsNames;
};







}
#endif //__LOGCONFIG_H__

