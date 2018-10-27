
/** 
 *  @file hash.c
 *  @brief implementation of API for the the hash table (of ints)
 *	
 *  @details  See the functions description
 *  
 *
 *  @author Alexander Timoshenko sashatim125@gmail.com
 * 
 *  @bug NONE! 
 */

  
#include "hash.h"
#include <stdlib.h>


#ifndef TRUE
#define TRUE 1
#endif /*TRUE*/

#ifndef FALSE 
#define FALSE 0
#endif /*FALSE*/

#ifndef MAGIC_NUMBER
#define MAGIC_NUMBER	-0xabccba
#endif /*MAGIC_NUMBER*/


typedef enum 
{
	OK=-1,
	REMOVED=-2,
	EMPTY=-3,
	NOT_FOUND=-4
} HashStatus;

 
 
struct HashSet
{
	int*    m_data;
	size_t  m_capacity;			      /*original size given by the client*/
	size_t  m_size; 			      /*number of occupied plases in the table*/
	size_t  m_maxCollisionsEver;      /*maximum number of rehash opetations which have been done over one insertion*/
	size_t  m_counterOfOperation;     /*number of all operations*/
	size_t  m_counterOfCollisions;    /*all rehash operations mutual counter*/
	size_t (*m_hashFunction)(size_t); /*hash function from the user*/
	
	int m_magNum;					  /*magic number*/
};


static HashStatus HashSearch(const HashSet *_set, size_t _data, size_t *_firstKey, size_t *_collisions,size_t *_realKey);

static size_t getHashKey(const HashSet *_set,size_t _data);

static size_t Rehash(const HashSet *_set, size_t _key);

static HashStatus GetData(const HashSet *_set, size_t _key, size_t *_data);

static void UpdateCounters(HashSet *_set,size_t _collisions);








 
HashSet* HashSetCreate(size_t _capacity, float _loadFactor, size_t (*_hashFunction)(size_t))
{
	HashSet* newHash;
	size_t i;

	if((NULL==_hashFunction)||(0 == _capacity)||(_loadFactor<=0)||(_loadFactor>1))
	{
		return NULL;
	}
	
	newHash=(HashSet*)calloc(1,sizeof(HashSet));
	if(NULL==newHash)
	{
		return NULL;
	}
	newHash->m_capacity=_capacity*(size_t)(1.0/_loadFactor);
	
	newHash->m_data=(int*)malloc(sizeof(int)*newHash->m_capacity);
	
	if(NULL==newHash->m_data)
	{
		free(newHash);
		return NULL;
	}
	
	newHash->m_magNum=MAGIC_NUMBER;
/*	
	newHash->m_size = 0;
	newHash->m_maxCollisionsEver = 0;
	newHash->m_counterOfOperation = 0;
	newHash->m_counterOfCollisions = 0;
*/
	newHash->m_hashFunction = _hashFunction;
	
	for(i=0 ; i < newHash->m_capacity ; ++i)
	{
		newHash->m_data[i]=EMPTY;
	}
	
	return newHash;
}
 
 
void HashSetDestroy(HashSet* _set)
{
	if((NULL==_set)||(MAGIC_NUMBER != _set->m_magNum))
	{
		return;
	}
	
	_set->m_magNum = 0;
	
	free(_set->m_data);
	free(_set);
}

ADTErr HashSetAdd(HashSet* _set, size_t _data)
{
	HashStatus res;
	size_t firstKey,realKey,collisions;

	if(NULL==_set)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_set->m_size == _set->m_capacity)
	{
		return ERR_OVERFLOW;
	}
	
	res = HashSearch(_set,_data,&firstKey,&collisions,&realKey);
	
	UpdateCounters(_set,collisions);
	
	switch (res)
	{
		case OK:
			return ERR_ALREADY_EXISTS;
			break;
		
		case EMPTY:
			_set->m_data[realKey] = (int)_data;
			++(_set->m_size);
			break;
		
		case REMOVED:
			_set->m_data[firstKey] = (int)_data;
			++(_set->m_size);
			break;
			
		case NOT_FOUND:
			return ERR_OVERFLOW;
			break;
	}

	return ERR_OK;
}


