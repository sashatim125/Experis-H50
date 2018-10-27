

#include <iostream>
#include <vector>

#include "array.h"
#include "dlist.h"

using namespace std;


int main()
{
	int choise;
	int cont;
	
	int nextInt;
	char nextChar;
	
	int* nextIntPtr;
	char* nextCharPtr;
	
	size_t index;
	char type;
	
	const int*  res1=0;
	const char* res2=0;
	
	Container<int>* contPtr1 = 0;
	Container<char>* contPtr2 = 0; 
	
	cont = 1;
	
	cout<<"=====Welcome to the Containers test !=====\n";
	
	while(cont)
	{
		cout<<"\n\nPlease choose one of the options :\n";
		cout<<"0 : exit;\n";	
		cout<<"1 : create an Array of int* OR;\n";
		cout<<"2 : create an Double linked list of int*;\n";
		cout<<"3 : create an Array of char* OR;\n";
		cout<<"4 : create an Double linked list of char*;\n";
		cout<<"5 : append\n";	
		cout<<"6 : prepend;\n";
		cout<<"7 : contains;\n";
		cout<<"8 : count;\n";
		cout<<"9 : find :\n";
		cout<<"10: index;\n";
		cout<<"11: insert;\n";
		cout<<"12: isEmpty;\n";
		cout<<"13: remove;\n";
		cout<<"14: removeAll;\n";
		cout<<"15: removeAndDelete;\n";
		cout<<"16: removeAndDeleteAll;\n";
	
		cin>>choise;
	
		switch (choise)
		{
			case 1:
				contPtr1 = new Array<int>;
				break;
			case 2:
				contPtr1 = new DLink<int>;
				break;
			case 3:
				contPtr2 = new Array<char>;
				break;
			case 4:
				contPtr2 = new DLink<char>;
				break;
			case 5:
				cout<<"Please center the index :";
				cin>>index;
				
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					nextIntPtr = new int;
					*nextIntPtr = nextInt;
					try
					{
						contPtr1->Append(nextIntPtr,index);
					}
					catch (string& str)
					{
						cerr<<str<<endl;
					}
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					nextCharPtr = new char;
					*nextCharPtr = nextChar;
					try
					{
						contPtr2->Append(nextCharPtr,index);
					}
					catch (string& str)
					{
						cerr<<str<<endl;
					}
				}
				break;
			case 6:
				cout<<"Please enter the index :";
				cin>>index;
							
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					nextIntPtr = new int;
					*nextIntPtr = nextInt;
					try
					{
						contPtr1->Prepend(nextIntPtr,index);
					}
					catch (string& str)
					{
						cerr<<str<<endl;
					}
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					nextCharPtr = new char;
					*nextCharPtr = nextChar;
					try
					{
						contPtr2->Prepend(nextCharPtr,index);
					}
					catch (string& str)
					{
						cerr<<str<<endl;
					}
				}
				break;
			case 7:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					cout << (contPtr1->Contains(nextInt)?"Yes":"No")<<endl;
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					cout << (contPtr2->Contains(nextChar)?"Yes":"No")<<endl;
				}
				break;
			case 8:
				cout<<"Count of int* container is "<<contPtr1->Count();
				cout<<" and Count of char* container is "<<contPtr2->Count()<<endl;
				break;
			case 9:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					res1 = contPtr1->Find(nextInt);
					if(res1)
					{
						cout<<"It's "<< *res1 <<endl;
					}else
					{
						cout<<"No such value !"<<endl;
					}
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					res2 = contPtr2->Find(nextChar);
					if(res2)
					{
						cout<<"It's "<< *res2 <<endl;
					}else
					{
						cout<<"No such value !"<<endl;
					}
				}
				break;
		case 10:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					try
					{
						cout<< "The index is "<<contPtr1->Index(nextInt)<<endl;
					}
					catch(string& str)
					{
						cerr<<str<<endl;
					}
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					try
					{
						cout<< "The index is "<<contPtr2->Index(nextChar)<<endl;
					}
					catch(string& str)
					{
						cerr<<str<<endl;
					}
				}
				break;
			case 11:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					nextIntPtr = new int;
					*nextIntPtr = nextInt;
					contPtr1->Insert(nextIntPtr);
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					nextCharPtr = new char;
					*nextCharPtr = nextChar;
					contPtr2->Insert(nextCharPtr);
				}
				break;
			case 12:
				cout<<"int* container is "<<( contPtr1->IsEmpty() ? "" : "not")<<" empty."<<endl;
				cout<<"char* container is "<<( contPtr2->IsEmpty() ? "" : "not")<<" empty."<<endl;
				break;
			case 13:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					try
					{
						cout<<contPtr1->Remove(nextInt)<<" was just removed."<<endl;
					}
					catch(string& str)
					{
						cerr<<str<<endl;
					}
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					try
					{
						cout<<contPtr2->Remove(nextChar)<<" was just removed."<<endl;
					}
					catch(string& str)
					{
						cerr<<str<<endl;
					}
				}
				break;
			case 14:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					contPtr1->RemoveAll();
				}
				if(type == 'c')
				{
					contPtr2->RemoveAll();
				}
				break;	
			case 15:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					cout<<"Please enter the integer :";
					cin>>nextInt;
					try
					{
						contPtr1->RemoveAndDelete(nextInt);
						cout<<"It was just removed and deleted."<<endl;
					}
					catch(string& str)
					{
						cerr<<str<<endl;
					}
				}
				if(type == 'c')
				{
					cout<<"Please enter the char :";
					cin>>nextChar;
					try
					{
						contPtr2->RemoveAndDelete(nextChar);
						cout<<"It was just removed and deleted."<<endl;
					}
					catch(string& str)
					{
						cerr<<str<<endl;
					}
				}
				break;
			case 16:
				cout<<"Please choose i(nt) or c(har) :";
				cin>>type;
				if(type == 'i')
				{
					contPtr1->RemoveAndDeleteAll();
				}
				if(type == 'c')
				{
					contPtr2->RemoveAndDeleteAll();
				}
				break;	
			default:
				cont = 0;
				break;
		}
	}
	
		cout<<"=====Thank you for using our Containers test !=====\n";
		
		delete contPtr1;
		delete contPtr2;
	
	return 0;
}















