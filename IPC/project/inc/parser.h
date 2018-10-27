
#ifndef __PARSER_H__
#define __PARSER_H__


/** 
 *  @file parser.c
 *  @brief parsing the CDR file and sending the structured data to the msgQ
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


/**  
 * @brief parse a string of CDR into appropriate structure
 * and sends it to a msgQ
 * @param[in] _buff string with CDR
 * @param[in] _msgQID id of the msgQ (of System V)
 * @return 0 if successful , other value otherwise
 */
int ParseCDR(char* _buff, int _msgQID);


/**  
 * @brief parse a file of CDR into appropriate structures
 * and sends it to a msgQ
 * @param[in] _fileName name of the CDR file
 * @return 0 if successful , other value otherwise
 */
int ParseCDRFile(const char* _fileName);






#endif /* __PARSER_H__ */

