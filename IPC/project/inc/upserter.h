
#ifndef __UPSERTER_H__
#define __UPSERTER_H__


/** 
 *  @file upserter.h
 *  @brief the upserter thread api
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#include "aggregator.h"
#include "subscrStorageManager.h"
#include "operStorageManager.h"


typedef struct UpserterParams
{
	int m_MsgQId;

	Aggregator* m_sagg;
	Aggregator* m_oagg;
	
	SubscrStorageManager*	m_ssm;
	OperStorageManager*		m_osm;

} UpserterParams;



/**  
 * @brief main function of the upserter thread
 * @param[in] _p parameters of the type UpserterParams*
 * @return (void*)0 if succsessful , other value otherwise
 */
void* Upserter(void* _p);










#endif /* __UPSERTER_H__ */







