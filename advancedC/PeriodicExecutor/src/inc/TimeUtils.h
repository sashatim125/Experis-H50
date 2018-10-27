#ifndef __TIME_UTILS_H__
#define __TIME_UTILS_H__

/** 
 *  @file TimeUtils.h
 *  @brief Definitions of the usefull time utilities
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */

#include <sys/time.h>
#include <stddef.h>


typedef struct timespec Timespec;


/** 
 * @brief calculate the time elapsed from _begin to _end
 * @details can be positive(on both sec and nsec) or negative (on both sec and nsec)
 *			or one or both sec and nsec can be 0.
 * 
 * @params[in] _begin 	start time
 * @params[in] _end		end time
 *
 * @returns the time elapsed from _begin to _end
 * @warning can be negative
 * @warning provide correct times as parameters !
 */
Timespec TimeDiff(Timespec _begin,Timespec _end);

/** 
 * @brief calculate the time after _delay_ms milliseconds from the time _begin
 * 
 * @params[in] _begin 		start time
 * @params[in] _delay_ms	delay in milliseconds
 *
 * @returns ime after _delay_ms milliseconds from the time _begin
 * @warning provide correct time as parameters !
 */
Timespec TimeAfterDelay(Timespec _begin,size_t _delay_ms);


/** 
 * @brief checks if _t1 is LATER then _t2
 * 
 * @params[in] _begin 	start time
 * @params[in] _end		end time
 *
 * @returns !=0 if _t1 is LATER then _t2, 0 - otherwise
 * @warning provide correct times as parameters !
 */
int IsLater(Timespec _t1,Timespec _t2);









#endif /*__TIME_UTILS_H__*/
