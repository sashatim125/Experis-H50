
#include <cstring>
#include <cctype>

#include "string_t.h"


//static initialization
unsigned int String_t::m_initCapacity = GetLeastPowerOf2(DEFAULT_INIT_CAPACITY);
bool String_t::m_caseSensitive = true;


//public

	//constructors
	
	String_t::String_t()
	{
		CreateFrom(NULL);
	}
	
	String_t::String_t(const char* _str)
	{
		CreateFrom(_str);	
	}
	
	String_t::String_t(const String_t &_otherStr)
	{
		CreateFrom(_otherStr.m_string);
	}
	
	String_t::~String_t()
	{
		delete[] m_string;
	}
	
	//operators
	
	String_t& String_t::operator=(const String_t& _otherStr)
	{
		
		if(this != &_otherStr && 0== ResizeString(_otherStr.m_length))
		{
			strcpy(m_string, _otherStr.m_string);
			m_length = _otherStr.m_length;
		}
			
		return *this;
	}
	
	String_t& String_t::operator+=(const String_t &_otherStr)
	{
		return *this += _otherStr.m_string;
	}
	
	
	String_t& String_t::operator+=(const char* _str)
	{
		unsigned int newLength;
		unsigned int len;
		if(_str)
		{
			newLength =  this->m_length + (len = (unsigned)strlen(_str)) ;
		
			if(0== ResizeString(newLength))
			{
				memcpy(m_string+m_length, _str, len+1);
				m_length = newLength;
			}
		}
		return *this;
	}

//shortcut for compare functions
#define COMPARE StringCmp(m_string, _otherStr.m_string, m_caseSensitive)

	bool String_t::operator<(const String_t &_otherStr) const
	{
		return (0> COMPARE);
	}
	
	bool String_t::operator>(const String_t &_otherStr) const
	{
		return (0< COMPARE);
	}
	
	bool String_t::operator<=(const String_t &_otherStr) const
	{
		return (0>= COMPARE);
	}
	
	bool String_t::operator>=(const String_t &_otherStr) const
	{
		return (0<= COMPARE);
	}
	
	bool String_t::operator==(const String_t &_otherStr) const
	{
		return (0== COMPARE);
	}
	
	bool String_t::operator!=(const String_t &_otherStr) const
	{
		return (0!= COMPARE);
	}
#undef COMPARE
	
#define GET_MEMBER (_index < m_length) ? m_string[_index] : m_string[m_length];	
	
	char& String_t::operator[](unsigned int _index)
	{
		return GET_MEMBER;
	}
	
	const char& String_t::operator[](unsigned int _index) const
	{
		return GET_MEMBER;
	}
	
#undef GET_MEMBER

	String_t String_t::operator()(unsigned int _start, unsigned int _len) const
	{
		String_t resStr;
		
		if(_start+_len <= m_length)
		{
			if (0== resStr.ResizeString(_len))
			{
				memcpy(resStr.m_string, this->m_string + _start, _len);
				resStr.m_string[_len] = '\0';				
			}
		}
		return resStr;
	}
	
	//mem_functions
	
	void String_t::SetString(const char *_str)
	{
		unsigned int len;
		if(_str && 0== ResizeString(len = (unsigned)strlen(_str)))
		{
			strcpy(m_string, _str);
			m_length = len;
		}
	}
	
	void String_t::SetString(const String_t _otherStr)
	{
		this->SetString(_otherStr.m_string);
	}
	
	const char* String_t::GetString() const
	{
		return m_string;
	}
	
	String_t& String_t::ToUpperCase()
	{
		char *str = m_string;
		
		while(*str)
		{
			*str = (char)toupper(*str);
			++str;
		}
		
		return *this;
	}

	String_t& String_t::ToLowerCase()
	{
		char *str = m_string;
		
		while(*str)
		{
			*str = (char)tolower(*str);
			++str;
		}
		
		return *this;
	}
	
	String_t& String_t::Prepend(const char* _str)
	{
		unsigned int newLength;
		unsigned int len;
		
		if(_str)
		{
			newLength = this->m_length + (len = (unsigned)strlen(_str)) ;
		
			if(0== ResizeString(newLength))
			{
				memmove(m_string+len, m_string, m_length+1);
				memcpy(m_string, _str, len);
				m_length = newLength;
			}
		}			
		return *this;
	}
	
	String_t& String_t::Prepend(const String_t &_otherStr)
	{
		return this->Prepend(_otherStr.m_string);
	}
	
	bool String_t::Contains(const String_t &_otherStr) const
	{
		return (NULL!=strstr(m_string,_otherStr.m_string));
	}
	
	long String_t::GetFirstOccurrence(char _c) const
	{
		char* charPtr;
		
		charPtr = strchr(m_string,_c);
		
		return (charPtr) ? charPtr-m_string : -1;
	
	}
	
	long String_t::GetLastOccurrence(char _c) const
	{
		char* charPtr;
		
		charPtr = strrchr(m_string,_c);
		
		return (charPtr) ? charPtr-m_string : -1;
	
	}


	
	
//private

	void String_t::CreateFrom(const char* _str)
	{
		m_length = (_str) ? (unsigned)strlen(_str) : 0;
		
		m_capacity = GetLeastPowerOf2(m_length+1);
		
		if(m_initCapacity > m_capacity)
		{
			m_capacity = m_initCapacity;
		}
		
		m_string = new char[m_capacity];
		
		if(_str)
		{
			strcpy(m_string,_str);
		}else
		{
			m_string[0]='\0';
		}
	}
	
	int String_t::ResizeString(unsigned int _newLength)
	{
		char* tmpStr;
		unsigned int tmpCapacity;
	
		if(_newLength >= m_capacity)
		{
			tmpCapacity = GetLeastPowerOf2(_newLength+1);
		
			if(NULL== (tmpStr = StrRealloc(m_string,tmpCapacity)))
			{
				return -1;
			}else
			{
				m_string = tmpStr;
				m_capacity = tmpCapacity;
			}
		}
		
		return 0;
	}

	//static

	unsigned int String_t::GetLeastPowerOf2(unsigned int _n) 
	{
		unsigned int next = 1;
	
		while(next<_n)
		{
			next*=2;
		}

		return next;
	}
	
	char* String_t::StrRealloc(char* _str,unsigned int _newSize)
	{
		char* tmpStr = _str;
	
		if(NULL!= (_str = new char[_newSize]))
		{	
			strcpy(_str,tmpStr);
			delete[] tmpStr;
		}
		
		return _str;
	}	
	
	int String_t::StringInsCaseCmp(const char* _str1, const char* _str2)
	{
		unsigned long i;
		
		for(i=0 ;
			_str1[i]!='\0' && _str2[i]!='\0' && tolower(_str1[i]) == tolower(_str2[i]);
			++i)
		{	
		}
		
		return tolower(_str1[i]) - tolower(_str2[i]);	
	}
	
	
	int String_t::StringCmp(const char* _str1, const char* _str2,bool _isCaseSen)
	{
		return _isCaseSen ? strcmp(_str1, _str2) : StringInsCaseCmp(_str1, _str2);
	
	
	}	
	
	
	
	
	
	
	

//overloaded IO operators

	ostream& operator<<(ostream& os, const String_t &_str)
	{
		os << _str.GetString();
		
		return os;
	}
	
#define EXPECTED_STRING_SIZE 1024
	
	istream& operator>>(istream& is, String_t &_str)
	{
		char s[EXPECTED_STRING_SIZE];
		
		is >> s;
		
		_str.SetString(s);	
	
		return is;
	}

