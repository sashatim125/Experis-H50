#include "bignumber.h"
#include <iostream>

using namespace std;

int main()
{
	int choise;
	int cont;
	
	BigNumber n1, n2;
	
	int val;
	string str;
	string entType;
	
	cont = 1;
	
	cout<<"=====Welcome to the BigNumbers test !=====\n";
	
	while(cont)
	{
		cout<<"\n\nPlease choose one of the options :\n";
		cout<<"0 : exit;\n";	
		cout<<"1 : enter the first number;\n";
		cout<<"2 : enter the second number;\n";
		cout<<"3 : compare the numbers ;\n";
		cout<<"4 : compute n1 + n2 (if both are positive);\n";
		cout<<"5 : compute n1 - n2 (if both are positive);\n";	
		cout<<"6 : print n1;\n";
		cout<<"7 : print n2;\n";
		cout<<endl;
	
		cin>>choise;
	
		switch (choise)
		{
			case 1:
				cout<<"Enter as i(nt) or s(tring) :";
				cin>>entType;
				if(entType == "i")
				{
					cin>>val;
					n1 = val;
				}
				if(entType == "s")
				{
					cin>>str;
					n1 = str.c_str();
				}
				break;
			case 2:
				cout<<"Enter as i(nt) or s(tring) :";
				cin>>entType;
				if(entType == "i")
				{
					cin>>val;
					n2 = val;
				}
				if(entType == "s")
				{
					cin>>str;
					n2 = str.c_str();
				}
				break;
			case 3:
				if(n1 == n2)
				{
					cout << "n1 == n2" <<endl;
				}
				if(n1 > n2)
				{
					cout << "n1 > n2" <<endl;
				}
				if(n1 < n2)
				{
					cout << "n1 < n2" <<endl;
				}
				break;
			case 4:
				cout<<"n1 + n2 = "<< n1+n2 <<endl;
				break;
			case 5:
				cout<<"n1 - n2 = "<< n1-n2 <<endl;
				break;
			case 6:
				cout<<"n1 = "<< n1 <<endl;
				break;
			case 7:
				cout<<"n2 = "<< n2 <<endl;
				break;
				
			default:
				cont = 0;
				break;
		}
	}
	
		cout<<"=====Thank you for using our BigNumbers test !=====\n";
	
	return 0;
}











