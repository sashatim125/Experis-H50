



#include <iostream>

#include "configuration.h"
#include "iniFileParser.h"






int main()
{
	IniFileParser parser("./config.ini");

	const std::map<std::string, IniFileSection>& sections =
		parser.GetIniSections();
		
		
	std::map<std::string, IniFileSection>::const_iterator it = sections.begin();
	std::map<std::string, IniFileSection>::const_iterator end = sections.end();
	
	/*
	for(; it != end; ++it)
	{
		std::cout<<"id = "<<(*it).first<<"\n";
		
		std::map<std::string, std::string>::const_iterator it1 = (*it).second.m_varValPairs.begin();
		std::map<std::string, std::string>::const_iterator end1 = (*it).second.m_varValPairs.end();
		
		for(; it1 != end1; ++it1)
		{
			std::cout<<(*it1).first<<" = "<<(*it1).second<<"\n";
		}
		std::cout<<std::endl;
	}*/
	
	
	
	for(; it != end; ++it)
	{
		Configuration conf((*it).second);
		
		std::cout<<"m_id= "<<conf.m_id<<"\n";
		std::cout<<"m_type= "<<conf.m_type<<"\n";
		std::cout<<"m_floor= "<<conf.m_floor<<"\n";
		std::cout<<"m_room= "<<conf.m_room<<"\n";
		std::cout<<"m_log= "<<conf.m_log<<"\n";
		std::cout<<"m_config= "<<conf.m_config<<"\n";
		std::cout<<std::endl;
	}











	return 0;
}


