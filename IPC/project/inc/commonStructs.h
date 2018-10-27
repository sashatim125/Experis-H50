
#ifndef __COMMON_STRUCTS_H__
#define __COMMON_STRUCTS_H__


/** 
 *  @file commonStructs.h
 *  @brief commonly used data structs and definitions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h> /*size_t*/

/*including '\0' terminator*/
#define OPERATOR_BRANDNAME_SIZE 65
#define DATE_SIZE 11
#define TIME_SIZE 9

#define MAX_STRUCTURE_SIZE 2048
#define MAX_CDR_STRING_SIZE 2048

typedef enum AggregatedDataType
{
	SUBSCRIBER,
	OPERATOR
} AggregatedDataType;

typedef size_t			IMSI_t;

typedef size_t			MSISDN_t;

typedef size_t			IMEI_t;

typedef unsigned long	MCCMNC_t;

typedef enum CallType
{
	MOC,
	MTC,
	SMS_MO,
	SMS_MT,
	GPRS	
}CallType;

typedef unsigned long	NumOfSMS;

typedef unsigned long	CallDuration;

typedef unsigned long	NumOfMb;

typedef struct AggSubscriberData
{
	IMSI_t m_IMSI;
	
	CallDuration m_outWithin;
	
	CallDuration m_inWithin;
	
	CallDuration m_outOutside;
	
	CallDuration m_inOutside;
	
	NumOfSMS m_sendWithin;
	
	NumOfSMS m_recWithing;

	NumOfSMS m_sendOutside;
	
	NumOfSMS m_recOutside;
	
	NumOfMb m_down;
	
	NumOfMb m_up;
	
} AggSubscriberData;


typedef struct AggOperatorData
{
	MCCMNC_t m_MCCMNC;
	
	char m_operBrand[OPERATOR_BRANDNAME_SIZE];
	
	CallDuration m_in;
	
	CallDuration m_out;
	
	NumOfSMS m_send;
	
	NumOfSMS m_rec;

} AggOperatorData;


typedef struct CDR
{
	IMSI_t m_IMSI;
	
	MSISDN_t m_MSISDN;
	
	IMEI_t m_IMEI;
	
	char m_operBrand[OPERATOR_BRANDNAME_SIZE];
	
	MCCMNC_t m_MCCMNC;
	
	CallType m_callType;
	
	char m_callDate[DATE_SIZE];
	
	char m_callTime[TIME_SIZE];
	
	CallDuration m_dur;
	
	NumOfMb m_down;
	
	NumOfMb m_up;
	
	MSISDN_t m_partyMSISDN;
	
	MCCMNC_t m_partyMCCMNC;

}CDR;










#endif /* __COMMON_STRUCTS_H__ */

