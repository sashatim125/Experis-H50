
#ifndef __TEXCEPTION_T_H__
#define __TEXCEPTION_T_H__

#include <string>

using namespace std;

#define THROW(TYPE, EXOBJ, DESC) do\
{\
	throw(TException_t<TYPE>(EXOBJ, DESC, __FILE__, __LINE__));\
}while(0)


template <typename ExType>
class TException_t
{
	public:

	TException_t(const ExType& _ex, const string& _desc, const string& _fileName, int _line) :
		m_exObj(_ex), m_desc(_desc), m_fileName(_fileName), m_line(_line) {}

	const ExType& GetExObj()const		{return m_exObj;}
	
	const string& GetDesc()const	 	{return m_desc;}
	
	const string& GetFilename()const	{return m_fileName;}
	
	const int&    GetLine()const		{return m_line;}


	private:
	
	ExType m_exObj;
	
	string m_desc;
	
	string m_fileName;
	
	int m_line;



};


#endif//__TEXCEPTION_T_H__

