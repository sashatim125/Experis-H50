#ifndef __LOGSHOLDER_H__
#define __LOGSHOLDER_H__

// 
//  @file logsHolder.h
//  @brief Logs Holder
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include "zlog4cpp.h"

namespace advcpp
{

class LogsHolder
{
public:

	explicit
	LogsHolder(const std::string& _iniDir);

private:

	std::vector<Zlog_sp> m_logs;
};


}//endof namespace advcpp











#endif //__LOGSHOLDER_H__

