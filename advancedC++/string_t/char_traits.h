
#ifndef __CHAR_TRAITS_H__
#define __CHAR_TRAITS_H__

#include <cstddef>

template <class charT>
struct Char_traits
{
	//>0 if c1>c2, ==0 if c1==c2, 
	static int Comp(const charT& c1, const charT& c2);

	static std::size_t Length (const charT* s);
	
	static charT ToUpper(const charT& _c);
	
	static charT ToLower(const charT& _c);
	

private:
	Char_traits();
//	~Char_traits();

};


template <>
int Char_traits<char>::Comp(const char& c1, const char& c2)
{
	return c1-c2;
}

template <>
std::size_t Char_traits<char>::Length (const char* s)
{
	std::size_t len;
	
	for (len=0; s[len]; ++len)
	{}
	
	return len;
}	

template <>
int Char_traits<wchar_t>::Comp(const wchar_t& c1, const wchar_t& c2)
{
	return c1-c2;
}

template <>
std::size_t Char_traits<wchar_t>::Length (const wchar_t* s)
{
	std::size_t len;
	
	for (len=0; s[len]; ++len)
	{}
	
	return len;
}



















#endif //__CHAR_TRAITS_H__
