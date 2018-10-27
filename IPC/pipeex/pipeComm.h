
#ifndef __PIPE_COMM_H__
#define __PIPE_COMM_H__

/** 
 *  @file pipeComm.h
 *  @brief Definitions of the file transfer through pipe functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#define NEW_FILE "_new"

/**  
 * @brief Send a file to named pipe.  
 * @param[in] _fileName - name of the file to be streamed (as '\0' terminated string)
 * @param[in] _pipeName - name of the pipe (as '\0' terminated string)
 * @return status (0 fo success)
 */
int sendFileToPipe(const char* _fileName, const char* _pipeName);


/**  
 * @brief Receive a file from named pipe.  
 * @param[in] _pipeName - name of the pipe (as '\0' terminated string)
 * @return status (0 fo success)
 */
int receiveFileFromPipe(const char* _pipeName);




#endif /*__PIPE_COMM_H__*/

