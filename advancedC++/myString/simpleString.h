#ifndef __SIMPLESTRING_H__
#define __SIMPLESTRING_H__

#include <string>

#include "specialString.h"

namespace advcpp
{

class SimpleString : public SpecialString
{
public:

class StringIterator : public SpecialString::StringIterator
{
public:

	explicit
	StringIterator(SimpleString& _ss);

	virtual
	~StringIterator()
	{}

	virtual
	void FirstChar();
	
	virtual
	void Next();
	
	virtual
	bool HasNext() ;
	
	virtual
	char GetChar() ;
	
private:

	std::string& m_strRef;
	std::string::iterator m_it;
	
};

	SimpleString();
	
	explicit
	SimpleString(const std::string& _s);

	virtual
	~SimpleString()
	{}
	
	virtual
	SimpleString::StringIterator* GetIter();
	
	virtual
	void Print() ;
	
private:

	std::string m_str;
};

}//namespace advcpp

#endif //__SIMPLESTRING_H__

