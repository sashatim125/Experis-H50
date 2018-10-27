#ifndef __JUMPSTRING_H__
#define __JUMPSTRING_H__

#include "stringManip.h"

namespace advcpp
{

class JumpString : public StringManip
{
public:

class StringIterator : public StringManip::StringIterator
{
public:

	explicit inline
	StringIterator(SpecialString& _ss,unsigned _jump);

//	virtual
//	~StringIterator()
	
	virtual
	void FirstChar();
	
	virtual
	void Next();
	
	virtual
	bool HasNext() ;
	
//	virtual
//	char GetChar() ;
	
protected:

//	SpecialString::StringIterator* GetMyIter();

	void Jump();
	
private:

	unsigned m_jump;
};

	explicit inline
	JumpString(SpecialString& _ss,unsigned _jump = 1);

//	virtual
//	~ToUpperString();
	
	virtual inline
	JumpString::StringIterator* GetIter();
	
//	virtual
//	void Print();

protected:

//	SpecialString& GetMyString();

private:

	unsigned m_jumpSize;
};

}//namespace advcpp

using namespace advcpp;

inline
JumpString::JumpString(SpecialString& _ss,unsigned _jump) :
StringManip(_ss), m_jumpSize(_jump)
{}

inline
JumpString::StringIterator::StringIterator(SpecialString& _ss,unsigned _jump) :
StringManip::StringIterator(_ss), m_jump(_jump)
{}

inline
JumpString::StringIterator* JumpString::GetIter()
{
	return new JumpString::StringIterator(GetMyString(),m_jumpSize);
}



#endif //__JUMPSTRING_H__

