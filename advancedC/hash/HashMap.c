
/** 
 *  @file HashMap.c
 *  @brief Implementation of the generic Hash Map
 *	
 *  @details  see incode comments
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug exterminator at work!  
 */
 
 
 
 
#include "HashMap.h"
#include "list.h"
#include "list_itr.h"
#include "list_functions.h"

#include <stdlib.h>

#ifndef TRUE
#define TRUE 1
#endif
 
#ifndef FALSE
#define FALSE 0
#endif 
 
#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER 0xabcd
#endif /*MAGIC_NUMBER*/

typedef struct HashPair
{
	void* m_key;
	
	void* m_value;

} HashPair;


typedef struct HashBucket
{
	List*	m_list;
	
	size_t	m_size;
	
} HashBucket;


struct HashMap
{
	int 				m_magicNum;
	
	size_t 				m_capacity;
	
	HashBucket* 		m_buckets;
	
	HashFunction 		m_hashFunc;
	
	EqualityFunction	m_keysEqualFunc;
	
#ifndef NDEBUG
	size_t				m_collisions;
#endif /* NDEBUG */
};


static int IsPrime(size_t _num)
{
	size_t div;
	size_t maxDiv;
	
	if(2 > _num)
	{
		return FALSE;
	}
	
	for(div=2 , maxDiv = _num/2; div <= maxDiv && 0 != _num % div ; ++div)
		;
	
	return (div > maxDiv) ? TRUE : FALSE;
}


static size_t GetNearestPrime(size_t _num)
{
	while (!IsPrime(_num++))
		;
	
	return _num-1;
}


HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{

	HashMap *newMap;

	if(0==_capacity || NULL==_hashFunc || NULL==_keysEqualFunc)
	{
		return NULL;
	}
	
	if(NULL==(newMap = calloc(1,sizeof(HashMap))))
	{
		return NULL;
	}
	
	newMap->m_capacity = GetNearestPrime(_capacity);
	
	if(NULL==(newMap->m_buckets = calloc(newMap->m_capacity,sizeof(HashBucket))))
	{
		free(newMap);
		return NULL;
	}
	
	newMap->m_hashFunc = _hashFunc;
	newMap->m_keysEqualFunc = _keysEqualFunc;

	newMap->m_magicNum = MAGIC_NUMBER;

	return newMap;	
}


static void (*keyDestroyFunctionPtr)(void* _key);
static void (*valDestroyFunctionPtr)(void* _value);

static void PairDestroyFunc(void* _pair)
{
	
	if (NULL!=keyDestroyFunctionPtr)
	{
		keyDestroyFunctionPtr(((HashPair*)_pair)->m_key);
	}
	
	if (NULL!=valDestroyFunctionPtr)
	{
		valDestroyFunctionPtr(((HashPair*)_pair)->m_value);
	}
	
	free(_pair);
}

void HashMap_Destroy(HashMap** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	size_t i;
	List *nextList;

	if(NULL==_map || NULL==*_map || MAGIC_NUMBER != (*_map)->m_magicNum)
	{
		return;
	}
	
	(*_map)->m_magicNum = -1;
	
	keyDestroyFunctionPtr = _keyDestroy;
	valDestroyFunctionPtr = _valDestroy;
	
	for(i=0 ; i < (*_map)->m_capacity ; ++i)
	{
		if(NULL!=(nextList = (*_map)->m_buckets[i].m_list))
		{
			if (NULL!=_keyDestroy || NULL!=_valDestroy) 
			{
				List_Destroy(&nextList,PairDestroyFunc);
			}else
			{
				List_Destroy(&nextList,free);
			}
		}
	}
	
	free((*_map)->m_buckets);
	free(*_map);
	
	*_map = NULL;
}


typedef struct Search
{
	const void*		 m_key;
	EqualityFunction m_equalFunc;

} Search;

static int ArePairsEqual(void * _nextPair, void* _searchStructPtr)
{
	return ((Search*)_searchStructPtr)->m_equalFunc(((HashPair*)_nextPair)->m_key,
		((Search*)_searchStructPtr)->m_key);
}

static ListItr FindPair(HashMap* _map, const void* _searchKey, HashBucket** _bucketPtr)
{
	size_t place;
	ListItr iterator;
	Search searchStruct;
	List *list;
	
	place = _map->m_hashFunc(_searchKey) % _map->m_capacity;
	*_bucketPtr = &(_map->m_buckets[place]);
	
	if(NULL==(list = (*_bucketPtr)->m_list))
	{
		return NULL;
	}
	
	searchStruct.m_key = _searchKey;
	searchStruct.m_equalFunc = _map->m_keysEqualFunc;
	
#ifndef NDEBUG
	if(1 < (*_bucketPtr)->m_size)
	{
		++_map->m_collisions;
	}
#endif /* NDEBUG */
	
	iterator = ListItr_FindFirst(ListItr_Begin(list), ListItr_End(list),
		ArePairsEqual, &searchStruct);
	
	return (ListItr_Equals(iterator,ListItr_End(list)) ?
		NULL : iterator);
}


