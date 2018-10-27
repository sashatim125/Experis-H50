
#ifndef __PARSER_H__
#define __PARSER_H__

#include <fstream>

#include "tokenizer.h"
#include "analyzer.h"

using namespace std;

class Parser
{
	public:
	
	Parser();
	~Parser();
	
	void ParseFile(const string& _fileName);//throws on wrong file
	
	private:
	//non-copyable
	Parser(const Parser& _p);
	const Parser& operator=(const Parser& _p);
	
	ifstream m_file;

	Tokenizer* m_tokenizer;
	
	Analyzer* m_analyzer;
};













#endif //__PARSER_H__


