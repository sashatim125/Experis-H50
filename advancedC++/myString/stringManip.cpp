
#include <iostream>	
#include "stringManip.h"	
	

StringManip::StringIterator::StringIterator(SpecialString& _ss) :
	m_it(_ss.GetIter())
{}


StringManip::StringIterator::~StringIterator()
{
	delete m_it;
}

void StringManip::StringIterator::FirstChar()
{
	m_it->FirstChar();
}
	

void StringManip::StringIterator::Next()
{
	m_it->Next();
}
	
bool StringManip::StringIterator::HasNext() 
{
	return m_it->HasNext();
}
	
char StringManip::StringIterator::GetChar() 
{
	return m_it->GetChar();
}


void StringManip::Print()
{
	StringManip::StringIterator* it = GetIter();
	
	for(; it->HasNext() ; it->Next())
	{
		std::cout<<it->GetChar();
	}
}









