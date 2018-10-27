
#ifndef __MEM_PAGE_T_H__
#define __MEM_PAGE_T_H__

#include "memManager_t.h"

class MemPage_t : public MemManager_t
{
	public:
	
	//construct with default size
	inline					MemPage_t();
	
	//construct with the user provided size
	inline
	explicit				MemPage_t(size_t _size);
	
	inline
	virtual					~MemPage_t();

	
	//check if the page is full
	inline
	bool					IsMemFull()const;
	
	//get the capacity(length) of the page
	inline
	size_t					GetCapacity()const;
	
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
	
	protected:
	
	private:
	
	//copying is forbidden
							MemPage_t(const MemPage_t& _mp);
	
	MemPage_t& 				operator=(const MemPage_t& _mp);
	
	//for the default constructor
	static const size_t s_defaultPageSize = 1024;
	
	//the page capacity
	size_t m_capacity;
	
	//the memory buffer
	char* m_buffer;	
	
};

	inline	MemPage_t::MemPage_t()
	{
		m_capacity = s_defaultPageSize;
		m_buffer = new char[m_capacity];
	}
	
	inline	MemPage_t::MemPage_t(size_t _size)
	{
		m_capacity = (_size > 0) ? _size : s_defaultPageSize;
		m_buffer = new char[m_capacity];
	}

	inline	MemPage_t::~MemPage_t()
	{
		delete[] m_buffer;
	}
	
	inline
	bool	MemPage_t::IsMemFull()const
	{
		return (GetActualSize() == m_capacity);
	}
	

	inline
	size_t	MemPage_t::GetCapacity()const
	{
		return m_capacity;
	}
	
	
	
	


#endif //__MEM_PAGE_T_H__

