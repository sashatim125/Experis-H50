
#ifndef __AGGREGATOR_H__
#define __AGGREGATOR_H__


/** 
 *  @file aggregator.h
 *  @brief aggregator interface
 *	
 *  @details  see comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 */

#include "HashMap.h"


typedef struct Aggregator Aggregator;

/**  
 * @brief Aggregator creator
 * @param[in] _numOfLocks number of locks(mutexes or semaphores to be used)
 * @param[in] _capacity - Expected max capacity 
 * 						  actuall capacity will be equal to nearest larger prime number.
 * @param[in] _hashFunc - hashing function for keys
 * @param[in] _keysEqualFunc - equality check function for keys. 
 * @param[in] _upFunc - user function on _context and the value from the aggregator
 * @param[in] _insFunc - user function on _context that return the value to put to the aggregator
 * @param[in] _readFunc - user function on _context and the value from the aggregator
 * @return newly created Aggregator or null on failure
 */
Aggregator* Aggregator_Create(size_t _numOfLocks, size_t _capacity,
	HashFunction _hashFunc, EqualityFunction _keysEqualFunc,
	void (*_upFunc)(void*, void*),
	void* (*_insFunc)(void*),
	void (*_readFunc)(void*,void*));


/**
 * @brief destroy the Aggregator
 * @param[in] _agg : Aggregator to be destroyed
 * @warning do not call if you have Aggregator_Upsert or Aggregator_Read threads waiting
 */
void Aggregator_Destroy(Aggregator* _agg);


/** 
 * @brief Update or insert new value
 * @param[in] _agg : Aggregator
 * @param[in] _key - to look for
 * @param[in] _context - User provided context for the _upFunc or _insFunc from the create
 * @returns 0 on success or !=0 otherwise
 * @warning the function IS thread-safe
 */
int Aggregator_Upsert(Aggregator* _agg, const void* _key, void* _context);


/** 
 * @brief Read the Value (call _readFunc) of the corresponding _key
 * @param[in] _agg : Aggregator
 * @param[in] _key - to look for
 * @param[in] _context - User provided context for the _readFunc
 * @returns 0 on success or !=0 otherwise
 * @warning the function IS thread-safe
 */
int Aggregator_Read(Aggregator* _agg, const void* _key, void* _context);

#endif /* __AGGREGATOR_H__ */

