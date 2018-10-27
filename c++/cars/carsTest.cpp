
#include <iostream>
#include <cstdio>

#include "bus_t.h"
#include "private_t.h"

using namespace std;


int main()
{
	int choise;
	int cont;
	
	Bus_t *bus = 0;
	Private_t *priv = 0;
	Car_t *car;
	
	unsigned int capacity;
	int carType;
	unsigned int numOfSeats;
	unsigned int lineNum;
	
	cont = 1;
	
	cout<<"=====Welcome to the Cars test !=====\n";
	
	while(cont)
	{
		cout<<"\n\nPlease choose one of the options :\n";
		cout<<"0 : exit;\n";	
		cout<<"1 : create the Bus;\n";
		cout<<"2 : create the Private car;\n";
		cout<<"3 : get the name of the Bus ;\n";
		cout<<"4 : get the name of the Private car;\n";
		cout<<"5 : get the gear type of the car;\n";	
		cout<<"6 : compare (by operator <) the Bus and the Private car;\n";
		cout<<"7 : check if the Bus and the car are of the same type;\n";
		cout<<"8 : get the Bus's ID;\n";
		cout<<"9 : get the Private car's ID;\n";
		cout<<"10: get the number of seats in the bus;\n";
		cout<<"11: set the number of seats in the bus;\n";
		cout<<"12: get the line number in the Bus;\n";
		cout<<"13: set the line number in the Bus;\n";
		cout<<"14: get the speed of the Private car;\n";
		cout<<"15: accelerate the private car;\n";
		cout<<"16: reduce the speed of the Private car;\n";	
	
		cin>>choise;
	
		switch (choise)
		{
			case 1:
				cout<<"Please enter the capacity :";
				cin>>capacity;
				bus = new Bus_t(capacity);
				break;
			case 2:
				cout<<"Please enter the capacity :";
				cin>>capacity;
				priv = new Private_t(capacity);
				break;
			case 3:
				cout<<"The name of the Bus is : "<<bus->GetName()<<endl;
				break;
			case 4:
				cout<<"The name of the Private Car is : "<<priv->GetName()<<endl;
				break;
			case 5:
				cout<<"What car ? 1=Bus, 2= Private car :";
				cin>>carType;
				cout<<"The gear type of "<<((carType==1) ? "Bus" : "Private car")<<" is ";
				if(carType==1)
				{
					car = bus;
				}
				if(carType==2)
				{
					car = priv;
				}
				cout<<car->GetGearType()<<endl;
				break;
			case 6:
				cout<<"The result of Bus < Private car is "<<((*bus<*priv)?"true":"false")<<endl;
				break;
			case 7:
				cout<<"The Bus and the Private car are";
				cout<<((bus->Compare(*priv))?" ":" not ")<<"of the same type."<<endl;
				break;
			case 8:
				cout<<"The Bus's ID is "<<bus->GetID()<<endl;
				break;
			case 9:
				cout<<"The Private car's ID is "<<priv->GetID()<<endl;
				break;
			case 10:
				cout<<"The number of seats in the bus is "<<bus->GetNumOfSeats()<<endl;
				break;
			case 11:
				cout<<"Please enter the number of seats :";
				cin>>numOfSeats;
				bus->SetNumOfSeats(numOfSeats);
				break;
			case 12:
				cout<<"The line number of the bus is "<<bus->GetLineNum()<<endl;
				break;
			case 13:
				cout<<"Please enter the line number :";
				cin>>lineNum;
				bus->SetLineNum(lineNum);
			case 14:
				cout<<"The speed of the Private car is "<<priv->GetSpeed();
				break;
			case 15:
				priv->Accelerate();
				break;
			case 16:
				priv->ReduceSpeed();
				break;				
				
			default:
				cont = 0;
				break;
		}
	}
	
		cout<<"=====Thank you for using our Cars test !=====\n";
		
		delete bus;
		delete priv;
	
	return 0;
}










