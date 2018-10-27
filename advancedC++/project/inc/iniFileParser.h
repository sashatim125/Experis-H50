#ifndef __INIFILEPARSER_H__
#define __INIFILEPARSER_H__

#ifndef interface
#define interface struct
#endif //interface

// 
//  @file iniFileParser.h
//  @brief .ini files parser
//	
//  @details  see comments
//  
//
//  @author Alexander Timoshenko sashatim125@gmail.com
// 
//

#include <string>
#include <map>


namespace advcpp
{

struct IniFileSection
{
	//Section title
	std::string m_sectionTitle;
	
	//var = val pairs
	std::map<std::string, std::string> m_varValPairs;
};

class IniFileParser
{
private:
	static const std::string s_blankCharacters;

public:

	//may throw runtime_error on wrong _filePath or wrong .ini file content
	explicit
	IniFileParser(const std::string& _filePath);
	
	//key = sectionTitle
	const std::map<std::string, IniFileSection>& 
	GetIniSections() const;

private:
	//uncopyable objects
	IniFileParser(const IniFileParser&);
	const IniFileParser& operator=(const IniFileParser&);
	
	//key = sectionTitle
	std::map<std::string, IniFileSection> m_sections;
	
	static std::string StingTrim(const std::string& _str);
};


}//endof namespace advcpp







#endif //__INIFILEPARSER_H__

