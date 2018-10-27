
#ifndef __DATA_STORAGE_API_H__
#define __DATA_STORAGE_API_H__


/** 
 *  @file dataStorageApi.h
 *  @brief Data storage API
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

typedef struct DataStorageContext
{
	void* m_storageManager;
	
	void* m_data;

} DataStorageContext;

/**
 *The following SIGNATURES are to be implemented with appropriate names.
 */

/**  
 * @brief update the record in _location with the new _data
 * @param[in] _context of type DataStorageApi
 * @param[in] _location location of the record
 */
void STORAGE_MANAGER_UpdateFunction(void* _context, void* _location);

/**  
 * @brief insert the new _data to the storage
 * @param[in] _context of type DataStorageApi
 * @return newly allocated location of the record
 */
void* STORAGE_MANAGER_InsertFunction(void* _context);


/**  
 * @brief read the data from the storage
 * @param[in] _context of type DataStorageContext
 * @param[in] _location location of the record
 */
void STORAGE_MANAGER_ReadFunction(void* _context, void* _location);


#endif /* __DATA_STORAGE_API_H__ */

