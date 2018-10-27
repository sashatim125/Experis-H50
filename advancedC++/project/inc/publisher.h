#ifndef __PUBLISHER_H__
#define __PUBLISHER_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file publisher.h
//  @brief Publisher interface
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

namespace advcpp
{

interface Publisher
{	
	virtual
	~Publisher() {}
	
	virtual
	void Publish(Event_sp _event) =0;
};

}//endof namespace advcpp
















#endif //__PUBLISHER_H__

