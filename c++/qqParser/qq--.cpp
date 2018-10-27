
#include <iostream>
#include <stdexcept>
#include "parser.h"


int main(int argc, char* argv[])
{
	int i ;
	Parser p;

	for(i = 1; i < argc; ++i)
	{
		cout<<endl<<endl;
		
		try
		{
			p.ParseFile(argv[i]);
		}
		catch (runtime_error& _e)
		{
			cerr<<"Error with "<<argv[i]<<" -- "<<_e.what()<<endl<<endl;
		} 
	}
	
	return 0;
}

