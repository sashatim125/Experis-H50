

#include "virtIO_t.h"

const string VirtIO_t::s_StatusStrs[] = 
	{
		"ok_e",
		"cant_open_file_e",
		"bad_access_e",
		"writeErr_e",
		"readErr_e"
	};


//public:

VirtIO_t::VirtIO_t():
	m_status(cant_open_file_e), m_isOpen(false)
{}
	
//ends with "cant_open_file_e" status
VirtIO_t::VirtIO_t(const string& _name, const string& _mode):
	m_pathname(_name), m_mode(_mode),
	m_status(cant_open_file_e), m_isOpen(false)
{}

VirtIO_t::~VirtIO_t()
{
	if(IsOpen())
	{
		fclose(m_file);
	}
}

//throws if have open file
void VirtIO_t::SetNameAndMode(const string & _name, const string& _mode)
{
	if(m_isOpen)
	{
		throw runtime_error("can't set name or mode to open file");
	}
	
	m_pathname = _name;
	m_mode = _mode;
}

pair<string,string> VirtIO_t::GetNameAndMode()const
{
	return pair<string,string>(m_pathname,m_mode);
}

const string& VirtIO_t::VirtIO_t::GetStatus()const
{
	return s_StatusStrs[m_status];
}
	
bool VirtIO_t::IsOpen()const
{
	return m_isOpen;
}
	
size_t VirtIO_t::GetLength()const
{
	if(!m_isOpen)
	{
		throw runtime_error("can't get length of unopen file");
	}
	
	long pos = ftell(m_file);
	
	fseek(m_file,0,SEEK_END);
	
	long size = ftell(m_file);
	
	fseek(m_file,pos,SEEK_SET);
	
	return size;	 
}
	
void VirtIO_t::OpenFile()
{
	if(m_isOpen)
	{
		throw runtime_error("file already open");
	}
	
	if(0 == (m_file = fopen(m_pathname.c_str(),m_mode.c_str())))
	{
		throw runtime_error("can't open the file");
	}
	
	m_isOpen = true;
	m_status = ok_e;
	
}

void VirtIO_t::CloseFile()
{
	if(!m_isOpen)
	{
		throw runtime_error("no open file");
	}
	
	fclose(m_file);
	m_isOpen = false;
	m_status = cant_open_file_e;
}
	
void VirtIO_t::SetStatus(Status _st)
{
	m_status = _st;
}
	

FILE*& VirtIO_t::GetFile()
{
	return m_file;
}
	





