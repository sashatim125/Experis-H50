
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


#include <sstream>
#include <fstream>
#include <stdexcept>

#include "iniFileParser.h"

using namespace advcpp;

const std::string IniFileParser::s_blankCharacters = " \t\r\n";

const std::map<std::string, IniFileSection>& 
IniFileParser::GetIniSections() const
{
	return m_sections;
}

std::string IniFileParser::StingTrim(const std::string& _str)
{
	size_t start = _str.find_first_not_of(s_blankCharacters);
	
	if(std::string::npos == start)
	{
		return "";
	}
	
	size_t end   = _str.find_last_not_of (s_blankCharacters);
	
	return _str.substr(start, end - start +1);
}

#define THROW_ERROR do\
{\
	std::ostringstream os;\
	os<<"Error in config file "<<_filePath<<" in line "<<lineCount<<std::endl;\
	throw std::runtime_error(os.str());\
}while(false)


IniFileParser::IniFileParser(const std::string& _filePath)
{
	std::ifstream iniFile(_filePath.c_str());
	if(! iniFile.good())
	{
		std::ostringstream os;
		os<<"Error in config file "<<_filePath<<" : no such file! "<<std::endl;
		throw std::runtime_error(os.str());
	}
	
	size_t lineCount = 0;
	IniFileSection nextSection;
	
	do
	{
		std::string nextLine;
	
		if(! getline(iniFile,nextLine).good())
		{
			break;
		}
		++lineCount;
		
		//comments line
		if(';' == nextLine[0] || '#' == nextLine[0])
		{
			continue;
		}
		//empty line
		if(nextLine.find_first_not_of(s_blankCharacters) == std::string::npos)
		{
			continue;
		}
		
		size_t start, end;
		//section title
		if((start = nextLine.find_first_of("[")) != std::string::npos &&
			(end = nextLine.find_last_of("]")) != std::string::npos &&
			start < end)
		{
			if(start != nextLine.find_first_not_of(s_blankCharacters) ||
				end != nextLine.find_last_not_of(s_blankCharacters) ||
				start == end)
			{
				THROW_ERROR;
			}
		
			if(! nextSection.m_sectionTitle.empty())
			{	
				m_sections[nextSection.m_sectionTitle] = nextSection;
				nextSection.m_sectionTitle.clear();
				nextSection.m_varValPairs.clear();
			}
			
			nextSection.m_sectionTitle = nextLine.substr(start+1, end - start -1);
			
			continue;	
			
		}else if(nextSection.m_sectionTitle.empty())			
		{
			THROW_ERROR;
		}
		
		// variable = value
		if((end = nextLine.find("=")) == std::string::npos)
		{
			THROW_ERROR;
		}
		
		nextSection.m_varValPairs[StingTrim(nextLine.substr(0,end))] =
			StingTrim(nextLine.substr(end+1, std::string::npos));
			
	}while(true);
	
	if(! nextSection.m_sectionTitle.empty())
	{	
		m_sections[nextSection.m_sectionTitle] = nextSection;
	}

	iniFile.close();
}

#undef THROW_ERROR






