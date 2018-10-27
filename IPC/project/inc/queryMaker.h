
#ifndef __QUERY_MAKER_H__
#define __QUERY_MAKER_H__


/** 
 *  @file queryMaker.h
 *  @brief the query maker thread api
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


#include "commonStructs.h"
#include "aggregator.h"
#include "subscrStorageManager.h"
#include "operStorageManager.h"

typedef struct QueryMakerParams
{
	int m_MsgQId;
	
	long m_msgType;
	
	void* m_key;
	
	AggregatedDataType m_queryType;

	Aggregator* m_agg;
	
	void*	m_sm; /*<< storage manager*/

} QueryMakerParams;



/**  
 * @brief main function of the queryMaker thread
 * @param[in] _p parameters of the type QueryMakerParams*
 * @return (void*)0 if successful , other value otherwise
 */
void* QueryMaker(void* _p);










#endif /* __QUERY_MAKER_H__ */







