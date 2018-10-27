

#include "Trie.h"
#include <iostream>


void writeTrie(Trie* triePtr, const std::string& str, ITrie::LongInt val)
{
	bool res = triePtr->TryWrite(str,val);
	
	std::cout<<"Tried to write ("<<str<<","<<val<<") with"<<(res?"":"out")<<" success.\n";
}

void readTrie(const Trie* triePtr, const std::string& str)
{
	ITrie::LongInt val;
	bool res = triePtr->TryRead(str,val);
	
	std::cout<<"Tried to read ("<<str<<","<<val<<") with"<<(res?"":"out")<<" success.\n";
}

void deleteTrie(Trie* triePtr, const std::string& str)
{
	triePtr->Delete(str);
	
	std::cout<<"Tried to delete ("<<str<<").\n";
}

int main()
{

	char* buffer_ptr = new char[Trie::BUFFER_SIZE];
	Trie* myTriePtr = Trie::TrieCreate(buffer_ptr);
//read/write
	
	writeTrie(myTriePtr,"abc",1);
	readTrie(myTriePtr,"abc");	
	
	writeTrie(myTriePtr,"abd",2);
	readTrie(myTriePtr,"abd");
	
	writeTrie(myTriePtr,"bcd",3);
	readTrie(myTriePtr,"bcd");
		
	readTrie(myTriePtr,"a");	
	
	writeTrie(myTriePtr,"",-1);
	readTrie(myTriePtr,"");	
	
	writeTrie(myTriePtr,"xyz",11);
	readTrie(myTriePtr,"xyz");	
	
	readTrie(myTriePtr,"xyzq");		

//save and destroy

	myTriePtr->Save("file");
	
	myTriePtr->~Trie();
	delete[] (buffer_ptr);

//make new and load
	buffer_ptr = new char[Trie::BUFFER_SIZE];	
	myTriePtr = Trie::TrieCreate(buffer_ptr);

	myTriePtr->Load("file");
	std::cout<<"\n\n\n";
	
//read
	readTrie(myTriePtr,"abc");

	readTrie(myTriePtr,"xyz");
	
	readTrie(myTriePtr,"a");

	readTrie(myTriePtr,"xyz");

//delete and read	
	deleteTrie(myTriePtr,"abc");
	readTrie(myTriePtr,"abc");

	deleteTrie(myTriePtr,"xyz");
	readTrie(myTriePtr,"xyz");

	readTrie(myTriePtr,"bcd");
	readTrie(myTriePtr,"");


	return 0;
}
