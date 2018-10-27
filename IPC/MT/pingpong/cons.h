
#ifndef __CONS_H__
#define __CONS_H__

/** 
 *  @file cons.h
 *  @brief Message consumer
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#include "waitQueue.h"

#define CONS_STOPED +1

typedef struct Consumer Consumer;



Consumer* Consumer_Create(WaitQueue* _msgQueue, WaitQueue* _ackQueue, int _id);


void Consumer_Destroy(Consumer* _cons);


int Consumer_RecieveAndAck(Consumer* _cons);


int Consumer_StopThemAll(Consumer* _cons);



#endif /*__CONS_H__*/


