ADTErr HashSetRemove(HashSet* _set, size_t _data)
{
	HashStatus res;
	size_t firstKey,realKey,collisions;

	if(NULL==_set)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	res = HashSearch(_set,_data,&firstKey,&collisions,&realKey);
	
	UpdateCounters(_set,collisions);
	
	if (res == OK)
	{
		_set->m_data[realKey] = REMOVED;
		--(_set->m_size);
		return ERR_OK;
	}else
	{
		return ERR_NOT_FOUND;
	}
}


int HashSetContains(HashSet* _set, size_t _data)
{
	HashStatus res;
	size_t key1,key2,collisions;

	if(NULL==_set)
	{
		return FALSE;
	}
	
	res = HashSearch(_set,_data,&key1,&collisions,&key2);
	
	UpdateCounters(_set,collisions);
	
	return (OK == res) ? TRUE : FALSE;
}


size_t HashSetSize(const HashSet* _set)
{
	if(NULL==_set)
	{
		return 0;
	}
	
	return _set->m_size;
}

 
ADTErr HashSetStatistics(const HashSet* _set, size_t *_maxCollisionsEver, float *_averageCollisions)
{
	if((NULL==_set)||(NULL==_maxCollisionsEver)||(NULL==_averageCollisions))
	{
		return ERR_NOT_INITIALIZED;
	}
	
	*_maxCollisionsEver = _set->m_maxCollisionsEver;
	
	if(_set->m_counterOfOperation > 0)
	{
		*_averageCollisions = (float)(_set->m_counterOfCollisions)/(float)(_set->m_counterOfOperation);
	}else
	{
		*_averageCollisions=0;
	}
	
	return ERR_OK;
} 


void HashSetForEach(const HashSet* _set, void (*_userFunction)(size_t _data))
{
	size_t i, data;
	HashStatus res;
	
	for(i=0 ; i <_set->m_capacity ; ++i)
	{
		res=GetData(_set,i,&data);
		if(res == OK)
		{
			_userFunction(data);
		}
	}
}



 
static HashStatus HashSearch(const HashSet *_set, size_t _data, size_t *_firstKey, size_t *_collisions,size_t *_realKey )
{
	size_t key, colls, newData;
	HashStatus res;
	int wasRemoved;

	wasRemoved = FALSE;
	
	key = getHashKey(_set,_data);

	for(colls=0 ; colls < _set->m_capacity ; ++colls)
	{
		res=GetData(_set,key,&newData);
		
		switch(res)
		{
			case OK:
				if(newData == _data)
				{
					*_realKey = key;
					*_collisions=colls;
					return OK;
				}
				break;
			
			case EMPTY:
				*_realKey = key;
				*_collisions=colls;
				return (wasRemoved) ? REMOVED : EMPTY;
				break;
				
			case REMOVED:
				if (!wasRemoved)
				{
					wasRemoved = TRUE;
					*_firstKey = key;
				}
				break;
			case NOT_FOUND:
				break; 			
		}
				
		key=Rehash(_set,key);
	}
	
	*_realKey = key;
	*_collisions=colls;

	return (wasRemoved) ? REMOVED : NOT_FOUND;
}


static size_t getHashKey(const HashSet *_set,size_t _data)
{
	return ((_set->m_hashFunction(_data))%(_set->m_capacity));
}


static size_t Rehash(const HashSet *_set, size_t _key)
{
	return ((_key+1)%(_set->m_capacity));
}


static HashStatus GetData(const HashSet *_set, size_t _key, size_t *_data)
{
	int val;
	
	val = _set->m_data[_key];

	if ((val != REMOVED)&&(val != EMPTY))
	{
		*_data = (size_t)_set->m_data[_key];
		val = OK;
	}

	return val;
}


static void UpdateCounters(HashSet *_set,size_t _collisions)
{
	if (_collisions > _set->m_maxCollisionsEver)
	{
		_set->m_maxCollisionsEver = _collisions;
	}
	
	++(_set->m_counterOfOperation);
	(_set->m_counterOfCollisions)+=_collisions;
}
 
 
 
 
 
 
 
 
 

