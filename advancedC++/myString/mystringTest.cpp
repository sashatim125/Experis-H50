

#include "simpleString.h"
#include "toUpperString.h"
#include "jumpString.h"
#include <iostream>


int main()
{
	SpecialString *str = new SimpleString("my StRiNg");
	
	str->Print();
	
	std::cout<<std::endl<<std::endl;
	
	SpecialString *str1 = new ToUpperString(*str);
	
	str1->Print();

	std::cout<<std::endl<<std::endl;
	
	str->Print();
			
	std::cout<<std::endl<<std::endl;

	SpecialString *str2 = new JumpString(*str);
	
	str2->Print();

	std::cout<<std::endl<<std::endl;



	return 0;
}







