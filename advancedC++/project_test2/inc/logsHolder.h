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

	LogsHolder(const std::string& _iniDir);

private:

	std::vector<Zlog_sp> m_logs;
};


}











#endif //__LOGSHOLDER_H__

