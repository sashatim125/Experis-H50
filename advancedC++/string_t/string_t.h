
#ifndef __STRING_T_H__
#define __STRING_T_H__

#include <iostream>

#include "char_traits.h"
#include "buffer.h"

namespace advcpp
{

template <class CharT>
class String_t
{
public:

	static const std::size_t s_npos = ~0;

	String_t(std::size_t _capacity);
		
	explicit String_t(const CharT* _str);
	
template<>
	explicit String_t<char>(const CharT* _str ="");

template<>
	explicit String_t<wchar_t>(const CharT* _str =L"");

//copy ctor
//	String_t(const String_t &_otherStr);
	
//	String_t& operator=(const String_t &_otherStr);

	String_st& operator=(const CharT* _otherStr);
/*	
	//concatenate parameter string to the object
	String_t& operator+=(const CharT* _str);
	
	String_t& operator+=(const String_t &_otherStr);
*/	
	//strings comparison (like in strcmp) 
	bool operator<(const String_t &_otherStr) const;
	
	bool operator>(const String_t &_otherStr) const;
	
	bool operator<=(const String_t &_otherStr) const;
	
	bool operator>=(const String_t &_otherStr) const;
	
	bool operator==(const String_t &_otherStr) const;
	
	bool operator!=(const String_t &_otherStr) const;
	
//doesn't check index
	CharT& operator[](size_t _index);
	
	const CharT& operator[](size_t _index) const;
	
//checks index and throws std::out_of_range
	CharT& operator()(std::size_t _index);
	
	const CharT& operator()(std::size_t _index) const;
	
	//return the length (like strlen) of the string
	size_t Length() const;
	
	//return the capacity (really allocated memory) of the string 
	size_t Capacity() const;	
	
	const CharT* C_String() const;
	
	CharT* C_String();
/*	
	String_t& Prepend(const CharT* _str);
	
	String_t& Prepend(const String_t &_otherStr);
*/	
	std::size_t Find(const String_t &_otherStr) const;
/*	
	//return the index of occurence or -1 if none
	std::size_t GetFirstOccurrence(CharT _c) const;
	
	std::size_t GetLastOccurrence(CharT _c) const;
*/	
	private:

	Buffer<CharT> m_data;

	static int StringCmp(const CharT* _str1, const CharT* _str2);
	
	//copy to the string in the class
	void CreateFrom(const CharT* _str);
};

/*
template <class CharT>
	ostream& 		operator<<(ostream& os, const String_t<CharT> &_str);
	
template <class CharT>	
	istream& 		operator>>(istream& is, String_t<CharT> &_str);
*/
	
template <class CharT>
std::size_t String_t<CharT>::Capacity() const
{
	return m_data.Capacity();	
}

template <class CharT>
std::size_t String_t<CharT>::Length() const
{
	return Char_traits<CharT>::Length(m_data.Array());	
}

template <class CharT>
String_t::String_t(const CharT* _str)
{
	CreateFrom(_str);	
}

template <class CharT>	
String_t::String_t(const String_t &_otherStr)
{
	CreateFrom(_otherStr.m_string);
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
	
	String_t& String_t::operator=(const char *_str)
	{
		size_t len;
		if(_str && 0== ResizeString(len = (unsigned)strlen(_str)))
		{
			strcpy(m_string, _str);
			m_length = len;
		}
		return *this;
	}
	
	String_t& String_t::operator+=(const String_t &_otherStr)
	{
		return *this += _otherStr.m_string;
	}
	
	
	String_t& String_t::operator+=(const char* _str)
	{
		size_t newLength;
		size_t len;
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
#define COMPARE StringCmp(m_string, _otherStr.m_string)
//, m_caseSensitive)

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
	
//#define GET_MEMBER (_index < m_length) ? m_string[_index] : m_string[m_length];	
#define GET_MEMBER m_string[_index];
	
	char& String_t::operator[](size_t _index) 
	{
		return GET_MEMBER;
	}
	
	const char& String_t::operator[](size_t _index) const
	{
		return GET_MEMBER;
	}
	
#undef GET_MEMBER

	String_t String_t::operator()(size_t _start, size_t _len) const
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
	
	const char* String_t::GetString() const
	{
		return m_string;
	}
	
	String_t& String_t::Prepend(const char* _str)
	{
		size_t newLength;
		size_t len;
		
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
	
	int String_t::ResizeString(size_t _newLength)
	{
		char* tmpStr;
		size_t tmpCapacity;
	
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

	size_t String_t::GetLeastPowerOf2(size_t _n) 
	{
		size_t next = 1;
	
		while(next<_n)
		{
			next*=2;
		}

		return next;
	}
	
	char* String_t::StrRealloc(char* _str,size_t _newSize)
	{
		char* tmpStr = _str;
	
		if(NULL!= (_str = new char[_newSize]))
		{	
			strcpy(_str,tmpStr);
			delete[] tmpStr;
		}
		
		return _str;
	}	
	
	int String_t::StringCmp(const char* _str1, const char* _str2)
	{
		return strcmp(_str1, _str2);	
	}	
	
	
	
	

//overloaded IO operators

	ostream& operator<<(ostream& os, const String_t &_str)
	{
		os << _str.GetString();
		
		return os;
	}
	
#define EXPECTED_STRING_SIZE 1024
//what with strings bigger then 1024 ??????	
	istream& operator>>(istream& is, String_t &_str)
	{
		char s[EXPECTED_STRING_SIZE];
		
		is >> s;
		
		_str=(s);	
	
		return is;
	}
}//namespace


}//namespace
#endif //__STRING_T_H__

