
#ifndef __ASCIIIO_T_H__
#define __ASCIIIO_T_H__

#include "virtIO_t.h"

class AsciiIO_t : public VirtIO_t
{
	public:
	
	AsciiIO_t()
	{}
	
	AsciiIO_t(const string & _name, const string& _mode) :
		VirtIO_t(_name,_mode)
	{}
		
	virtual ~AsciiIO_t()
	{}

	//void SetNameAndMode(const string & _name, const string& _mode);

	//pair<string,string> GetNameAndMode()const;

	//const string& GetStatus()const;
	
	//bool IsOpen()const;
	
	//size_t GetLength()const;
	
	//void OpenFile();

	//void CloseFile();
	
	virtual
	AsciiIO_t& operator<<(const char& _val)
	{
		WriteToFile(_val,"%c");
		return *this;
	}

	virtual
	AsciiIO_t& operator<<(const unsigned char& _val)
	{
		WriteToFile(_val,"%hhu");
		return *this;
	}

	virtual
	AsciiIO_t& operator<<(const short& _val)
	{
		WriteToFile(_val,"%hd");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator<<(const unsigned short& _val)
	{
		WriteToFile(_val,"%hu");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator<<(const int& _val)
	{
		WriteToFile(_val,"%d");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator<<(const unsigned int& _val)
	{
		WriteToFile(_val,"%u");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator<<(const long& _val)
	{
		WriteToFile(_val,"%ld");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator<<(const unsigned long& _val)
	{
		WriteToFile(_val,"%lu");
		return *this;
	}

	virtual
	AsciiIO_t& operator<<(const float& _val)
	{
		WriteToFile(_val,"%f");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator<<(const double& _val)
	{
		WriteToFile(_val,"%lf");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator>>(char& _val)
	{
		ReadFromFile(_val,"%hhd");
		return *this;
	}

	virtual
	AsciiIO_t& operator>>(unsigned char& _val)
	{
		ReadFromFile(_val,"%hhu");
		return *this;
	}

	virtual
	AsciiIO_t& operator>>(short& _val)
	{
		ReadFromFile(_val,"%hd");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator>>(unsigned short& _val)
	{
		ReadFromFile(_val,"%hu");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator>>(int& _val)
	{
		ReadFromFile(_val,"%d");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator>>(unsigned int& _val)
	{
		ReadFromFile(_val,"%u");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator>>(long& _val)
	{
		ReadFromFile(_val,"%ld");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator>>(unsigned long& _val)
	{
		ReadFromFile(_val,"%lu");
		return *this;
	}

	virtual
	AsciiIO_t& operator>>(float& _val)
	{
		ReadFromFile(_val,"%f");
		return *this;
	}
	
	virtual
	AsciiIO_t& operator>>(double& _val)
	{
		ReadFromFile(_val,"%lf");
		return *this;
	}
	
	protected:

	//throw if there is no open file or read error 
	template<class T>
	void ReadFromFile(T& _t, const string& _format);
	
	//throw if there is no open file or write error 
	template<class T>
	void WriteToFile(const T& _t, const string& _format);
	
	private:
	//uncopyable objects
	AsciiIO_t(const AsciiIO_t& _aio);
	
	AsciiIO_t& operator=(const AsciiIO_t& _aio);
	
	

};

template<class T>
void AsciiIO_t::ReadFromFile(T& _t, const string& _format)
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
	
	if(1 != fscanf(GetFile(),_format.c_str(),&_t))
	{
		SetStatus(readErr_e);
		throw runtime_error("read error !");
	}
	
	SetStatus(ok_e);	
}


//I know that it is a "C" style and can be done better
//with "C++" functionality, but we are building a "C"
//file wrapper, don't we ?..
#define BUFFER_SIZE 128

template<class T>
void AsciiIO_t::WriteToFile(const T& _t, const string& _format)
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
	
	char buf[BUFFER_SIZE];
	int size;
	//for knowing the real size in characters
	if(0 >= (size = sprintf(buf,_format.c_str(),_t)))
	{
		SetStatus(writeErr_e);
		throw runtime_error("write error !");
	}
	
	if(size != fprintf(GetFile(),_format.c_str(),_t))
	{
		SetStatus(writeErr_e);
		throw runtime_error("write error !");
	}
	
	SetStatus(ok_e);	
}











#endif //__ASCIIIO_T_H__

