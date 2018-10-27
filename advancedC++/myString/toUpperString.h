#ifndef __TOUPPERSTRING_H__
#define __TOUPPERSTRING_H__


#include "stringManip.h"

namespace advcpp
{

class ToUpperString : public StringManip
{
public:

class StringIterator : public StringManip::StringIterator
{
public:

	explicit inline
	StringIterator(SpecialString& _ss);

//	virtual
//	~StringIterator()

//	virtual
//	void FirstChar();
	
//	virtual
//	void Next();
	
//	virtual
//	bool HasNext() ;
	
	virtual
	char GetChar() ;
	
protected:

//	SpecialString::StringIterator* GetMyIter();

};

	explicit inline
	ToUpperString(SpecialString& _ss);

//	virtual
//	~ToUpperString();
	
	virtual inline
	ToUpperString::StringIterator* GetIter();
	
//	virtual
//	void Print();

protected:

//	SpecialString& GetMyString();

};

}//namespace advcpp

using namespace advcpp;

inline
ToUpperString::ToUpperString(SpecialString& _ss) :
StringManip(_ss)
{}

inline
ToUpperString::StringIterator::StringIterator(SpecialString& _ss) :
StringManip::StringIterator(_ss)
{}

inline
ToUpperString::StringIterator* ToUpperString::GetIter()
{
	return new ToUpperString::StringIterator(GetMyString());
}



#endif //__TOUPPERSTRING_H__

