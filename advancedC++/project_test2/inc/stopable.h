#ifndef __STOPABLE_H__
#define __STOPABLE_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file stopable.h
//  @brief  
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

interface Stopable
{
	virtual
	~Stopable() {}

	virtual
	void Stop() =0;
	
};


typedef std::tr1::shared_ptr<Stopable> Stopable_sp;

}







#endif //__STOPABLE_H__