static Map_Result InsertPair(HashPair *_pair, HashBucket *_bucket)
{
	int newListCreated;
	
	if(NULL==_bucket->m_list)
	{
		if(NULL==(_bucket->m_list = List_Create()))
		{
			return MAP_ALLOCATION_ERROR;
		}
		newListCreated = TRUE;
	}else
	{
		newListCreated = FALSE;
	}

	if(LIST_ALLOCATION_ERROR == List_PushHead(_bucket->m_list,_pair))
	{
		if(newListCreated)
		{
			List_Destroy(&(_bucket->m_list),NULL);
		}
		return MAP_ALLOCATION_ERROR;
	}
	
	++(_bucket->m_size);
	
	return MAP_SUCCESS;
}




/** 
 * @brief Insert a key-value pair into the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to insert to, must be initialized
 * @param[in] _key - key to serve as index 
 * @param[in] _value - the value to associate with the key 
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_DUPLICATE_ERROR	if key alread present in the map
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_ALLOCATION_ERROR on failer to allocate key-value pair
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
	ListItr itr;
	HashBucket *bucket;
	HashPair *newPair;
	Map_Result res;

	if(NULL==_map)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(NULL==_key)
	{
		return MAP_KEY_NULL_ERROR;
	}

	itr = FindPair(_map, _key, &bucket);
	
	if(NULL!=itr)
	{
		return MAP_KEY_DUPLICATE_ERROR;
	}
	
	if(NULL==(newPair = malloc(sizeof(HashPair))))
	{
		return MAP_ALLOCATION_ERROR;
	}
	newPair->m_key 	 = (void*)_key;
	newPair->m_value = (void*)_value;
	
	res = InsertPair(newPair,bucket);
	if(MAP_ALLOCATION_ERROR == res)
	{
		free(newPair);
	}
	return res;
}



/** 
 * @brief Remove a key-value pair from the hash map.
 * complexty(?)
 * @param[in] _map - Hash map to remove pair from, must be initialized
 * @param[in] _searchKey - key to to search for in the map
 * @param[out] _pKey - pointer to variable that will get the key stored in the map equaling _searchKey
 * @param[out] _pValue - pointer to variable that will get the value stored in the map corresponding to foind key
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	ListItr itr;
	HashBucket *bucket;
	HashPair *pair;

	if(NULL==_map || NULL==_pKey || NULL==_pValue)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(NULL==_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	itr = FindPair(_map, _searchKey, &bucket);
	
	if(NULL==itr)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	pair = (HashPair*)ListItr_Remove(itr);
	--(bucket->m_size);
	
	*_pKey = pair->m_key;
	*_pValue = pair->m_value;
	
	free(pair);
	
	if(0 == bucket->m_size)
	{
		List_Destroy(&(bucket->m_list),NULL);
	}
	
	return MAP_SUCCESS;
}


/** 
 * @brief Find a value by key
 * complexty(?)
 * @param[in] _map - Hash map to use, must be initialized
 * @param[in] _searchKey - key to serve as index for search
 * @param[out] _pValue - pointer to variable that will get the value assoiciated with the search key.
 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
Map_Result HashMap_Find(const HashMap* _map, const void* _searchKey, void** _pValue)
{
	ListItr iterator;
	HashBucket *bucket;

	if(NULL==_map || NULL==_pValue)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(NULL==_searchKey)
	{
		return MAP_KEY_NULL_ERROR;
	}

	iterator = FindPair((HashMap*)(void*)_map, _searchKey, &bucket);
	
	if(NULL==iterator)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	
	*_pValue = ((HashPair*)ListItr_Get(iterator))->m_value;

	return MAP_SUCCESS;
}


typedef struct Reinsert
{
	HashBucket*		m_buckets;
	size_t 			m_capacity;
	HashFunction	m_hashFunc;

} Reinsert;

static int InsertPairToBuckets(void* _pair, void* _reinsertStruct)
{
	size_t place;
	Reinsert *reinsertStruct = (Reinsert*)_reinsertStruct;
	HashPair *pair = (HashPair*)_pair;
	Map_Result res;
	
	place = reinsertStruct->m_hashFunc(pair->m_key) % reinsertStruct->m_capacity;
	
	res = InsertPair(pair, &(reinsertStruct->m_buckets[place]));
	
	return (MAP_SUCCESS == res) ? TRUE : FALSE;
}

static void CleanBuckets(HashBucket *_buckets,size_t _capacity)
{
	size_t i;
	
	for(i=0 ; i < _capacity ; ++i)
	{
		if(NULL!=_buckets[i].m_list)
		{
			List_Destroy(&(_buckets[i].m_list),NULL);
		}
	}
}

/** 
 * @brief Adjust map capacity and rehash all key/value pairs
 * @param[in] _map - exisiting map
 * @param[in] _newCapacity - new capacity shall be rounded to nearest larger prime number.
 * @return MAP_SUCCESS or MAP_ALLOCATION_ERROR
 */
