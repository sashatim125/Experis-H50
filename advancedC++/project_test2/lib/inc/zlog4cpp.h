#ifndef __ZLOG4CPP_H__
#define __ZLOG4CPP_H__

// 
//  @file zlog4cpp.h
//  @brief ZLOG for C++ (thread safe)
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//



#include <fstream>
#include <sstream>
#include <map>
#include <tr1/memory>

#include "logConfig.h"
#include "mutex.h"

namespace advcpp
{

#ifndef NDEBUG
	#define GET_FILE_DETAILS \
		__func__<<"@"__FILE__<<":"<<__LINE__<<" "

#else 
	#define GET_FILE_DETAILS " "

#endif //#ifndef NDEBUG

//////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////MAIN MACRO////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
//Usage:
//ZLOG(Zlog& LOGGER, const std::string& MODULE, LogLevels LOG_LEVEL, const std::string& FREE_TEXT);
//////////////////////////////////////////////////////////////////////////////////////////////////


#define ZLOG(LOGGER, MODULE, LOG_LEVEL, FREE_TEXT) do\
{\
	std::ostringstream os;\
	os<<GET_FILE_DETAILS;\
	(LOGGER).RecordToLog((MODULE), (LOG_LEVEL), os.str(), (FREE_TEXT));\
}while(false)

/////////////////LOG LEVELS LIST/////////////////////////////////////////
//	LOG_TRACE		< Trace message usually very detailed			
//	LOG_DEBUG		< A message useful for debugging					
//	LOG_INFO		< Informative message							
//	LOG_WARNING		< Warning										
//	LOG_ERROR		< An error occurred								
//	LOG_CRITICAL	< Critical error									
//	LOG_SEVERE		< Server error requiring immediate intervention	
//	LOG_FATAL		< Fatal error signaling an emergency				
//	LOG_NONE		< Used only in configuration file				
////////////////////////////////////////////////////////////////////////

class Zlog;
typedef std::tr1::shared_ptr<Zlog> Zlog_sp;

class Zlog
{
public:

#define X(arg) arg=0
#define Y(arg) arg
	enum LogLevels {LOGLEVELSLIST};
#undef X
#undef Y

	//throw runtime_error if wrong file name/permissions
	//or if such log already exist
	explicit
	Zlog(const LogConfig& _config);

	~Zlog();

//DO NOT call directly , can result in wrong log record
	void RecordToLog(const std::string& _module, LogLevels _logLevel,
		const std::string& _fileDetails, const std::string& _freeText);

	//throw runtime_error if unsuccessful
	void Clear();

	const LogConfig& GetConfig() const;

	const std::string& GetName() const;
	
	//Get existing log by the name
	//return Zlog_sp(0) if such log does not exist
	static
	Zlog* GetLog(const std::string& _name);


private:
	Zlog(const Zlog&);
	Zlog& operator=(const Zlog&);

	std::ofstream m_logFile;
	Mutex m_mutex;
	LogConfig m_config;
	
	static
	std::map<std::string, Zlog*> s_logs;
	
	static inline
	std::string GetTimeStamp();
	
	static inline
	char GetLevelChar(LogLevels _logLevel);	
};




}



#endif //__ZLOG4CPP_H__


