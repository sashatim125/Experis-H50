
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


typedef struct Consumer Consumer;

/*_id > 0*/
Consumer * consCreate(int _msgQueue, int _ackQueue, int _sem, int _id);



void consDestroy(Consumer* _cons);



int recieveAndAck(Consumer* _cons);






#endif /*__CONS_H__*/





