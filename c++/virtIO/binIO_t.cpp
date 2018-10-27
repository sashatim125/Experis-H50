

#include "binIO_t.h"

BinIO_t& BinIO_t::operator>>(void* _buf)
{
	if(!_buf)
	{
		m_wasShiftOper = false;
		throw runtime_error("Null pointer!");
	}
	m_buf = _buf;
	m_setToWrite = false;
	m_wasShiftOper = true;
	
	return *this;
}


BinIO_t& BinIO_t::operator<<(const void* _buf)
{
	if(!_buf)
	{
		m_wasShiftOper = false;
		throw runtime_error("Null pointer!");
	}
	m_buf = (void*)_buf;
	m_setToWrite = true;
	m_wasShiftOper = true;
	
	return *this;
}



void BinIO_t::operator,(int _len)
{
	if(_len <= 0)
	{
		throw runtime_error("Non positive length!");
	}
	if(!m_wasShiftOper)
	{
		throw runtime_error("Incorrect use of operator, !");
	}
	
	if(m_setToWrite)
	{	
		if(!IsOpen())
		{	
			SetStatus(writeErr_e);
			throw runtime_error("write error - no open file!");
		}
	
		pair<string,string> nameAndMode(GetNameAndMode());
		
		if(nameAndMode.second == "r")
		{
			SetStatus(bad_access_e);
			throw runtime_error("write error - no access!");
		}
	
		if(1 != fwrite(m_buf,(size_t)_len,1,GetFile()))
		{	
			SetStatus(writeErr_e);
			throw runtime_error("write error !");
		}
	}else
	{
		if(!IsOpen())
		{		
			SetStatus(readErr_e);
			throw runtime_error("read error - no open file!");
		}
	
		pair<string,string> nameAndMode(GetNameAndMode());
	
		if( nameAndMode.second == "w"  || 
			nameAndMode.second == "a")
		{
			SetStatus(bad_access_e);
			throw runtime_error("read error - no access!");
		}	
	
		if(1 != fread(m_buf,(size_t)_len,1,GetFile()))
		{
			SetStatus(readErr_e);
			throw runtime_error("read error !");
		}
	}

	SetStatus(ok_e);
	m_wasShiftOper = false;
}





