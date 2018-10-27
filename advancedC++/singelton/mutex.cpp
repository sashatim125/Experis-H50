

#include "mutex.h"

//
//  @file mutex.cpp
//  @brief Posix mutex wrapper
//	
//  @details  see comments
// 
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


using namespace advcpp;

void Mutex::Ctor(Type _t)
{
	pthread_mutexattr_init(&m_attr);

	pthread_mutexattr_settype(&m_attr,_t);
	
	pthread_mutex_init(&m_mutex,&m_attr);
}

Mutex::Mutex()
{
	Ctor(mutex_default_t);
}
	
	
Mutex::Mutex(Type _t)
{
	Ctor(_t);
}


Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_mutexattr_destroy(&m_attr);
}


void Mutex::Lock()  throw(MutexLockError)
{
	int err;
	
	if(0!= (err= pthread_mutex_lock(&m_mutex)))
	{
		throw MutexLockError(err);
	}
}


void Mutex::TryLock()  throw(MutexLockError)
{
	int err;
	
	if(0!= (err= pthread_mutex_trylock(&m_mutex)))
	{
		throw MutexLockError(err);
	}
}


void Mutex::Unlock()  throw(MutexUnlockError)
{
	int err;
	
	if(0!= (err= pthread_mutex_unlock(&m_mutex)))
	{
		throw MutexUnlockError(err);
	}
}

pthread_mutex_t* Mutex::GetPthreadMutexPtr()
{
	return &m_mutex;
}










