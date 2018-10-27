
#ifndef __MUTEX_H__
#define __MUTEX_H__

//
//  @file mutex.h
//  @brief Posix mutex wrapper
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
}

#include <string>
#include <stdexcept>

namespace advcpp
{
//Class Mutex Exceptions
	class MutexError : public std::runtime_error
	{
	public:
		
		MutexError(const std::string& _whatArg, int _errNum) :
			std::runtime_error(_whatArg), m_errNum(_errNum) 
		{}
			
		int ErrNum()const
		{return m_errNum;}
			
	private:
		int m_errNum;	
	};
	
	class MutexLockError : public MutexError
	{
	public:
		explicit
		MutexLockError(int _errNum) :
			MutexError("mutex lock error",_errNum)
		{}
	};
	
	class MutexUnlockError : public MutexError
	{
	public:
		explicit
		MutexUnlockError(int _errNum) :
			MutexError("mutex unlock error",_errNum)
		{}
	};


class Mutex
{
	friend class CV;
	
public:
	
	enum Type
	{
		mutex_normal_t		= PTHREAD_MUTEX_NORMAL,
		mutex_errorcheck_t	= PTHREAD_MUTEX_ERRORCHECK,
		mutex_recursive_t	= PTHREAD_MUTEX_RECURSIVE,
		mutex_default_t		= PTHREAD_MUTEX_DEFAULT
	};
	
	//create default mutex
	Mutex() ;
	
	explicit
	Mutex(Type _t) ;
	
	//unsafe if not unlocked
	~Mutex() ;
	
	void Lock() throw(MutexLockError) ;

	void TryLock() throw(MutexLockError) ;

	void Unlock()  throw(MutexUnlockError) ;

protected:
	
private:
	//uncopyable objects
	Mutex(const Mutex& _m);
	Mutex& operator=(const Mutex& _m);
	
	pthread_mutexattr_t m_attr;
	
	pthread_mutex_t m_mutex;
	
	//for friends only
	pthread_mutex_t* GetPthreadMutexPtr();
	
	void Ctor(Type _t) ;
};


class MutexGuard
{

public:
	inline
	MutexGuard(Mutex& _m);
	
	inline
	~MutexGuard();
private:
	Mutex& m_mutex;	
};


inline
MutexGuard::MutexGuard(Mutex& _m):
	m_mutex(_m)
{
	m_mutex.Lock();
}

inline
MutexGuard::~MutexGuard()
{
	m_mutex.Unlock();
}















}
#endif //__MUTEX_H__




