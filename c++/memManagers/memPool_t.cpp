

#include "memPool_t.h"

size_t MemPool_t::DefaultPageSize = InitialDefaultPageSize;

//public:
	
	MemPool_t::MemPool_t() :m_currPageNum(0)
	{
		MemPage_t *page = new MemPage_t(DefaultPageSize);
		m_pages.push_back(page);	
	}
	
	MemPool_t::~MemPool_t()
	{
		size_t i, numOfPages = m_pages.size();
		
		for(i=0 ; i < numOfPages ; ++i)
		{
			delete m_pages[i];
		}
	}
	
	void	MemPool_t::SetPos(size_t _pos)
	{
		if(_pos > GetActualSize())
		{
			throw -1;
		}

		MemManager_t::SetPos(_pos);
		
		for(m_currPageNum = 0 ; _pos > m_pages[m_currPageNum]->GetActualSize() ; 
			_pos -= m_pages[m_currPageNum]->GetActualSize(), ++m_currPageNum)
		{}
		m_pages[m_currPageNum]->SetPos(_pos);
	}
	
	size_t MemPool_t::Read(void* _buff, size_t _numOfBytes)
	{
		return Read(_buff, _numOfBytes, 0, true);	
	}
	
	size_t MemPool_t::Read(void* _buff, size_t _numOfBytes, size_t _pos)
	{
		return Read(_buff, _numOfBytes, _pos, false);	
	}
	
	size_t MemPool_t::Write(const void* _buff, size_t _numOfBytes)
	{
		return Write(_buff, _numOfBytes, 0, true);
	}
	
	size_t MemPool_t::Write(const void* _buff, size_t _numOfBytes, size_t _pos)
	{
		return Write(_buff, _numOfBytes, _pos, false);
	}



//private:

	
	size_t MemPool_t::Read(void* _buff, size_t _numOfBytes, size_t _pos, bool _fromCurrPos)
	{
		size_t numOfBytesToRead, numOfBytesReadInCurrPage;
		size_t unreadBytes;
		size_t buffPos;
		size_t asize = GetActualSize();
		
		if(!_buff || 0==_numOfBytes || (!_fromCurrPos && _pos > asize))
		{
			return 0;
		}
		
		if(_fromCurrPos)
		{
			_pos = GetPos();
		}else
		{
			SetPos(_pos);
		}
		
		numOfBytesToRead = (_pos+_numOfBytes <= asize) ?
			_numOfBytes : asize - _pos;
		
		for(unreadBytes = numOfBytesToRead, buffPos=0 ;
			unreadBytes > 0 ; )
		{
			if(m_pages[m_currPageNum]->GetPos() == m_pages[m_currPageNum]->GetCapacity())
			{
				m_pages[++m_currPageNum]->SetPos(0);
			}	
		
			numOfBytesReadInCurrPage = m_pages[m_currPageNum]->Read(
				(char*)_buff + buffPos,unreadBytes);
		
			unreadBytes -= numOfBytesReadInCurrPage;
			
			buffPos += numOfBytesReadInCurrPage;
			
			_pos += numOfBytesReadInCurrPage;
		}
		
		MemManager_t::SetPos(_pos);
		
		return numOfBytesToRead;

	}
	
	
	size_t MemPool_t::Write(const void* _buff, size_t _numOfBytes, size_t _pos, bool _fromCurrPos)
	{
		size_t numOfBytesWrittenInCurrPage;
		size_t unwrittenBytes;
		size_t buffPos;
		
		if(!_buff || 0==_numOfBytes || (!_fromCurrPos && _pos > GetActualSize()))
		{
			return 0;
		}
		
		if(_fromCurrPos)
		{
			_pos = GetPos();
		}else
		{
			SetPos(_pos);
		}
		
		for(unwrittenBytes = _numOfBytes, buffPos=0 ;
			unwrittenBytes > 0 ; )
		{
			if(m_pages[m_currPageNum]->GetPos() == m_pages[m_currPageNum]->GetCapacity())
			{
				++m_currPageNum;
			}
			if(m_pages.size() == m_currPageNum)
			{
				m_pages.push_back(new MemPage_t(DefaultPageSize));
				
			}
			m_pages[m_currPageNum]->SetPos(0);
			
			numOfBytesWrittenInCurrPage = m_pages[m_currPageNum]->Write(
				(char*)_buff + buffPos, unwrittenBytes);
		
			unwrittenBytes -= numOfBytesWrittenInCurrPage;
			
			buffPos += numOfBytesWrittenInCurrPage;
			
			_pos += numOfBytesWrittenInCurrPage;
		}
			
		if(_pos > GetActualSize())
		{
			SetActualSize(_pos);
		}
		MemManager_t::SetPos(_pos);
		
		return _numOfBytes;
	}




























	

