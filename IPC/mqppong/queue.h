
#ifndef __QUEUE_H__
#define __QUEUE_H__

/** 
 *  @file queue.h
 *  @brief Message queues
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#define KEY_FILE "mqpingpongkeyfile"

int getMsgQueue(void);


int getAckQueue(void);


int getSemaphore(void);





#endif /*__QUEUE_H__*/
