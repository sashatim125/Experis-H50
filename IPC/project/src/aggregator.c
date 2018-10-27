

#include <stdlib.h>
#include <pthread.h>
#include <assert.h>


#include "aggregator.h"


#ifndef TRUE
#define TRUE 1
#endif
 
#ifndef FALSE
#define FALSE 0
#endif

struct Aggregator
{
	size_t m_capacity;
	
	size_t m_numOfLocks;
	
	pthread_mutex_t *m_locks;
	
	HashMap* m_hashMap;
		
	HashFunction m_hashFunc;
	
	void (*m_upFunc)(void*, void*);
	
	void* (*m_insFunc)(void*);
	
	void (*m_readFunc)(void*,void*);
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


static size_t GetLockNumber(Aggregator* _agg, const void* _key)
{
	return (_agg->m_hashFunc(_key) % _agg->m_capacity) % _agg->m_numOfLocks;
}



Aggregator* Aggregator_Create(size_t _numOfLocks, size_t _capacity,
	HashFunction _hashFunc, EqualityFunction _keysEqualFunc,
	void (*_upFunc)(void*, void*),
	void* (*_insFunc)(void*),
	void (*_readFunc)(void*,void*))
{
	Aggregator* agg;
	size_t i,j;
	int res;
	
	assert(0<_numOfLocks);
	assert(0<_capacity);
	assert(NULL!=_hashFunc);
	assert(NULL!=_keysEqualFunc);
	assert(NULL!=_upFunc);
	assert(NULL!=_insFunc);
	assert(NULL!=_readFunc);
	
	if(NULL == (agg = malloc(sizeof(Aggregator))))
	{
		return NULL;
	}
	
	if(NULL == (agg->m_locks = malloc(_numOfLocks * sizeof(pthread_mutex_t))))
	{
		free(agg);
		return NULL;
	}

	for(i=0 , res = 0; i < _numOfLocks && 0==res ; ++i)
	{
		res+= pthread_mutex_init(agg->m_locks + i,NULL);
	}
	
	if(res)
	{
		for(j=0 ; j < i ; ++j)
		{
			pthread_mutex_destroy(agg->m_locks + j);
		}
		free(agg->m_locks);
		free(agg);
		return NULL;
	}
	
	_capacity = GetNearestPrime(_capacity);

	if(NULL == (agg->m_hashMap = HashMap_Create(_capacity,_hashFunc,_keysEqualFunc)))
	{
		for(j=0 ; j < _numOfLocks ; ++j)
		{
			pthread_mutex_destroy(agg->m_locks + j);
		}
		free(agg->m_locks);
		free(agg);
		return NULL;
	}

	agg->m_capacity = _capacity;
	agg->m_numOfLocks = _numOfLocks;
	agg->m_hashFunc = _hashFunc;
	agg->m_upFunc = _upFunc;
	agg->m_insFunc = _insFunc;
	agg->m_readFunc = _readFunc;

	return agg;
}

void Aggregator_Destroy(Aggregator* _agg)
{
	size_t i;
	
	assert(NULL!=_agg);
	
	HashMap_Destroy(&(_agg->m_hashMap),NULL,NULL);
	for(i=0 ; i < _agg->m_numOfLocks ; ++i)
	{
		pthread_mutex_destroy(_agg->m_locks + i);
	}
	free(_agg->m_locks);
	free(_agg);
}


int Aggregator_Upsert(Aggregator* _agg, const void* _key, void* _context)
{
	void* value;
	size_t lockNum;
	
	assert(NULL!=_agg);
	
	lockNum = GetLockNumber(_agg,_key);

	if(MAP_SUCCESS == HashMap_Find(_agg->m_hashMap,_key,&value))
	{
		if(0!=pthread_mutex_lock(_agg->m_locks + lockNum))
		{
			return -1;
		}
		_agg->m_upFunc(_context,value);
		if(0!=pthread_mutex_unlock(_agg->m_locks + lockNum))
		{
			return -2;
		}
		
	}else
	{
		if(0!=pthread_mutex_lock(_agg->m_locks + lockNum))
		{
			return -3;
		}
		if(NULL == (value = _agg->m_insFunc(_context)))
		{
			pthread_mutex_unlock(_agg->m_locks + lockNum);
			return -4;
		}
	
		if(MAP_SUCCESS != HashMap_Insert(_agg->m_hashMap,_key,value))
		{
			pthread_mutex_unlock(_agg->m_locks + lockNum);
			return -5;
		}
		if(0!=pthread_mutex_unlock(_agg->m_locks + lockNum))
		{
			return -6;
		}
	}

	return 0;
}


int Aggregator_Read(Aggregator* _agg, const void* _key, void* _context)
{
	void* value;
	size_t lockNum;
	
	assert(NULL!=_agg);
	
	lockNum = GetLockNumber(_agg,_key);
	
	if(0!=pthread_mutex_lock(_agg->m_locks + lockNum))
	{
		return -1;
	}

	if(MAP_SUCCESS != HashMap_Find(_agg->m_hashMap,_key,&value))
	{
		pthread_mutex_unlock(_agg->m_locks + lockNum);
		return -2;
	}
	
	_agg->m_readFunc(_context,value);
	
	if(0!=pthread_mutex_unlock(_agg->m_locks + lockNum))
	{
		return -3;
	}
	
	return 0;
}











