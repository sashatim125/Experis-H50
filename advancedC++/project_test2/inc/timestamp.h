#ifndef __TIMESTAMP_H__
#define __TIMESTAMP_H__

// 
//  @file timestamp.h
//  @brief Timestamp
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

extern "C"
{
#include <sys/time.h>	
#include <string.h> 	
#include <stdio.h>	
}

//this class IS NOT thread safe !
class Timestamp
{
public:

	inline
	Timestamp();
	
	inline
	void SetTime();

	inline
	struct timeval GetTime() const;
	
	inline
	std::string ToString() const;
	
private:

	struct timeval m_time;
};


inline
Timestamp::Timestamp()
{
	SetTime();
}

inline
void Timestamp::SetTime()
{
	gettimeofday(&m_time,NULL);
}

inline
std::string Timestamp::ToString() const
{
	char strBuff[128];
	struct tm *tms;

	tms = localtime(&(m_time.tv_sec));
	strftime(strBuff, 128, "%F %X", tms);

	sprintf(strBuff+strlen(strBuff),".%03ld ",m_time.tv_usec/1000);
	
	return std::string(strBuff);
}











#endif //__TIMESTAMP_H__