Map_Result HashMap_Rehash(HashMap *_map, size_t _newCapacity)
{
	HashBucket *newBackets;
	size_t i;
	ListItr itr;
	Reinsert reinsertStruct;

	if(NULL==_map)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	if(0 == _newCapacity)
	{
		return MAP_ALLOCATION_ERROR;
	}
	_newCapacity = 	GetNearestPrime(_newCapacity);
	
	if(NULL==(newBackets = calloc(_newCapacity,sizeof(HashBucket))))
	{
		return MAP_ALLOCATION_ERROR;
	}
	
	reinsertStruct.m_buckets  = newBackets;
	reinsertStruct.m_capacity = _newCapacity;
	reinsertStruct.m_hashFunc = _map->m_hashFunc;

	for(i=0 ; i < _map->m_capacity ; ++i)
	{	
		if(NULL!=_map->m_buckets[i].m_list)
		{
			itr = ListItr_ForEach(ListItr_Begin(_map->m_buckets[i].m_list),
				ListItr_End(_map->m_buckets[i].m_list), InsertPairToBuckets, &reinsertStruct);
			
			if(!ListItr_Equals(itr,ListItr_End(_map->m_buckets[i].m_list)))
			{
				CleanBuckets(newBackets,_newCapacity);
				free(newBackets);
				return MAP_ALLOCATION_ERROR;
			}
		}
	}
	
	CleanBuckets(_map->m_buckets,_map->m_capacity);
	free(_map->m_buckets);
	
	_map->m_buckets  = newBackets;
	_map->m_capacity = _newCapacity;
	
#ifndef NDEBUG
	_map->m_collisions = 0;
#endif /* NDEBUG */

	return MAP_SUCCESS;
}


/**
 * @brief Get number of key-value pairs inserted into the hash map
 * @warning complexity can be O(capacity)
 */
size_t HashMap_Size(const HashMap* _map)
{
	size_t count;
	size_t i;
	
	if(NULL==_map)
	{
		return 0;
	}
	
	for(i=0, count=0 ; i < _map->m_capacity ; ++i)
	{
		count+=_map->m_buckets[i].m_size;
	}
	
	return count;	
}




typedef struct ForEach
{
	KeyValueActionFunction	m_action;
	void* 					m_context;
	size_t*					m_counter;
	
} ForEach;

static int ForEachPairAction(void *_pair,void *_forEachStruct)
{
	HashPair *pair = (HashPair*)_pair;
	ForEach  *forEachStruct = (ForEach*)_forEachStruct;
	
	++(*(forEachStruct->m_counter));
	
	return forEachStruct->m_action(pair->m_key, pair->m_value,
		forEachStruct->m_context);
}

/** 
 * This method is optional in the homework 
 * @brief Iterate over all key-value pairs in the map and call a function for each pair
 * The user provided KeyValueActionFunction will be called for each element.  
 * Iteration will stop if the called function returns a zero for a given pair
 * 
 * @param[in] _map - Hash map to iterate over.
 * @param[in] _action - User provided function pointer to be invoked for each element
 * @param[in] _context - User provided function pointer to be invoked for each element
 * @returns number of times the user functions was invoked
 */
size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
	size_t i;
	size_t count;
	ForEach forEachStruct;
	ListItr itr;

	if(NULL==_map || NULL==_action)
	{
		return MAP_UNINITIALIZED_ERROR;
	}
	
	forEachStruct.m_action  = _action;
	forEachStruct.m_context = _context;
	forEachStruct.m_counter = &count;
	
	for(i=0, count=0 ; i < _map->m_capacity ; ++i)
	{	
		if(NULL!=_map->m_buckets[i].m_list)
		{
			itr = ListItr_ForEach(ListItr_Begin(_map->m_buckets[i].m_list),
				ListItr_End(_map->m_buckets[i].m_list), ForEachPairAction, &forEachStruct);
			
			if(!ListItr_Equals(itr,ListItr_End(_map->m_buckets[i].m_list)))
			{
				break;
			}
		}
	}
	
	return count;
}



#ifndef NDEBUG
Map_Stats HashMap_GetStatistics(const HashMap* _map)
{
	Map_Stats stats={0};
	size_t i;

	if(NULL==_map)
	{
		return stats;
	}
	
	stats.collisions = _map->m_collisions;
	stats.buckets = _map->m_capacity;
	
	for(i=0 ; i < _map->m_capacity ; ++i)
	{
		stats.pairs+=_map->m_buckets[i].m_size;
		
		stats.chains += (_map->m_buckets[i].m_size > 0) ? 1 : 0;
		
		stats.maxChainLength = (_map->m_buckets[i].m_size > stats.maxChainLength) ?
			_map->m_buckets[i].m_size : stats.maxChainLength;
	}
	
	stats.averageChainLength = stats.pairs / stats.chains;
	
	return stats;
}
#endif /* NDEBUG */

















