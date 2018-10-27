
#ifndef __FORMATED_PRINT_H__
#define __FORMATED_PRINT_H__


/** 
 *  @file formatedPrint.h
 *  @brief Formating aggregated data to a printable format
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stdio.h>

#include "commonStructs.h"

/**  
 * @brief prints the _data to the _output in appropriate format
 * @param[in] _output output stream (opened for write)
 * @param[in] _dataType the data type
 * @param[in] _data pointer to the data structure
 * @return 0 if succsessful , other value otherwise
 */
int PrintAggregatedDataReport(FILE* _output, AggregatedDataType _dataType, const void* _data);


/**  
 * @brief prints the _data to the _output in appropriate format
 * @param[in] _output output stream (opened for write)
 * @param[in] _dataType the data type
 * @param[in] _data pointer to the data structure
 * @return 0 if succsessful , other value otherwise
 */
int PrintAggregatedDataReadable(FILE* _output, AggregatedDataType _dataType, const void* _data);


#endif /* __FORMATED_PRINT_H__ */

