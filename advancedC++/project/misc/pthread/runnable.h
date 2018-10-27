#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file runnable.h
//  @brief Runnable 
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <tr1/memory>

namespace advcpp
{

interface Runnable
{
	virtual
	~Runnable() {}

	virtual
	void Run() =0;
	
};


typedef std::tr1::shared_ptr<Runnable> Runnable_sp;

}//endof namespace advcpp











#endif //__RUNNABLE_H__

