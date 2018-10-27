
#include <iostream>
#include <cstring>

#include "building_t.h"
#include "street_t.h"
#include "city_t.h"

using namespace std;


int main()
{
	int choise;
	int cont;
	
	Building_t<int> *b=0;
	Street_t<string, int> *s=0;
	City_t<string, string, int> *c=0;
	
	string str1;
	string str2;
	string str3;
	int num;
	int id;
	
	cont = 1;
	
	cout<<"=====Welcome to the Cities test !=====\n";
	
	while(cont)
	{
		cout<<"\n\nPlease choose one of the options :\n";
		cout<<"0 : exit;\n";	
		cout<<"1 : create a building;\n";
		cout<<"2 : create a street;\n";
		cout<<"3 : create a city;\n";
		cout<<"4 : get the building ID;\n";
		cout<<"5 : set the building ID\n";	
		cout<<"6 : get the street ID;\n";
		cout<<"7 : set the street ID;\n";
		cout<<"8 : get city ID;\n";
		cout<<"9 : set city ID :\n";
		cout<<"10: add the building to the street;\n";
		cout<<"11: add the street to the city;\n";
		cout<<"12: get building from the street :\n";
		cout<<"13: get street from the city;\n";
	
		cin>>choise;
	
		switch (choise)
		{
			case 1:
				b = new Building_t<int>();
				break;
			case 2:
				s = new Street_t<string,int>();
				break;
			case 3:
				c = new City_t<string, string, int>();
				break;
			case 4:
				cout<<"The ID is :"<<b->GetBuildingID();
				break;
			case 5:
				cout<<"Please enter ID(int) :";
				cin>>num;
				b->SetBuildingID(num);
				break;
			case 6:
				cout<<"The ID is :"<<s->GetStreetID();
				break;
			case 7:
				cout<<"Please enter ID(string) :";
				cin>>str1;
				s->SetStreetID(str1);
				break;
			case 8:
				cout<<"The ID is :"<<c->GetCityID();
				break;
			case 9:
				cout<<"Please enter ID(string) :";
				cin>>str2;
				c->SetCityID(str2);
				break;
			case 10:
				s->AddBuilding2Street(*b);
				break;
			case 11:
				c->AddStreet(*s);
				break;
			case 12:
				cout<<"Enter the bulding ID :";
				cin>>id;
				try
				{
					cout<<"Here is the id :"<<((s->GetBuilding(id)).GetBuildingID())<<endl;
				}
				catch(const char* _str)
				{
					cout<<_str<<endl;
				}
				break;
			case 13:
				cout<<"Enter the street ID :";
				cin>>str3;
				try
				{
					cout<<"Here is the id :"<<(c->GetStreet(str3)).GetStreetID()<<endl;
				}
				catch(const char* _str)
				{
					cout<<_str<<endl;
				}
				break;		
			default:
				cont = 0;
				break;
		}
	}
	
		cout<<"=====Thank you for using our Cities test !=====\n";
		
		delete b;
		delete s;
		delete c;
	
	return 0;
}










