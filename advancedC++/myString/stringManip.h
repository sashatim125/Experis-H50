#ifndef __STRINGMANIP_H__
#define __STRINGMANIP_H__


#include "specialString.h"

namespace advcpp
{

class StringManip : public SpecialString
{
public:

class StringIterator : public SpecialString::StringIterator
{
public:

	explicit
	StringIterator(SpecialString& _ss);

	virtual
	~StringIterator();

	virtual
	void FirstChar();
	
	virtual
	void Next();
	
	virtual
	bool HasNext() ;
	
	virtual
	char GetChar() ;

protected:

	inline
	SpecialString::StringIterator* GetMyIter();
	
private:

	SpecialString::StringIterator* m_it;
	
};

	explicit inline
	StringManip(SpecialString& _ss);

	virtual inline
	~StringManip()=0;
	
	virtual inline
	StringManip::StringIterator* GetIter();
	
	virtual
	void Print() ;

protected:
	inline
	SpecialString& GetMyString();
	
private:

	SpecialString& m_str;
};

}//namespace advcpp

using namespace advcpp;

inline
StringManip::StringManip(SpecialString& _ss):
	m_str(_ss)
{}

inline
StringManip::~StringManip()
{}

inline
SpecialString& StringManip::GetMyString()
{
	return m_str;
}

inline
StringManip::StringIterator* StringManip::GetIter()
{
	return new StringManip::StringIterator(GetMyString());
}

inline
SpecialString::StringIterator* StringManip::StringIterator::GetMyIter()
{
	return m_it;
}


#endif //__STRINGMANIP_H__

