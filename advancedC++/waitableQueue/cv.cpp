
//
//  @file cv.cpp
//  @brief Posix conditional variable wrapper
//	
//  @details  see comments
// 
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//


#include "cv.h"

using namespace advcpp;

CV::CV(Mutex& _m):
	m_mutex(_m)
{
	pthread_cond_init(&m_cv,0);

}

CV::~CV()
{
	pthread_cond_destroy(&m_cv);
}

void CV::Signal() throw()
{
	pthread_cond_signal(&m_cv);
}
	
void CV::Broadcast() throw()
{
	pthread_cond_broadcast(&m_cv);
}
























