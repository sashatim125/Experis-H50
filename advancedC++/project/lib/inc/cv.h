
#ifndef __CV_H__
#define __CV_H__


//
//  @file cv.h
//  @brief Posix conditional variable wrapper
//	
//  @details  see comments
// 
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


extern "C"
{
#include <pthread.h>
#include <errno.h>
}

#include <string>
#include <stdexcept>

#include "mutex.h"

namespace advcpp
{

	class CVError : public std::runtime_error
	{
	public:
		
		CVError(const std::string& _whatArg, int _errNum) :
			std::runtime_error(_whatArg), m_errNum(_errNum) 
		{}
			
		int ErrNum()const
		{return m_errNum;}
			
		private:
		int m_errNum;	
	};
	
	class CVWaitError : public CVError
	{
	public:
		explicit
		CVWaitError(int _errNum) :
			CVError("cv wait error",_errNum)
		{}
	};
	
	class CVWaitTimedoutError : public CVError
	{
	public:
		explicit
		CVWaitTimedoutError(int _errNum) :
			CVError("cv wait timedout",_errNum)
		{}
	};

//conditional varable class
class CV
{
public:

	//create default cv
	CV(Mutex& _m);
	
	//unsafe if there are waiting threads
	~CV() ;
	
	typedef bool(*Predicate)(void*);
	
//	void Wait(Predicate _p, void* _cntxt) throw(CVWaitError) ;

	template<class Functor>
	void Wait(Functor& _f) throw(CVWaitError) ;

//	void TimedWait(Predicate _p, void* _cntxt, const timespec& _abstime) throw(CVWaitError, CVWaitTimedoutError) ;

	template<class Functor>
	void TimedWait(Functor& _f, const timespec& _abstime) throw(CVWaitError, CVWaitTimedoutError) ;
	
	void Signal() throw();
	
	void Broadcast() throw();

protected:
	
private:
	//uncopyable objects
	CV(const CV& _m);
	CV& operator=(const CV& _m);
	
	pthread_cond_t m_cv;
	
	Mutex& m_mutex;
};



template<class Functor>
void CV::Wait(Functor& _f) throw(CVWaitError)
{
	int err;
	
	while(_f())
	{
		if(0!= (err= pthread_cond_wait(&m_cv, m_mutex.GetPthreadMutexPtr())))
		{
			throw CVWaitError(err);
		}
	}
}

template<class Functor>
void CV::TimedWait(Functor& _f, const timespec& _abstime) throw(CVWaitError, CVWaitTimedoutError) 
{
	int err=0;
	bool wasTimedout = false;
	
	while(_f())
	{
		if(wasTimedout)
		{
			//m_mutex.Unlock();
			throw CVWaitTimedoutError(err);
		}
		if(0!= (err= pthread_cond_timedwait(&m_cv, m_mutex.GetPthreadMutexPtr(), &_abstime)))
		{
			if(ETIMEDOUT == err)
			{
				wasTimedout = true;
				continue;
			}else
			{
			 throw CVWaitError(err);
			}
		}
	}
}
















}
#endif //__CV_H__

