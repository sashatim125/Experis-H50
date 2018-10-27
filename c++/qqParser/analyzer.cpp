
#include <cctype>
#include <algorithm> 
#include <iostream>

#include "analyzer.h"

const string Analyzer::s_predefinedTypesStrings[] =
	{"char", "short", "int", "long", "float", "double", "void"};
const string Analyzer::s_keyWordsStrings[] =
	{"if", "else", "for" , "while", "class", 
		"private", "public", "protected", "main", "const", "virtual"};
const string Analyzer::s_operatorsStrings[] =
	{"++", "--", "==", "->" , "=", "+", "-", "*", "&", "<<", ">>"};
const string Analyzer::s_predefTokensStrings[] =
	{"(", ")", "[", "]" , "{" , "}", ";", "<", ">" , "=", "+", "-", "*", "&"};

#define NUMOFELEM(ARR) (sizeof(ARR)/sizeof((ARR)[0]))

set<string> Analyzer::s_predefinedTypes
	(s_predefinedTypesStrings, s_predefinedTypesStrings + NUMOFELEM(s_predefinedTypesStrings));
set<string> Analyzer::s_keyWords
	(s_keyWordsStrings, s_keyWordsStrings + NUMOFELEM(s_keyWordsStrings));
set<string> Analyzer::s_operators
	(s_operatorsStrings, s_operatorsStrings + NUMOFELEM(s_operatorsStrings));
set<string> Analyzer::s_predefTokens
	(s_predefTokensStrings, s_predefTokensStrings + NUMOFELEM(s_predefTokensStrings));

void Analyzer::Init()
{
	m_programStarted = false;
	m_predefTypeEncountered = false;

	m_enclosuresCounters["("] = 0;
	m_enclosuresCounters["["] = 0;
	m_enclosuresCounters["{"] = 0;	
	m_enclosuresCounters["if"] = 0;
	
	m_operatorChecker["+"] = 0;
	m_operatorChecker["-"] = 0;
}

static void PrintEnclErr(const pair<string,int>& _p)
{
	if(_p.second > 0)
	{
		cout<<"error - "<<_p.second<<" '"<<_p.first<<"' not closed"<<endl;
	}
}

void Analyzer::Finish()
{
	m_enclosuresCounters["if"] = 0;
	
	for_each(m_enclosuresCounters.begin(), m_enclosuresCounters.end(), PrintEnclErr);	
}


bool Analyzer::IsValidVarName(const string& _token) const
{
	return (isalpha(_token[0]) || _token[0] == '_');
}



void Analyzer::AnalizeLine(Tokenizer& _t, size_t _lineNum)
{
	static const string emptyString("");
	
	const string* token = &_t.GetNextToken();
	
	while (*token != emptyString)
	{
		AnalyzeToken(*token,_lineNum);
		
		token = &_t.GetNextToken();
	}
}


bool Analyzer::CheckEnclosure(const string& _token, const string& _open, const string& _close,  size_t _lineNum)
{
	int* counter;
	
	if(_close == _token)
	{
		if(0 < *(counter = &m_enclosuresCounters[_open]))
		{
			--(*counter);
		}else
		{
			cout<<"line "<<_lineNum<<": error - "<<_close<<" without "<<_open<<"\n"<<endl;
		}
		return true;
	}
	if(_open == _token)
	{
		++(m_enclosuresCounters[_open]);
		
		return true;
	}
	return false;	
} 


bool Analyzer::CheckOperators(const string& _token, size_t _lineNum)
{
	map<string,int>::iterator it, it1;
	
	if((it = m_operatorChecker.find(_token)) != m_operatorChecker.end())
	{
		if(2 > it->second)
		{
			++(it->second);
		}
		else
		{
			cout<<"line "<<_lineNum<<": error - no operator ";
			cout<<_token<<_token<<_token<<"\n"<<endl;
			it->second = 0;
		}
		for(it1 = m_operatorChecker.begin(); it1 != m_operatorChecker.end(); ++it1)
		{	
			if (it1 != it)
			{
				it1->second = 0;
			}
		}
		return true;
	}
	
	for(it = m_operatorChecker.begin(); it != m_operatorChecker.end(); ++it)
	{
		it->second = 0;
	}
	
	return false;
}


void Analyzer::AnalyzeToken(const string& _token,  size_t _lineNum)
{
		
	if(!m_programStarted)
	{
		if(_token != "main")
		{
			cout<<"line "<<_lineNum<<": error - the program doesn't start with 'main'\n"<<endl;
		}
		m_programStarted = true;
	}

	if (CheckEnclosure(_token,"(",")",_lineNum) ||
		CheckEnclosure(_token,"[","]",_lineNum) ||
		CheckEnclosure(_token,"{","}",_lineNum) ||
		CheckEnclosure(_token,"if","else",_lineNum))
	{
		return;
	}
	
	if (CheckOperators(_token,_lineNum))
	{
		return;
	}
	
	if (s_predefinedTypes.find(_token) != s_predefinedTypes.end())
	{
		if(m_predefTypeEncountered)
		{
			cout<<"line "<<_lineNum<<": error - multiple type declaration\n"<<endl;
			m_predefTypeEncountered = false;
		}else
		{
			m_predefTypeEncountered = true;
		}
		return;
	}
	
	if(m_predefTypeEncountered)
	{
		if (s_keyWords.find(_token) != s_keyWords.end() ||
			s_operators.find(_token) != s_operators.end() ||
			s_predefTokens.find(_token) != s_predefTokens.end())
		{
			cout<<"line "<<_lineNum<<": error - illegal variable name\n"<<endl;
		}else
		{
			if(m_symbolTable.find(_token) != m_symbolTable.end())
			{
				cout<<"line "<<_lineNum<<": error - variable '"<<_token<<"' already declared\n"<<endl;			
			}else
			{
				if(IsValidVarName(_token))
				{
					m_symbolTable.insert(_token);
				}else
				{
					cout<<"line "<<_lineNum<<": error - illegal variable name\n"<<endl;
				}
			}
		}
		m_predefTypeEncountered = false;
	}else
	{
		if (!(s_keyWords.find(_token) != s_keyWords.end() ||
			s_operators.find(_token) != s_operators.end() ||
			s_predefTokens.find(_token) != s_predefTokens.end()) &&
			IsValidVarName(_token) &&
			m_symbolTable.find(_token) == m_symbolTable.end())
		{
			cout<<"line "<<_lineNum<<": error - "<<_token<<" is not declared\n"<<endl;
		}
	}
}











