
#include <iostream>

#include "simpleString.h"

using namespace advcpp;

SimpleString::StringIterator::StringIterator(SimpleString& _ss)
: 	m_strRef(_ss.m_str)
,	m_it(_ss.m_str.begin())
{}

void SimpleString::StringIterator::FirstChar()
{
	m_it = m_strRef.begin();
}
	
void SimpleString::StringIterator::Next()
{
	++m_it;
}
	
bool SimpleString::StringIterator::HasNext() 
{
	return m_it != m_strRef.end();
}

char SimpleString::StringIterator::GetChar() 
{
	return (m_it != m_strRef.end()) ? *m_it : '\0';
}

SimpleString::SimpleString()
{}
	
SimpleString::SimpleString(const std::string& _s) :
m_str(_s) 
{}
	

SimpleString::StringIterator* SimpleString::GetIter()
{
	return new SimpleString::StringIterator(*this);
}
	
void SimpleString::Print()
{
	SimpleString::StringIterator* it = GetIter();
	
	for(; it->HasNext() ; it->Next())
	{
		std::cout<<it->GetChar();
	}
}

	


