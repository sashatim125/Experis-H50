#ifndef __PTHREAD_H__
#define __PTHREAD_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file pthread_class.h
//  @brief PThread (posix thread) 
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <string>

extern "C"
{
#include <pthread.h>
}
#include "runnable.h"
#include "mutex.h"

namespace advcpp
{


//shared pointer to PThread
class PThread;
typedef std::tr1::shared_ptr<PThread> PThread_sp;

//This class IS NOT intended to be inherited !
class PThread
{
public:

	explicit
	PThread(Runnable_sp _runnable);

	PThread(Runnable_sp _runnable, const std::string& _name);

//the DCTOR CANCELS the thread!
	~PThread();

//throw runtime_error if can't start the thread
//like no more resources or reached the limit 
//on the total number of threads in a process 
	void Start();

//DO NOT call if not started by Start()	
//throw runtime_error
	void Join();

//DO NOT call if not started by Start()	
//throw runtime_error
	void Cancel();
	
	const std::string& GetName() const;
	
	Runnable_sp GetRunnable() const;

private:
	//uncopyable objects
	PThread(const PThread& _pt);
	const PThread& operator= (const PThread& _pt);
	
	Runnable_sp m_runnable;
	
	std::string m_name;
	
	pthread_t m_pthread;
	
	bool m_isStarted;
	Mutex m_mutex; //to guard m_isStarted
	
	static void* StartRoutine(void* _cntxt);
};


}//endof namespace advcpp










#endif //__PTHREAD_H__

