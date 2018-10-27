
#ifndef __BINIO_T_H__
#define __BINIO_T_H__

#include "virtIO_t.h"

class BinIO_t : public VirtIO_t
{
	public:
	
	BinIO_t() :m_wasShiftOper(false)
	{}
	
	BinIO_t(const string & _name, const string& _mode) :
		VirtIO_t(_name,_mode), m_wasShiftOper(false)
	{}
		
	virtual ~BinIO_t()
	{}

	//void SetNameAndMode(const string & _name, const string& _mode);

	//pair<string,string> GetNameAndMode()const;

	//const string& GetStatus()const;
	
	//bool IsOpen()const;
	
	//size_t GetLength()const;
	
	//void OpenFile();

	//void CloseFile();
	
	virtual
	BinIO_t& operator<<(const char& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}

	virtual
	BinIO_t& operator<<(const unsigned char& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}

	virtual
	BinIO_t& operator<<(const short& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator<<(const unsigned short& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator<<(const int& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator<<(const unsigned int& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator<<(const long& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator<<(const unsigned long& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}

	virtual
	BinIO_t& operator<<(const float& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator<<(const double& _val)
	{
		(*this)<<(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator>>(char& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}

	virtual
	BinIO_t& operator>>(unsigned char& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}

	virtual
	BinIO_t& operator>>(short& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator>>(unsigned short& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator>>(int& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator>>(unsigned int& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator>>(long& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator>>(unsigned long& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}

	virtual
	BinIO_t& operator>>(float& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}
	
	virtual
	BinIO_t& operator>>(double& _val)
	{
		(*this)>>(&_val),(int)sizeof(_val);
		return *this;
	}
	
	//to use with "," , like file << &object , length
	BinIO_t& operator>>(void* _buf);

	BinIO_t& operator<<(const void* _buf);

	void operator,(int _len);
	
	protected:

	private:
	//uncopyable objects
	BinIO_t(const BinIO_t& _bio);
	BinIO_t& operator=(const BinIO_t& _bio);
	
	
	void* m_buf;
	bool m_wasShiftOper;
	bool m_setToWrite;

};









#endif //__BINIO_T_H__

