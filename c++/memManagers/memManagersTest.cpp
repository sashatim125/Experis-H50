
#include <iostream>
#include <cstring>

#include "memPage_t.h"
#include "memPool_t.h"

using namespace std;


int main()
{
	int choise;
	int cont;
	
	MemManager_t *memMan = 0;
	
	int managerType;
	int readType;
	int posChoise;
	size_t capacity;
	size_t pos;
	size_t defPageSize;
	size_t numOfBytes;
	
	int i;
	int num;
	char str[1024];
	
	cont = 1;
	
	cout<<"=====Welcome to the Memory Managers test !=====\n";
	
	while(cont)
	{
		cout<<"\n\nPlease choose one of the options :\n";
		cout<<"0 : exit;\n";	
		cout<<"1 : create the Memory Manager (page or pool);\n";
		cout<<"2 : destroy the Memory Manager;\n";
		cout<<"  : common functionality :\n";
		cout<<"3 : get the current position;\n";
		cout<<"4 : set the current position;\n";
		cout<<"5 : check if the memory is empty;\n";	
		cout<<"6 : get actual size of the memory;\n";
		cout<<"7 : read from the memory;\n";
		cout<<"8 : write to the memory;\n";
		cout<<"  : page functionality :\n";
		cout<<"9 : check if the page is full;\n";
		cout<<"10: get the page's capacity;\n";
		cout<<"  : pool functionality :\n";
		cout<<"11: get default page size;\n";
		cout<<"12: set default page size;\n";	
	
		cin>>choise;
	
		switch (choise)
		{
			case 1:
				cout<<"Please type 1 for page or 2 for pool :";
				cin>>managerType;
				switch (managerType)
				{
					case 1:
						cout<<"Please enter the capacity (0 for default capacity):";
						cin>>capacity;						
						memMan = (0 < capacity) ? new MemPage_t(capacity) : new MemPage_t();
						break;
					case 2:
						memMan = new MemPool_t();
						break;
					default :
						cout<<"Wrong choise !"<<endl;
						continue;
				}
				break;
			case 2:
				delete memMan;
				break;
			case 3:
				cout<<"The current position is : "<<memMan->GetPos()<<endl;
				break;
			case 4:
				cout<<"Please enter the position :";
				cin>>pos;
				try
				{
					memMan->SetPos(pos);
				}
				catch(int)
				{
					cout<<"Wrong position !"<<endl;
					continue;
				}
				cout<<"The position has been set to "<<memMan->GetPos()<<"."<<endl;
				break;
			case 5:
				cout<<"The memory is "<<((memMan->IsMemEmpty()) ? "" : "not ")<<"empty."<<endl;
				break;
			case 6:
				cout<<"The actual size of the memory is : "<<memMan->GetActualSize()<<"."<<endl;
				break;
			case 7:
				cout<<"You can read an integer number (of size "<<sizeof(int)<<" bytes) or ";
				cout<<"string of characters(with terminating 0)."<<endl;
				cout<<"Enter 1 for current position or 2 for choosing the position :";
				cin>>posChoise;
				switch (posChoise)
				{
					case 1:
						break;
					case 2:
						cout<<"Please enter the position:";
						cin>>pos;
						break;
					default :
						cout<<"Wrong choise !"<<endl;
						continue;
				}				
				cout<<"Please enter your choise (1 for number or 2 for string) :";
				cin>>readType;
				switch (readType)
				{
					case 1:
						cout<<"The number of bytes read is : ";
						numOfBytes = ((posChoise == 1) ? memMan->Read(&num, sizeof(num)) :
							memMan->Read(&num, sizeof(num), pos));
						cout<<numOfBytes<<"."<<endl;
						if(numOfBytes > 0)
						{
							cout<<"And the value of the number is "<<num<<"."<<endl;
						}
						break;
					case 2:
						if(posChoise == 2) 
						{
							try
							{
							memMan->SetPos(pos);
							}catch(int)
							{
								cout<<"Wrong position !"<<endl;
								continue;
							}
						}
						for(i=0, numOfBytes=0;
							0 < (numOfBytes += memMan->Read(str+i,1)) && '\0' != str[i] ; ++i)
						{}
						str[i] = '\0';
						cout<<"The number of bytes read is : "<<numOfBytes<<"."<<endl;
						cout<<"The string is : "<<str<<"."<<endl;
						break;
					default :
						cout<<"Wrong choise !"<<endl;
						continue;
				}
				break;
			case 8:
				cout<<"You can write an integer number (of size "<<sizeof(int)<<" bytes) or ";
				cout<<"string of characters(with terminating 0)."<<endl;
				cout<<"Enter 1 for current position or 2 for choosing the position :";
				cin>>posChoise;
				switch (posChoise)
				{
					case 1:
						break;
					case 2:
						cout<<"Please enter the position:";
						cin>>pos;
						break;
					default :
						cout<<"Wrong choise !"<<endl;
						continue;
				}				
				cout<<"Please enter your choise (1 for number or 2 for string) :";
				cin>>readType;
				switch (readType)
				{
					case 1:
						cout<<"Please enter your number : ";
						cin>>num;
						cout<<"The number of bytes written is :";
						cout<<((posChoise == 1) ? memMan->Write(&num, sizeof(num)) :
							memMan->Write(&num, sizeof(num), pos)) << "."<<endl;
						num=0;
						break;
					case 2:
						if(posChoise == 2) 
						{
							try
							{
								memMan->SetPos(pos);
							}catch(int)
							{
								cout<<"Wrong position !"<<endl;
								continue;
							}
						}
						cout<<"Please enter your string :";
						cin>>str;
						cout<<"The number of bytes written is :";
						cout<<memMan->Write(str, strlen(str)+1) << "."<<endl;
						break;
					default :
						cout<<"Wrong choise !"<<endl;
						continue;
				}
				break;
			case 9:
				cout<<"The page is "<<(((MemPage_t*)memMan)->IsMemFull() ? "" : "not ");
				cout<<"full."<<endl;
				break;
			case 10:
				cout<<"The page's capacity is : "<<((MemPage_t*)memMan)->GetCapacity()<<"."<<endl;
				break;
			case 11:
				cout<<"The default page size is : "<<((MemPool_t*)memMan)->GetDefaultPageSize()<<"."<<endl;
				break;
			case 12:
				cout<<"Please enter the new default page size :";
				cin>>defPageSize;
				((MemPool_t*)memMan)->SetDefaultPageSize(defPageSize);
				cout<<"The new default page size is : "<<((MemPool_t*)memMan)->GetDefaultPageSize()<<"."<<endl;
				break;		
			default:
				cont = 0;
				break;
		}
	}
	
		cout<<"=====Thank you for using our Memory Managers test !=====\n";
		
		delete memMan;
	
	return 0;
}










