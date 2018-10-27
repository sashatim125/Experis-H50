
#ifndef __PROD_H__
#define __PROD_H__

/** 
 *  @file prod.h
 *  @brief Message producer
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include "waitQueue.h"


typedef struct Producer Producer;


Producer* Producer_Create(WaitQueue* _msgQueue, WaitQueue* _ackQueue, int _id);


void Producer_Destroy(Producer* _prod);


int Producer_SendMsg(Producer* _prod, void *_msg);


int Producer_ReceiveAck(Producer* _prod);


#endif /*__PROD_H__*/





