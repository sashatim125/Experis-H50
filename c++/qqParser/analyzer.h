
#ifndef __ANALYZER_H_
#define __ANALYZER_H_

#include <set>
#include <map>
#include <string>

#include "tokenizer.h"

using namespace std;

class Analyzer
{
	public:
	
	Analyzer(){};
	
	//call before parsing new file
	void Init();

	void AnalizeLine(Tokenizer& _t, size_t _lineNum);
	
	//call after parsing of the file is finished
	void Finish();

	private:
	//non-copyable
	Analyzer(const Analyzer& _a);
	const Analyzer& operator=(const Analyzer& _a);
	
	

	static set<string> s_predefinedTypes;
	static set<string> s_keyWords;
	static set<string> s_operators;
	static set<string> s_predefTokens;
	
	static const string s_predefinedTypesStrings[];
	static const string s_keyWordsStrings[];
	static const string s_operatorsStrings[];
	static const string s_predefTokensStrings[];
	
	
	map<string,int> m_enclosuresCounters;
	map<string,int> m_operatorChecker;
	
	set<string> m_symbolTable;
	
	bool m_programStarted;
	
	bool m_predefTypeEncountered;
	
	void AnalyzeToken(const string& _token,  size_t _lineNum);
	
	bool IsValidVarName(const string& _token)const;
	
	bool CheckEnclosure(const string& _token, const string& _open, const string& _close,  size_t _lineNum);
	
	bool CheckOperators(const string& _token, size_t _lineNum);
	

};





























#endif//__ANALYZER_H_

