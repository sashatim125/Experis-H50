
#ifndef __SUBSCR_STORAGE_MANAGER_H__
#define __SUBSCR_STORAGE_MANAGER_H__


/** 
 *  @file subscrStorageManager.h
 *  @brief Subscribers aggregated data storage
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


/*implements "dataStorageApi.h"*/

typedef struct SubscrStorageManager SubscrStorageManager;


/**  
 * @brief create the new storage for the subscribers data
 * @param[in] _capacity initial capacity > 1
 * @return newly alocated storage
 */
SubscrStorageManager* SubscrStorageManager_Create(size_t _capacity);

/**  
 * @brief destroy the storage for the subscribers data
 * @param[in] _ssm the storage object
 */
void SubscrStorageManager_Destroy(SubscrStorageManager* _ssm);

/**  
 * @brief update the record in _location with the new _data
 * @param[in] _context of type DataStorageContext
 * @param[in] _location location of the record (OFFSET!!!)
 */
void SubscrStorageManager_UpdateFunction(void* _context, void* _location);

/**  
 * @brief insert the new _data to the storage
 * @param[in] _context of type DataStorageContext
 * @return newly allocate location of the record (OFFSET!!!)
 */
void* SubscrStorageManager_InsertFunction(void* _context);

/**  
 * @brief read the data from the storage
 * @param[in] _context of type DataStorageContext
 * @param[in] _location location of the record  (OFFSET!!!)
 */
void SubscrStorageManager_ReadFunction(void* _context, void* _location);

/**  
 * @brief get the number of subscribers
 * @param[in] _ssm the storage object
 * @return the number of subscribers
 */
size_t SubscrStorageManager_GetNumOfSubscribers(SubscrStorageManager* _ssm);





/**  
 * @brief save the storage to file
 * @param[in] _ssm the storage object
 * @param[in] _fd file desciptor of the file opened for writing (could be pipe)
 * @warning the function may block
 * @warning the function IS NOT thread-safe
 * @returns number of entities successfully written to the file
 */
size_t SubscrStorageManager_Save(SubscrStorageManager* _ssm, int _fd);

#endif /* __SUBSCR_STORAGE_MANAGER_H__ */









