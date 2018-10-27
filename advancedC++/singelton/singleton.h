#ifndef __SINGLTON_H__
#define __SINGLTON_H__

#include "mutex.h"


namespace advcpp
{


template <class T>
class Singleton
{
public:

	static T& Instance();

protected:
	Singleton() {}
	virtual	~Singleton() {delete s_instance;}

private:
	Singleton(const Singleton& _other);
	Singleton& operator=(const Singleton& _other);

	static T* s_instance;
	static Mutex s_mutex;
};

template <class T>
T* Singleton<T>::s_instance = 0;

template <class T>
Mutex Singleton<T>::s_mutex;


void MemoryBarrier()
{
	__sync_synchronize();
}

template <class T>
T& Singleton<T>::Instance()
{
	MemoryBarrier();
	if(0 == s_instance)
	{
		MutexGuard mg(s_mutex);
		{
			if(0 == s_instance)
			{
				s_instance = new T;
				MemoryBarrier();
			}
		}
	}
	return *s_instance;
}




} //namespace advcpp
#endif //__SINGLTON_H__

