

#include <iostream>

#include "binIO_t.h"
#include "asciiIO_t.h"


using namespace std;

int main()
{
	int choise;
	int cont;
	
	AsciiIO_t aIO;
	BinIO_t bIO;
	
	string type;
	
	
	cont = 1;
	
	cout<<"=====Welcome to the Virtual IO test !=====\n";
	
	while(cont)
	{
		cout<<"\n\nPlease choose one of the options :\n";
		cout<<"0 : exit;\n";	
		cout<<"1 : Set Name and Mode;\n";
		cout<<"2 : Get Name and Mode;\n";
		cout<<"3 : get status ;\n";
		cout<<"4 : get length;\n";
		cout<<"5 : open file;\n";	
		cout<<"6 : close file;\n";
		cout<<"7 : write to file;\n";
		cout<<"8 : read from file;\n";
		cout<<endl;
	
		cin>>choise;
	
		switch (choise)
		{
			case 1:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{			
					string str1,str2;
					cout<<"Enter name and mode :";
					cin>>str1>>str2;
					try {aIO.SetNameAndMode(str1,str2);}
					catch(exception& e) {cerr<<e.what();}
				}
				if(type == "b")
				{			
					string str1,str2;
					cout<<"Enter name and mode :";
					cin>>str1>>str2;
					try {bIO.SetNameAndMode(str1,str2);}
					catch(exception& e) {cerr<<e.what();}
				}
				break;
			case 2:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{			
					pair<string,string> strp(aIO.GetNameAndMode());
					cout<<"Name is "<<strp.first<<" mode is "<<strp.second<<endl;
				}
				if(type == "b")
				{			
					pair<string,string> strp(bIO.GetNameAndMode());
					cout<<"Name is "<<strp.first<<" mode is "<<strp.second<<endl;
				}
				break;
			case 3:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{			
					cout<<"the status is "<<aIO.GetStatus()<<endl;
				}
				if(type == "b")
				{			
					cout<<"the status is "<<bIO.GetStatus()<<endl;
				}
				break;
			case 4:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{			
					try {cout<<"The length is "<<aIO.GetLength();}
					catch(exception& e) {cerr<<e.what();}
				}
				if(type == "b")
				{			
					try {cout<<"The length is "<<bIO.GetLength();}
					catch(exception& e) {cerr<<e.what();}
				}
				break;
			case 5:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{			
					try {aIO.OpenFile();}
					catch(exception& e) {cerr<<e.what();}
				}
				if(type == "b")
				{			
					try {bIO.OpenFile();}
					catch(exception& e) {cerr<<e.what();}
				}
				break;
			case 6:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{			
					try {aIO.CloseFile();}
					catch(exception& e) {cerr<<e.what();}
				}
				if(type == "b")
				{			
					try {bIO.CloseFile();}
					catch(exception& e) {cerr<<e.what();}
				}
				break;
			case 7:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{
					cout<<"enter the build-in data type"<<endl;
					cout<<"c(har)|uc(har)|s(hort)|us(hort)|i(nt)|ui(nt)";
					cout<<"l(ong)|ul(ong)|f(loat)|d(ouble) :"<<endl;
					string dtype;
					cin>>dtype;
					if(dtype=="c")
					{
						char i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="uc")
					{
						unsigned char i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="s")
					{
						short i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="us")
					{
						unsigned short i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="l")
					{
						long i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ul")
					{
						unsigned long i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="f")
					{
						float i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="d")
					{
						double i;
						cout<<"Enter the data :";
						cin>>i;
						try {aIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
				}
				if(type == "b")
				{
					cout<<"enter the build-in data type"<<endl;
					cout<<"c(har)|uc(har)|s(hort)|us(hort)|i(nt)|ui(nt)";
					cout<<"l(ong)|ul(ong)|f(loat)|d(ouble) :"<<endl;
					string dtype;
					cin>>dtype;
					if(dtype=="c")
					{
						char i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="uc")
					{
						unsigned char i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="s")
					{
						short i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="us")
					{
						unsigned short i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="l")
					{
						long i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ul")
					{
						unsigned long i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="f")
					{
						float i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="d")
					{
						double i;
						cout<<"Enter the data :";
						cin>>i;
						try {bIO<<i;}
						catch(exception& e) {cerr<<e.what();}
					}
				}
				break;
				
				case 8:
				cout<<"Choose type of file : a(scii) or b(inary):";
				cin>>type;
				if(type == "a")
				{
					cout<<"enter the build-in data type"<<endl;
					cout<<"c(har)|uc(har)|s(hort)|us(hort)|i(nt)|ui(nt)";
					cout<<"l(ong)|ul(ong)|f(loat)|d(ouble) :"<<endl;
					string dtype;
					cin>>dtype;
					if(dtype=="c")
					{
						char i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="uc")
					{
						unsigned char i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="s")
					{
						short i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="us")
					{
						unsigned short i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="l")
					{
						long i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ul")
					{
						unsigned long i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="f")
					{
						float i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="d")
					{
						double i;
						try {aIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
				}
				if(type == "b")
				{
					cout<<"enter the build-in data type"<<endl;
					cout<<"c(har)|uc(har)|s(hort)|us(hort)|i(nt)|ui(nt)";
					cout<<"l(ong)|ul(ong)|f(loat)|d(ouble) :"<<endl;
					string dtype;
					cin>>dtype;
					if(dtype=="c")
					{
						char i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="uc")
					{
						unsigned char i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="s")
					{
						short i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="us")
					{
						unsigned short i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="i")
					{
						int i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ui")
					{
						unsigned int i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="l")
					{
						long i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="ul")
					{
						unsigned long i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="f")
					{
						float i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
					if(dtype=="d")
					{
						double i;
						try {bIO>>i;cout<<"The value is "<<i<<endl;}
						catch(exception& e) {cerr<<e.what();}
					}
				}
				break;
				
			default:
				cont = 0;
				break;
		}
	}
	
		cout<<"=====Thank you for using our Virtual IO test !=====\n";
	
	return 0;
}












