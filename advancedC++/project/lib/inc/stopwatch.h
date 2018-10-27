#ifndef __STOPWATCH_H__
#define __STOPWATCH_H__


//
//  @file stopwatch.h
//  @brief simple stopwatch 
//	
//  @details  see comments
// 
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

extern "C"
{
#include <time.h>
}

namespace advcpp
{

//millisec stopwatch
class Stopwatch
{
public:

	enum Clocktype
	{
		realtime_t			= CLOCK_REALTIME,
		monolotic_t			= CLOCK_MONOTONIC,
		process_cputime_id	= CLOCK_PROCESS_CPUTIME_ID,
		thread_cputime_id_t	= CLOCK_THREAD_CPUTIME_ID
	};

	//with REALTIME
	Stopwatch() : 
		m_ct(realtime_t)
	{
		Mark();
	}
	
	Stopwatch(Clocktype _ct) : 
		m_ct(_ct)
	{
		Mark();
	}
	
	void Mark()
	{
		clock_gettime(m_ct,&m_tMark);
	}
	
	//return time in ms from last mark
	inline
	long Stop();
private:

	Clocktype m_ct;
	timespec m_tMark;
	timespec m_tStop;
};

inline
long Stopwatch::Stop()
{
	clock_gettime(m_ct,&m_tStop);
	m_tStop.tv_sec -= m_tMark.tv_sec;
	m_tStop.tv_nsec -= m_tMark.tv_nsec;
	if(m_tStop.tv_nsec < 0)
	{
		-- m_tStop.tv_sec;
		m_tStop.tv_nsec+=1000000000;
	}
	
	return (m_tStop.tv_sec*1000 + m_tStop.tv_nsec/1000000);
}







}
#endif //__STOPWATCH_H__

