

// 
//  @file pthread_class.cpp
//  @brief PThread (posix thread) 
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <sstream>
#include <stdexcept>

#include "pthread_class.h"

namespace advcpp
{

void* PThread::StartRoutine(void* _cntxt)
{
	PThread* thread = static_cast<PThread*>(_cntxt);
	
	thread->m_runnable->Run();
	
	return 0;
}

PThread::PThread(Runnable_sp _runnable)
:	m_runnable(_runnable)
,	m_isStarted(false)
{}

PThread::PThread(Runnable_sp _runnable, const std::string& _name)
:	m_runnable(_runnable)
,	m_name(_name)
,	m_isStarted(false)
{}

PThread::~PThread()
{	
	if(m_isStarted)
	{
		pthread_cancel(m_pthread);
	}
}

void PThread::Start()
{
	MutexGuard mg(m_mutex);
	
	if(m_isStarted || 0 != pthread_create(&m_pthread,0,StartRoutine,this))
	{
		std::ostringstream os;
		os<<"Thread "<<m_name<<" can't be started!"<<std::endl;
		throw std::runtime_error(os.str());
	}
	
	m_isStarted = true;
}

void PThread::Join()
{
	MutexGuard mg(m_mutex);
	
	if(!m_isStarted || 0 != pthread_join(m_pthread, 0))
	{
		std::ostringstream os;
		os<<"Thread "<<m_name<<" can't be joined!"<<std::endl;
		throw std::runtime_error(os.str());
	}
	
	m_isStarted = false;
}

void PThread::Cancel()
{
	MutexGuard mg(m_mutex);
	
	if(!m_isStarted || 0 != pthread_cancel(m_pthread))
	{
		std::ostringstream os;
		os<<"Thread "<<m_name<<" can't be canceled!"<<std::endl;
		throw std::runtime_error(os.str());
	}
	
	m_isStarted = false;
}

const std::string& PThread::GetName() const
{
	return m_name;
}


	
Runnable_sp PThread::GetRunnable() const
{
	return m_runnable;
}


}//endof namespace advcpp






