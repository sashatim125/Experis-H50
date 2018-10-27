
#ifndef __MSG_H__
#define __MSG_H__

/** 
 *  @file msg.h
 *  @brief Message utility functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h>

#define MESSAGE_BUFFER_SIZE 1024


int msgCreate(void* _newMsg, size_t* _newMsgTxtSize, int _prodId, const char* _msgTxt);




int msgAckCreate(void* _ackMsg, size_t* _ackMsgTxtSize, int* _prodId, const char* _msgTxt);






#endif /*__MSG_H__*/





