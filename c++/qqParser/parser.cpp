
#include <stdexcept>
#include "parser.h"

Parser::Parser() :
	m_tokenizer(new Tokenizer) ,m_analyzer(new Analyzer)
{}

Parser::~Parser()
{
	delete m_tokenizer;
	delete m_analyzer;
}


void Parser::ParseFile(const string& _fileName)
{
	m_file.open(_fileName.c_str());

	if(!m_file.good())
	{
		throw runtime_error("Wrong file name !");
	}
	
	m_analyzer->Init();
	
	string nextLine;
	size_t lineNum = 1;

	while(1)
	{
		getline(m_file,nextLine);
		
		if(!m_file.good())
		{
			break;
		}
	
		m_tokenizer->Tokenize(nextLine);
		
		if(0 < m_tokenizer->GetSize())
		{
			m_analyzer->AnalizeLine(*m_tokenizer,lineNum);
		}
		
		++lineNum;
	}
	
	m_analyzer->Finish();
	
	m_file.close();
}









