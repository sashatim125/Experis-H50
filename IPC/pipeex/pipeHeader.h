
#ifndef __PIPE_SHARE_H__
#define __PIPE_SHARE_H__

/** 
 *  @file pipeHeader.h
 *  @brief Definitions of the pipe connection protocol functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h> /*size_t*/


#define BUFFER_SIZE 1024



/**  
 * @brief Create a valid header to the pipe communication.  
 * @param[out] _buffer - where to store the header
 * @param[in] _fileName - name of the file to be streamed (as '\0' terminated string)
 * @param[in] _fileSize - size of the file to be streamed 
 * @return the header size (0 in case of error) 
 */
size_t createHeader(void* _buffer, const char* _fileName,size_t _fileSize);




/**  
 * @brief read the header and retrieve info from it.  
 * @param[in] _buffer - where to read the header from
 * @param[out] _fileName - name of the file to be streamed (as '\0' terminated string)
 * @param[out] _fileSize - size of the file to be streamed 
 * @return status
 * @return 0 if OK  ,!=0 otherwise  
 */
int readHeader(const void* _buffer, char* _fileName, size_t* _fileSize);








#endif /*__PIPE_SHARE_H__*/









