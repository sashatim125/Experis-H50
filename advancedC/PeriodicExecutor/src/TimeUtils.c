

/** 
 *  @file TimeUtils.c
 *  @brief Implementations of the usefull time utilities
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */

#include "TimeUtils.h"
#include <time.h>
#include <stddef.h>


Timespec TimeDiff(Timespec _begin,Timespec _end)
{
	double secDiff;
	long nsecDiff;
	Timespec diffTime;
	
	secDiff  = difftime(_end.tv_sec, _begin.tv_sec);
	nsecDiff = _end.tv_nsec - _begin.tv_nsec;
	
	if (0 < secDiff && 0 > nsecDiff)
	{
		secDiff-=1;
		nsecDiff+=(long)1e9;
	}
	if (0 > secDiff && 0 < nsecDiff)
	{
		secDiff+=1;
		nsecDiff-=(long)1e9;
	}

	diffTime.tv_sec = (time_t)secDiff;
	diffTime.tv_nsec = nsecDiff;
	
	return 	diffTime;
}


int IsLater(Timespec _t1,Timespec _t2)
{
	Timespec diffTime = TimeDiff(_t2,_t1);
	
	return 	(diffTime.tv_sec > 0 || diffTime.tv_nsec > 0);
}


Timespec TimeAfterDelay(Timespec _begin,size_t _delay_ms)
{
	_begin.tv_sec+=(long)(_delay_ms/1000+((_delay_ms%1000)*1000000)/1000000000);
	_begin.tv_nsec+=(long)(((_delay_ms%1000)*1000000)%1000000000);
	
	return _begin;
}




















