


/** 
 *  @file subscrStorageManager.c
 *  @brief Subscribers aggregated data storage
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "subscrStorageManager.h"
#include "dataStorageApi.h"
#include "commonStructs.h"

struct SubscrStorageManager
{
	size_t m_numOfSubscribers;
	
	size_t m_capacity;
	
	AggSubscriberData* m_asd;
};


static void SubscrUpdate(AggSubscriberData* _asd, const CDR* _cdr)
{
	#define IS_WITHIN_NETWORK (_cdr->m_MCCMNC == _cdr->m_partyMCCMNC)

	assert(NULL!=_asd);
	assert(NULL!=_cdr);	

	switch (_cdr->m_callType)
	{
		case MOC:
			if(IS_WITHIN_NETWORK)
			{
				_asd->m_outWithin += _cdr->m_dur;
			}else
			{
				_asd->m_outOutside += _cdr->m_dur;
			}
			break;
		case MTC:
			if(IS_WITHIN_NETWORK)
			{
				_asd->m_inWithin += _cdr->m_dur;
			}else
			{
				_asd->m_inOutside += _cdr->m_dur;
			}
			break;
		case SMS_MO:
			if(IS_WITHIN_NETWORK)
			{
				_asd->m_sendWithin += 1;
			}else
			{
				_asd->m_sendOutside += 1;
			}
			break;
		case SMS_MT:
			if(IS_WITHIN_NETWORK)
			{
				_asd->m_recWithing += 1;
			}else
			{
				_asd->m_recOutside += 1;
			}
			break;
		case GPRS:
			_asd->m_down += _cdr->m_down;
			_asd->m_up += _cdr->m_up;
		break;	
	}	
	#undef IS_WITHIN_NETWORK
}


SubscrStorageManager* SubscrStorageManager_Create(size_t _capacity)
{
	SubscrStorageManager* ssm;
	
	assert(1 < _capacity);
	
	if(NULL == (ssm = malloc(sizeof(SubscrStorageManager))))
	{
		return NULL;
	}
	
	if(NULL == (ssm->m_asd = malloc(sizeof(AggSubscriberData)*_capacity)))
	{
		free(ssm);
		return NULL;
	}
	
	ssm->m_capacity = _capacity;
	ssm->m_numOfSubscribers = 1;

	return ssm;
}


void SubscrStorageManager_Destroy(SubscrStorageManager* _ssm)
{
	assert(NULL!=_ssm);
	
	free(_ssm->m_asd);
	free(_ssm);
}


void SubscrStorageManager_UpdateFunction(void* _context, void* _location)
{
	DataStorageContext* dsc = (DataStorageContext*)_context;
	SubscrStorageManager* ssm = dsc->m_storageManager;
	
	assert(NULL!=_context);
	assert(NULL!=_location);
	
	SubscrUpdate((void*)((char*)(ssm->m_asd) + (size_t)_location), dsc->m_data);
}


void* SubscrStorageManager_InsertFunction(void* _context)
{
	DataStorageContext* dsc = (DataStorageContext*)_context;
	SubscrStorageManager* ssm = dsc->m_storageManager;
	AggSubscriberData* tmpASD;
	
	assert(NULL!=_context);

	if(ssm->m_numOfSubscribers == ssm->m_capacity)
	{
		tmpASD = realloc(ssm->m_asd,sizeof(AggSubscriberData)*2*(ssm->m_capacity));
		if(NULL == tmpASD)
		{
			return NULL;
		}
		
		ssm->m_capacity *= 2;
		ssm->m_asd = tmpASD;
	}
	
	memset(ssm->m_asd + ssm->m_numOfSubscribers,0,sizeof(AggSubscriberData));
	
	ssm->m_asd[ssm->m_numOfSubscribers].m_IMSI = ((CDR*)(dsc->m_data))->m_IMSI;

	SubscrUpdate(ssm->m_asd + ssm->m_numOfSubscribers, dsc->m_data);
	
	return ((void*)(sizeof(AggSubscriberData)*(ssm->m_numOfSubscribers ++)));
}


void SubscrStorageManager_ReadFunction(void* _context, void* _location)
{
	DataStorageContext* dsc = (DataStorageContext*)_context;
	SubscrStorageManager* ssm = dsc->m_storageManager;
	
	assert(NULL!=_context);
	assert(NULL!=_location);
	
	memcpy(dsc->m_data, (char*)(ssm->m_asd) + (size_t)_location, sizeof(AggSubscriberData));
}

size_t SubscrStorageManager_GetNumOfSubscribers(SubscrStorageManager* _ssm)
{
	assert(NULL!=_ssm);
	
	return _ssm->m_numOfSubscribers -1;
}


size_t SubscrStorageManager_Save(SubscrStorageManager* _ssm, int _fd)
{
	size_t i;
	
	assert(NULL!=_ssm);
	
	for(i = 1 ; i <  _ssm->m_numOfSubscribers ; ++i)
	{
		if(sizeof(AggSubscriberData) > write(_fd,_ssm->m_asd +i,sizeof(AggSubscriberData)))
		{
			break;
		}
	}
	
	return i-1;
}









