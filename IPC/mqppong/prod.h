
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



typedef struct Producer Producer;

/*_id > 0*/

Producer* prodCreate(int _msgQueue, int _ackQueue, int _sem, int _id);

void prodDestroy(Producer* _prod);


int prodStart(Producer* _prod);


int prodFinish(Producer* _prod);


int prodSendMsg(Producer* _prod, const char *_msgTxt);



int receiveAck(Producer* _prod);


#endif /*__PROD_H__*/





