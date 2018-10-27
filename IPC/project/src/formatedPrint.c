

/** 
 *  @file formatedPrint.c
 *  @brief Formating aggregated data to a printable format
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <assert.h>
#include <stdio.h>

#include "formatedPrint.h"
#include "aggregator.h"
#include "subscrStorageManager.h"
#include "operStorageManager.h"



int PrintAggregatedDataReport(FILE* _output, AggregatedDataType _dataType, const void* _data)
{
	AggSubscriberData* asd = (AggSubscriberData*)_data;
	AggOperatorData* aod = (AggOperatorData*)_data;

	assert(NULL!=_output);
	assert(NULL!=_data);

	switch(_dataType)
	{
		case SUBSCRIBER:
			fprintf(_output,"%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu,%lu\n",
	asd->m_IMSI,	
	asd->m_outWithin,
	asd->m_inWithin,
	asd->m_outOutside,
	asd->m_inOutside,
	asd->m_sendWithin,
	asd->m_recWithing,
	asd->m_sendOutside,
	asd->m_recOutside,
	asd->m_down,
	asd->m_up);
			break;
		case OPERATOR:
			fprintf(_output,"%lu,%s,%lu,%lu,%lu,%lu\n",
	aod->m_MCCMNC,	
	aod->m_operBrand,
	aod->m_in,
	aod->m_out,
	aod->m_send,
	aod->m_rec);
			break;
	}

	return 0;
}

int PrintAggregatedDataReadable(FILE* _output, AggregatedDataType _dataType, const void* _data)
{
	AggSubscriberData* asd = (AggSubscriberData*)_data;
	AggOperatorData* aod = (AggOperatorData*)_data;

	assert(NULL!=_output);
	assert(NULL!=_data);

	switch(_dataType)
	{
		case SUBSCRIBER:
			fprintf(_output,"\
IMSI            = %lu\n\
Call durations :\n\
Outcall within	= %lu\n\
Incall within	= %lu\n\
Outcall outside	= %lu\n\
Incall outside	= %lu\n\
Number of SMS :\n\
Sent within     = %lu\n\
Received within = %lu\n\
Sent outside	= %lu\n\
Received outside= %lu\n\
Number of Mb :\n\
Downloaded      = %lu\n\
Uploaded        = %lu\n\n",
	asd->m_IMSI,	
	asd->m_outWithin,
	asd->m_inWithin,
	asd->m_outOutside,
	asd->m_inOutside,
	asd->m_sendWithin,
	asd->m_recWithing,
	asd->m_sendOutside,
	asd->m_recOutside,
	asd->m_down,
	asd->m_up);
			break;
		case OPERATOR:
			fprintf(_output,"\
MCCMNC          = %lu\n\
Brand Name      = %s\n\
Call durations :\n\
Incall      	= %lu\n\
Outcall     	= %lu\n\
Number of SMS :\n\
Sent            = %lu\n\
Received        = %lu\n\n",
	aod->m_MCCMNC,	
	aod->m_operBrand,
	aod->m_in,
	aod->m_out,
	aod->m_send,
	aod->m_rec);
			break;
	}

	return 0;
}



