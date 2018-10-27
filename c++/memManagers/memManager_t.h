
#ifndef __MEM_MANAGER_T_H__
#define __MEM_MANAGER_T_H__

#include <cstdlib>

class MemManager_t
{
public:
	
					MemManager_t() : m_currPos(0), m_size(0) {}
	inline		
	virtual			~MemManager_t() = 0;
	
	//get current position
	inline
	size_t 			GetPos()const;
	
	//set current position
	//return true on success or false otherwise
	inline
	virtual void 	SetPos(size_t _pos);
	
	//check if the memory is empty
	inline
	bool 			IsMemEmpty()const;
	
	//get actual(used) size
	inline
	size_t 			GetActualSize()const;
	
	//read _numOfBytes from current position
	//return number of bytes actually read
	virtual size_t 	Read(void* _buff, size_t _numOfBytes) = 0;
	
	//read _numOfBytes from user provided position
	//return number of bytes actually read
	virtual size_t 	Read(void* _buff, size_t _numOfBytes, size_t _pos) = 0;
	
	//write _numOfBytes on current position
	//return number of bytes actually written
	virtual size_t 	Write(const void* _buff, size_t _numOfBytes) = 0;
	
	//write _numOfBytes on user provided position
	//return number of bytes actually written
	virtual size_t 	Write(const void* _buff, size_t _numOfBytes, size_t _pos) = 0;
	
protected:

	inline
	void 			SetActualSize(size_t _size);
	
private:
	//copying is forbidden
					MemManager_t(const MemManager_t& _mp);
	
	MemManager_t&	operator=(const MemManager_t& _mp);
	
	//current position	
	size_t m_currPos;
	
	//actual size
	size_t m_size;

};

	inline		
			MemManager_t::~MemManager_t() {}


	inline
	size_t	MemManager_t::GetPos()const
	{
		return m_currPos;
	}
	
	inline
	void 	MemManager_t::SetPos(size_t _pos)
	{
		if(_pos > m_size)
		{
			throw -1;
		}
		
		m_currPos = _pos;
		return ;
		
		
	}
	
	inline
	bool	MemManager_t::IsMemEmpty()const
	{
		return (0 == m_size);
	}
	
	inline
	size_t	MemManager_t::GetActualSize()const
	{
		return m_size;
	}
	
	inline
	void	MemManager_t::SetActualSize(size_t _size)
	{
		m_size = (m_size < _size) ? _size : m_size;
	}
	





#endif //__MEM_MANAGER_T_H__

