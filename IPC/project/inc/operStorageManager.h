
#ifndef __OPER_STORAGE_MANAGER_H__
#define __OPER_STORAGE_MANAGER_H__


/** 
 *  @file operStorageManager.h
 *  @brief Operators aggregated data storage
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */


/*implements "dataStorageApi.h"*/

typedef struct OperStorageManager OperStorageManager;


/**  
 * @brief create the new storage for the operators data
 * @param[in] _capacity initial capacity > 1
 * @return newly alocated storage
 */
OperStorageManager* OperStorageManager_Create(size_t _capacity);

/**  
 * @brief destroy the storage for the operators data
 * @param[in] _osm the storage object
 */
void OperStorageManager_Destroy(OperStorageManager* _osm);

/**  
 * @brief update the record in _location with the new _data
 * @param[in] _context of type DataStorageContext
 * @param[in] _location location of the record (OFFSET!!!)
 */
void OperStorageManager_UpdateFunction(void* _context, void* _location);

/**  
 * @brief insert the new _data to the storage
 * @param[in] _context of type DataStorageContext
 * @return newly allocated location of the record (OFFSET!!!)
 */
void* OperStorageManager_InsertFunction(void* _context);

/**  
 * @brief read the data from the storage
 * @param[in] _context of type DataStorageContext
 * @param[in] _location location of the record  (OFFSET!!!)
 */
void OperStorageManager_ReadFunction(void* _context, void* _location);

/**  
 * @brief get the number of operators
 * @param[in] _osm the storage object
 * @return the number of operators
 */
size_t OperStorageManager_GetNumOfOperators(OperStorageManager* _osm);

/**  
 * @brief save the storage to file
 * @param[in] _osm the storage object
 * @param[in] _fd file desciptor of the file opened for writing (could be pipe)
 * @warning the function may block
 * @warning the function IS NOT thread-safe
 * @returns number of entities successfully written to the file
 */
size_t OperStorageManager_Save(OperStorageManager* _osm, int _fd);


#endif /* __OPER_STORAGE_MANAGER_H__ */









