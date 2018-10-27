
#include <iostream>
#include <cstdio>

#include "string_t.h"

using namespace std;


int main()
{
	int choise;
	int cont;
	unsigned int capacity, index , start, len;
	String_t s1, s2;
	char c;
	long occ;
	bool caseSensFlag;
	
	cont = 1;
	
	cout<<"=====Welcome to the String_t test !=====\n";
	
	while(cont)
	{
		cout<<"\n\nPlease choose one of the options :\n";
		cout<<"0 : exit;\n";	
		cout<<"1 : enter the String 1 (no space characters please);\n";
		cout<<"2 : enter the String 2 (no space characters please);\n";
		cout<<"3 : convert String 1 to low case ;\n";
		cout<<"4 : convert String 1 to upper case ;\n";
		cout<<"5 : prepend String1 to String 2 ;\n";
		cout<<"6 : make String1+=String2 ;\n";	
		cout<<"7 : compare String 1 with String 2;\n";
		cout<<"8 : check if String1 contains String2;\n";
		cout<<"9 : get i-th character of Sting1;\n";
		cout<<"10: set i-th character of String1 ;\n";
		cout<<"11: print String1;\n";
		cout<<"12: print String2;\n";
		cout<<"13: get first occurence of a character in String1;\n";
		cout<<"14: get last occurence of a character in String1;\n";
		cout<<"15: get Length of String1;\n";
		cout<<"16: get capacity of String1;\n";
		cout<<"17: set initial capacity;\n";
		cout<<"18: get initial capacity;\n";
		cout<<"19: set case sensivity flag;\n";
		cout<<"20: get case sensivity flag;\n";
		cout<<"21: print the substring of String1\n";		
	
		cin>>choise;
	
		switch (choise)
		{
			case 1:
				cin>>s1;
				break;
			case 2:
				cin>>s2;
				break;
			case 3:
				s1.ToLowerCase();
				break;
			case 4:
				s1.ToUpperCase();
				break;
			case 5:
				s2.Prepend(s1);
				break;
			case 6:
				s1 += s2;
				break;
			case 7:
				if(s1 < s2)
					cout<<"S1 < S2\n";
				if(s1 <= s2)
					cout<<"S1 <= S2\n";
				if(s1 == s2)
					cout<<"S1 == S2\n";
				if(s1 != s2)
					cout<<"S1 != S2\n";
				if(s1 > s2)
					cout<<"S1 > S2\n";
				if(s1 >= s2)
					cout<<"S1 >= S2\n";
				break;
			case 8:
				printf("S1 does %s contain S2\n",s1.Contains(s2) ? "" : "not");
				break;
			case 9:
				cout<<"enter the index :";
				cin>>index;
				cout<< "S1[index] is "<<s1[index]<<"\n";
				break;
			case 10:
				cout<<"enter the index :";
				cin>>index;
				
				if(0 <= s1[index])
				{				
					cout<<"enter the character :";
					cin>>c;
					s1[index]=c;
				}else
				{
					cout<<"Wrong index !\n";
				}
				break;
			case 11:
				cout<<"S1 is : "<<s1<<"\n";
				break;
			case 12:
				cout<<"S2 is : "<<s2<<"\n";
				break;
			case 13:
				cout<<"enter the character :";
				cin>>c;
				occ = s1.GetFirstOccurrence(c);
				if(0<= occ)
				{
					cout<<"First occurrence of "<<c<<" in "<<s1<<" is "<<occ<<"\n";
				}else
				{
					cout<<"No such character in S1\n";
				}
				break;
			case 14:
				cout<<"enter the character :";
				cin>>c;
				occ = s1.GetLastOccurrence(c);
				if(0<= occ)
				{
					cout<<"Last occurrence of "<<c<<" in "<<s1<<" is "<<occ<<endl;
				}else
				{
					cout<<"No such character in S1\n";
				}
				break;
			case 15:
				cout<<"The length of S1 is "<<s1.GetLength()<<endl;
				break;
			case 16:
				cout<<"The capacity of S1 is "<<s1.GetCapacity()<<endl;
				break;	
			case 17:
				cout<<"enter the capacity :";
				cin>>capacity;
				cout<<"The previous initial capacity was "<<String_t::SetInitCapacity(capacity)<<endl;
				break;				
			case 18:
				cout<<"The initial capacity is "<<String_t::GetInitCapacity()<<endl;
				break;
			case 19:
				cout<<"enter the flag value (1=true or 0=false) :";
				cin>>caseSensFlag;
				cout<<"The previous flag value was ";
				cout<<((String_t::SetCaseSensitive(caseSensFlag)) ? "true" : "false") <<endl;
				break;
			case 20:
				cout<<"The case sensivity flag value is ";
				cout<<((String_t::GetCaseSensitive()) ? "true" : "false") <<endl;
				break;
			case 21:
				cout<<"enter the start and the length of the substring :";
				cin>>start>>len;
				cout<<"The substring is : "<< s1(start,len) <<endl;
				break;
				
			default:
				cont = 0;
				break;
		}
	}
	
		cout<<"=====Thank you for using our String_t test !=====\n";
	
	return 0;
}










