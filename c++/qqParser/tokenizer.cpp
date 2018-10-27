

#include <cstring>

#include "tokenizer.h"


const char Tokenizer::s_tokensDelimitersArr[] = "()[]{};<>=+-*&";
const char Tokenizer::s_blankDelimitersArr[] = " \t\n\r\0";
const string Tokenizer::s_emptyString("");

const set<char> Tokenizer::s_tokensDelimiters 
	(s_tokensDelimitersArr, s_tokensDelimitersArr+strlen(s_tokensDelimitersArr));

const set<char> Tokenizer::s_blankDelimiters
	(s_blankDelimitersArr, s_blankDelimitersArr+strlen(s_blankDelimitersArr));


void Tokenizer::Tokenize(const string& _str)
{
	size_t pos, next, len = _str.length();
	
	m_tokens.clear();
	
	for(pos = 0, next = 0; next <= len ; ++next)
	{
		if(s_blankDelimiters.find(_str[next]) != s_blankDelimiters.end())
		{
			if(next > pos)
			{
				m_tokens.push_back(string(_str,pos,next-pos));
			}
			pos = next+1;
			
			continue;		
		}
		if(s_tokensDelimiters.find(_str[next]) != s_tokensDelimiters.end())
		{
			if(next > pos)
			{
				m_tokens.push_back(string(_str,pos,next-pos));
			}
			
			m_tokens.push_back(string(1,_str[next]));
			pos = next+1;
		}
	}
	
	 m_nextToken = m_tokens.begin();
}


const string& Tokenizer::GetNextToken()
{	
	if(m_nextToken == m_tokens.end())
	{
		return s_emptyString;
	}
	
	return *(m_nextToken++);
}


