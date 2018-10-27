
#ifndef __REPORT_MAKER_H__
#define __REPORT_MAKER_H__


/** 
 *  @file reportMaker.h
 *  @brief the report maker api : snapshots and reports
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include "commonStructs.h"

#define SNAPSHOT_DIR "./snapshot/"
#define REPORT_DIR "./report/"

#define SUBSCRIBER_FILE_EXTENTION ".subscr"
#define OPERATOR_FILE_EXTENTION ".oper"

#define MAX_FILENAME_LENGTH	256


typedef struct SnapshotMakerParams
{
	AggregatedDataType m_adt;
	
	void* m_sm; /*<< storage manager*/

	char m_filename[MAX_FILENAME_LENGTH];
	
} SnapshotMakerParams;

/**  
 * @brief save the storage manager contents to the file with current date-time stamp :
 * "dd-mm-yyyy_hh:mm:ss.EXTENSION" , where EXTENSION is SUBSCRIBER_FILE_EXTENTION
 * or OPERATOR_FILE_EXTENTION as above
 * @param[in] _adt aggregated data type 
 * @param[in] _sm appropriate storage manager
 * @param[out] _filename the name of the snapshot file 
 * @return (void*)0 if successful , other value otherwise
 */
void* SnapshotMaker(void* _p);


/**  
 * @brief convert the snapshot file _fileName from the SNAPSHOT_DIR 
 * to report file in the REPORT_DIR
 * @param[in] _reportType aggregated data type 
 * @param[in] _filename the name of the snapshot file 
 * @return 0 if successful , other value otherwise
 */
int ReportMaker(AggregatedDataType _reportType, const char* _fileName);






#endif /* __REPORT_MAKER_H__ */



