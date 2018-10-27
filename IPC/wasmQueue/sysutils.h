
#ifndef __SYSUTILS_H__
#define __SYSUTILS_H__

/** 
 *  @file sysutils.h
 *  @brief System utility functions
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include <stddef.h>

#define KEY_FILE "wasmQueueKeyFile"

#define SHARED_MEM_SIZE 4096

/**  
 * @brief get the ID of the semaphors
 * @return semid
 */
int GetSemaphore(void);

/**  
 * @brief initiates the semaphors
 * @param[in] _sem  the ID of the semaphors
 * @param[in] _queueSize  size of queue (ITEMS !!!)
 * @return 0 if OK  ,!=0 otherwise  
 */
int InitSemaphore(int _sem, size_t _queueSize);

/**  
 * @brief request for inserting to message to the queue 
 * @param[in] _sem  the ID of the semaphors
 * @return 0 if OK  ,!=0 otherwise  
 */
int InsertRequest(int _sem);

/**  
 * @brief undo request for inserting to message to the queue 
 * @param[in] _sem  the ID of the semaphors
 * @return 0 if OK  ,!=0 otherwise  
 */
int UndoInsertRequest(int _sem);

/**  
 * @brief request for removing to message to the queue 
 * @param[in] _sem  the ID of the semaphors
 * @return 0 if OK  ,!=0 otherwise  
 */
int RemoveRequest(int _sem);

/**  
 * @brief undo request for removing to message to the queue 
 * @param[in] _sem  the ID of the semaphors
 * @return 0 if OK  ,!=0 otherwise  
 */
int UndoRemoveRequest(int _sem);

/**  
 * @brief release the binary semaphore 
 * @param[in] _sem  the ID of the semaphors
 * @return 0 if OK  ,!=0 otherwise  
 */
int ReleaseSem(int _sem);

/**  
 * @brief Init Shared Memory
 * @return shared memory ID
 */
int InitSharedMem(void);

/**  
 * @brief Attach To Shared Memory
 * @return local adress of the shared memory
 */
void* AttachToSharedMem(int _shmem);

/**  
 * @brief Detach From Shared Memory
 * @return 0 if OK  ,!=0 otherwise 
 */
int DetachFromSharedMem(void* _shmem);





#endif /*__SYSUTILS_H__*/





