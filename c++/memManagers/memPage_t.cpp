
#include <cstring>

#include "memPage_t.h"

//public:

	size_t MemPage_t::Read(void* _buff, size_t _numOfBytes)
	{
		return Read(_buff, _numOfBytes, GetPos());	
	}

	size_t MemPage_t::Read(void* _buff, size_t _numOfBytes, size_t _pos)
	{
		size_t numOfBytesToRead;
		size_t asize = GetActualSize();
	
		if(!_buff || 0==_numOfBytes || _pos >= asize)
		{
			return 0;
		}
		
		numOfBytesToRead = (_pos+_numOfBytes <= asize) ?
			_numOfBytes : asize - _pos;
		
		memcpy(_buff, m_buffer+_pos, numOfBytesToRead);
		SetPos(_pos + numOfBytesToRead);
		
		return numOfBytesToRead;		
	}
	
	size_t MemPage_t::Write(const void* _buff, size_t _numOfBytes)
	{
		return Write(_buff, _numOfBytes, GetPos());
	}

	size_t MemPage_t::Write(const void* _buff, size_t _numOfBytes, size_t _pos)
	{
		size_t numOfBytesToWrite;
		size_t asize = GetActualSize();
	
		if(!_buff || 0==_numOfBytes || _pos > asize)
		{
			return 0;
		}
		
		numOfBytesToWrite = (_pos+_numOfBytes <= m_capacity) ?
		_numOfBytes : m_capacity - _pos;
		
		memcpy(m_buffer+_pos, _buff, numOfBytesToWrite);
		
		_pos+=numOfBytesToWrite;
		if((_pos > asize))
		{
			SetActualSize(_pos);
		}
		SetPos(_pos);
		
		return numOfBytesToWrite;
	}



















