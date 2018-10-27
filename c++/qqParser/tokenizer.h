
#ifndef __TOKENIZER_H_
#define __TOKENIZER_H_


#include <string>
#include <list>
#include <set>

using namespace std;

class Tokenizer
{
	public:
	
	Tokenizer() {}
	
	void Tokenize(const string& _str);

	inline
	size_t GetSize() const;
	
	const string& GetNextToken(); //returns empty string on end

	private:
	//non-copyable
	Tokenizer(const Tokenizer& _t);
	Tokenizer& operator=(const Tokenizer& _t);

	static const char s_tokensDelimitersArr[];
	static const char s_blankDelimitersArr[];
	static const string s_emptyString;
	
	static const set<char> s_tokensDelimiters ;	
	static const set<char> s_blankDelimiters ;
	
		
	list<string> m_tokens;
	
	list<string>::iterator m_nextToken;	
};

inline
size_t Tokenizer::GetSize() const
{
	return m_tokens.size();
}































#endif //__TOKENIZER_H_

