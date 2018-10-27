
#ifndef __BARRIER_H__
#define __BARRIER_H__

/** 
 *  @file barrier.h
 *  @brief Barrier API
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h>

typedef struct Barrier Barrier;


Barrier* Barrier_Create(size_t _capacity);

void Barrier_Destroy(Barrier* _b);

int Barrier_Wait(Barrier* _b);



#endif /*__BARRIER_H__*/
