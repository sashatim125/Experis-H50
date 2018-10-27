


/** 
 *  @file operStorageManager.c
 *  @brief Operators aggregated data storage
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

#include "operStorageManager.h"
#include "dataStorageApi.h"
#include "commonStructs.h"

struct OperStorageManager
{
	size_t m_numOfOperators;
	
	size_t m_capacity;
	
	AggOperatorData* m_aod;
};



static void OperUpdate(AggOperatorData* _aod, const CDR* _cdr)
{
	assert(NULL!=_aod);
	assert(NULL!=_cdr);	

	switch (_cdr->m_callType)
	{
		case MOC:
			_aod->m_out += _cdr->m_dur;
			break;
		case MTC:
			_aod->m_in += _cdr->m_dur;
			break;
		case SMS_MO:
			_aod->m_send += 1;
			break;
		case SMS_MT:
			_aod->m_rec += 1;
			break;
		case GPRS:
		/*
			_aod->m_down += _cdr->m_down;
			_aod->m_up += _cdr->m_up;
		*/
		break;	
	}
	
}

OperStorageManager* OperStorageManager_Create(size_t _capacity)
{
	OperStorageManager* osm;
	
	assert(1 < _capacity);
	
	if(NULL == (osm = malloc(sizeof(OperStorageManager))))
	{
		return NULL;
	}
	
	if(NULL == (osm->m_aod = malloc(sizeof(AggOperatorData)*_capacity)))
	{
		free(osm);
		return NULL;
	}
	
	osm->m_capacity = _capacity;
	osm->m_numOfOperators = 1;
	
	return osm;
}


void OperStorageManager_Destroy(OperStorageManager* _osm)
{
	assert(NULL!=_osm);
	
	free(_osm->m_aod);
	free(_osm);
}


void OperStorageManager_UpdateFunction(void* _context, void* _location)
{
	DataStorageContext* dsc = (DataStorageContext*)_context;
	OperStorageManager* osm = dsc->m_storageManager;
	
	assert(NULL!=_context);
	assert(NULL!=_location);
	
	OperUpdate((void*)((char*)(osm->m_aod) + (size_t)_location),dsc->m_data);
}


void* OperStorageManager_InsertFunction(void* _context)
{
	DataStorageContext* dsc = (DataStorageContext*)_context;
	OperStorageManager* osm = dsc->m_storageManager;
	AggOperatorData* tmpAOD;
	
	assert(NULL!=_context);

	if(osm->m_numOfOperators == osm->m_capacity)
	{
		tmpAOD = realloc(osm->m_aod,sizeof(AggOperatorData)*2*(osm->m_capacity));
		if(NULL == tmpAOD)
		{
			return NULL;
		}
		
		osm->m_capacity *= 2;
		osm->m_aod = tmpAOD;		
	}
	
	memset(osm->m_aod + osm->m_numOfOperators,0,sizeof(AggOperatorData));
	
	osm->m_aod[osm->m_numOfOperators].m_MCCMNC = ((CDR*)(dsc->m_data))->m_MCCMNC;
	memcpy(osm->m_aod[osm->m_numOfOperators].m_operBrand,
		((CDR*)(dsc->m_data))->m_operBrand, OPERATOR_BRANDNAME_SIZE);

	OperUpdate(osm->m_aod + osm->m_numOfOperators, dsc->m_data);
	
	return ((void*)(sizeof(AggOperatorData)*(osm->m_numOfOperators ++)));
}


void OperStorageManager_ReadFunction(void* _context, void* _location)
{
	DataStorageContext* dsc = (DataStorageContext*)_context;
	OperStorageManager* osm = dsc->m_storageManager;
	
	assert(NULL!=_context);
	assert(NULL!=_location);
	
	memcpy(dsc->m_data,(void*)((char*)(osm->m_aod) + (size_t)_location), sizeof(AggOperatorData));
}


size_t OperStorageManager_GetNumOfOperators(OperStorageManager* _osm)
{
	assert(NULL!=_osm);
	
	return _osm->m_numOfOperators -1;
}


size_t OperStorageManager_Save(OperStorageManager* _osm, int _fd)
{
	size_t i;
	
	assert(NULL!=_osm);
	
	for(i = 1 ; i <  _osm->m_numOfOperators ; ++i)
	{
		if(sizeof(AggOperatorData) > write(_fd,_osm->m_aod +i,sizeof(AggOperatorData)))
		{
			break;
		}
	}
	
	return i-1;
}







