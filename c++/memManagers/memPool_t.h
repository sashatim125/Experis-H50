
#ifndef __MEM_POOL_T_H__
#define __MEM_POOL_T_H__

#include <vector>

#include "memPage_t.h"

using namespace std;

class MemPool_t : public MemManager_t
{
	public:
	
	//construct with 1 empty page
							MemPool_t();	
	
	virtual					~MemPool_t();
	
	//set current position
	//return true on success or false otherwise
	virtual void 			SetPos(size_t _pos);
	
	//get default page size
	inline
	size_t					GetDefaultPageSize()const;
	
	//set default page size 
	//_size should not be 0 !
	inline
	void					SetDefaultPageSize(size_t _size);
	
	//read _numOfBytes from current position
	//return number of bytes actually read
	virtual
	size_t					Read(void* _buff, size_t _numOfBytes);
	
	//read _numOfBytes from user provided position
	//return number of bytes actually read
	virtual
	size_t					Read(void* _buff, size_t _numOfBytes, size_t _pos);
	
	//write _numOfBytes on current position
	//return number of bytes actually written
	virtual
	size_t					Write(const void* _buff, size_t _numOfBytes);
	
	//write _numOfBytes on user provided position
	//return number of bytes actually written
	virtual
	size_t					Write(const void* _buff, size_t _numOfBytes, size_t _pos);

	
	private:
	
	//copying is forbidden
							MemPool_t(const MemPool_t& _mp);
	
	MemPool_t& 				operator=(const MemPool_t& _mp);
	
	size_t					Read(void* _buff, size_t _numOfBytes, size_t _pos, bool _fromCurrPos);
	
	size_t					Write(const void* _buff, size_t _numOfBytes, size_t _pos, bool _fromCurrPos);
	
	
	static const size_t InitialDefaultPageSize = 3;
	
	static 		 size_t DefaultPageSize;
	
	//current page number
	unsigned long m_currPageNum;
	
	//pages of the pool
	vector<MemPage_t*> m_pages;
	
};

	inline
	size_t MemPool_t::GetDefaultPageSize()const
	{
		return DefaultPageSize;
	}
	
	inline
	void	MemPool_t::SetDefaultPageSize(size_t _size)
	{
		DefaultPageSize = (_size > 0) ? _size : DefaultPageSize;
	}
















#endif //__MEM_POOL_T_H__

