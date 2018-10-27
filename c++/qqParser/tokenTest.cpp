

#include <iostream>
#include "tokenizer.h"


int main()
{
	string st;
	Tokenizer t ;
	size_t i;
	
	cout<<"Enter the string to test the tokenizer :";
	getline(cin,st);
	
	t.Tokenize(st);
	
	for(i=0 ; i < t.GetSize() ; ++i)
	{
		cout<<t.GetNextToken()<<endl;
	}

	return 0;
}










