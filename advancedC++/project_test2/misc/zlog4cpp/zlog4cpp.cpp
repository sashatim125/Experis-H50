
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


extern "C"
{
#include <unistd.h>		//getpid()
#include <pthread.h>
#include <sys/syscall.h>//gettid()
//using C code for formated timestamp
#include <sys/time.h>	//""
#include <string.h> 	//""
#include <stdio.h>		//""
}
#include <iomanip>

#include "zlog4cpp.h"

using namespace advcpp;

std::map<std::string, Zlog*> Zlog::s_logs;

Zlog::Zlog(const LogConfig& _config)
:	m_config(_config)
{
	if(s_logs.find(m_config.m_name) != s_logs.end())
	{
		std::ostringstream os;
		os<<"The log "<<m_config.m_name<<" already exists!"<<std::endl;
		throw std::runtime_error(os.str());
	}

	m_logFile.open(m_config.m_path.c_str(), std::ofstream::out | std::ofstream::app);
	
	if(!m_logFile.good())
	{
		std::ostringstream os;
		os<<"Wrong file name/permissions : "<<m_config.m_path<<std::endl;
		throw std::runtime_error(os.str());
	}
	
	s_logs[m_config.m_name] = this;
	
	ZLOG(*this, m_config.m_name, LOG_FATAL,"Log started!");
}
	
Zlog::~Zlog()
{
	try
	{
		ZLOG(*this, m_config.m_name, LOG_FATAL,"Log finished.");
	}catch(...)
	{}
	
	m_logFile.close();
	
	s_logs.erase(m_config.m_name);
}

static long GetCurrentThreadIdInProcess()
{
	return (syscall(SYS_gettid)-getpid()+1);
}

void Zlog::RecordToLog(const std::string& _module, LogLevels _logLevel,
		const std::string& _fileDetails, const std::string& _freeText)
{
	MutexGuard mg(m_mutex);
	
	if(_logLevel < m_config.m_level || LOG_NONE == m_config.m_level)
	{
		return;
	}
	
	m_logFile << "\n"<<GetTimeStamp()<<" ";
	m_logFile << getpid()<<" ";
	m_logFile << std::right<<std::setw(3)<<GetCurrentThreadIdInProcess()<<" ";
	m_logFile << GetLevelChar( _logLevel)<<" ";	
	m_logFile << _module<<" ";
	m_logFile << _fileDetails;
	m_logFile << _freeText <<std::endl;
}

void Zlog::Clear()
{
	MutexGuard mg(m_mutex);
	
	m_logFile.close();
	m_logFile.open(m_config.m_path.c_str(), std::ofstream::out | std::ofstream::trunc);
	
	if(!m_logFile.good())
	{
		std::ostringstream os;
		os<<"Can't clear the file content : "<<m_config.m_path<<std::endl;
		throw std::runtime_error(os.str());
	}
}

const LogConfig& Zlog::GetConfig() const
{
	return m_config;
}
	
const std::string& Zlog::GetName() const
{
	return m_config.m_name;
}

std::string Zlog::GetTimeStamp()
{
	char strBuff[128];
	struct tm *tms;
	struct timeval tv;
	
	gettimeofday(&tv,NULL);
	tms = localtime(&(tv.tv_sec));
	strftime(strBuff, 128, "%F %X", tms);

	sprintf(strBuff+strlen(strBuff),".%03ld ",tv.tv_usec/1000);
	
	return std::string(strBuff);	
}
	
char Zlog::GetLevelChar(LogLevels _logLevel)
{
	return LogConfig::LogLevelsNames[_logLevel][4];
}	

Zlog* Zlog::GetLog(const std::string& _name)
{
	std::map<std::string, Zlog*>::iterator it;
	return ((it = s_logs.find(_name)) != s_logs.end()) ? 
			(it->second) : 0;
}

