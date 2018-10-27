
#ifndef __STRING_T_H__
#define __STRING_T_H__

#include <iostream>

using namespace std;

#define DEFAULT_INIT_CAPACITY 32

class String_t
{
	public:
	//con/destructors	
						String_t();
	
	explicit			String_t(const char* _str);
	
						String_t(const String_t &_otherStr);
	
						~String_t();
					
	//mem-functions
	
	//static
	
	inline static bool	GetCaseSensitive();
	
	//return previous CaseSensitive value
	inline static bool	SetCaseSensitive(bool _caseSensitive);
	
	inline 
	static unsigned int	GetInitCapacity();
	
	//Set the initial capacity as power of 2(at least as big as requested)
	//return previous InitCapacity
	inline
	static unsigned int	SetInitCapacity(unsigned int _initCapacity);
	
	//non-static
	
	String_t& 			operator=(const String_t &_otherStr);
	
	//concatenate parameter string to the object
	String_t&			operator+=(const char* _str);
	
	String_t&			operator+=(const String_t &_otherStr);
	
	//strings comparison (like in strcmp) depends on the CaseSensitive flag
	bool				operator<(const String_t &_otherStr) const;
	
	bool				operator>(const String_t &_otherStr) const;
	
	bool				operator<=(const String_t &_otherStr) const;
	
	bool				operator>=(const String_t &_otherStr) const;
	
	bool				operator==(const String_t &_otherStr) const;
	
	bool				operator!=(const String_t &_otherStr) const;
	
	//if _index out of boundaries , return (reference to)terminating 0
	char&				operator[](unsigned int _index);
	
	const char&			operator[](unsigned int _index) const;
	
	//warning : the returned object is on the HEAP
	String_t			operator()(unsigned int _start, unsigned int _len) const;
	
	//return the length (like strlen) of the string
	inline unsigned int GetLength() const;
	
	//return the capacity (really allocated memory) of the string 
	inline unsigned int GetCapacity() const;	
	
	void 			SetString(const char *_str);
	
	void 			SetString(const String_t _otherStr);
	
	const char* 	GetString() const;
	
	String_t&		ToUpperCase();

	String_t&		ToLowerCase();
	
	String_t&		Prepend(const char* _str);
	
	String_t&		Prepend(const String_t &_otherStr);
	
	bool			Contains(const String_t &_otherStr) const;
	
	//return the index of occurence or -1 if none
	long			GetFirstOccurrence(char _c) const;
	
	long			GetLastOccurrence(char _c) const;

	private:
	
	//members
	
	//static
	
	//default value is DEFAULT_INIT_CAPACITY
	static
	unsigned int	m_initCapacity;
	
	//default value is true
	static
	bool			m_caseSensitive;
					
	//non-static
	char 			*m_string;
	unsigned int 	m_length;
	unsigned int 	m_capacity;
	
	//functions
	
	//static
	
	//compute the power of 2 that is at greater or equal to _n
	static
	unsigned int	GetLeastPowerOf2(unsigned int _n);	
		
	//allocate new space of _newSize, 
	//copy there the string and free the previously allocated space
	//return the pointer to the new place or NULL if unsuccessful
	static
	char* 			StrRealloc(char* _str,unsigned int _newSize);
	
	//compair 2 strings insensitive to case
	static
	int 			StringInsCaseCmp(const char* _str1, const char* _str2);
	
	//compair 2 strings with/out case sensitivity
	static
	int 			StringCmp(const char* _str1, const char* _str2, bool _isCaseSen);
	
	//copy to the string in the class
	void 			CreateFrom(const char* _str);
	
	//resize the existing string
	//return 0 if success , !=0 otherwise;
	//_newLength does not include terminating '\0'
	int				ResizeString(unsigned int _newLength);
	
	
};

//overloaded IO operators

	ostream& 		operator<<(ostream& os, const String_t &_str);
	
	istream& 		operator>>(istream& is, String_t &_str);
	
//inline functions implementation
	
inline bool	String_t::GetCaseSensitive()
{
	return m_caseSensitive;
}
	
inline bool String_t::SetCaseSensitive(bool _caseSensitive)
{
	bool oldCaseSensitive = m_caseSensitive;
	m_caseSensitive = _caseSensitive;
	
	return oldCaseSensitive;
}

inline unsigned int	String_t::GetInitCapacity()
{
	return m_initCapacity;
}

inline unsigned int String_t::SetInitCapacity(unsigned int _initCapacity)
{
	unsigned int oldInitCapacity = m_initCapacity;
	m_initCapacity = GetLeastPowerOf2(_initCapacity);
	
	return oldInitCapacity;
}

inline unsigned int String_t::GetLength() const
{
	return m_length;	
}

inline unsigned int String_t::GetCapacity() const
{
	return m_capacity;
}



#endif //__STRING_T_H__

