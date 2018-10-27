
#ifndef __CAR_T_H__
#define __CAR_T_H__

#include <string>

using namespace std;

class Car_t
{
	public:
	//constructors	
	
					Car_t (unsigned int _capacity);
	
					Car_t (const Car_t& _car);
	
	//mem-functions
	
	//compare by name
	bool 			Compare(const Car_t& _car) const;

	unsigned long	GetID() const;

	const string&	GetName() const;
	
	const string&	GetGearType() const;
	
	unsigned int	GetCapacity() const;
	
	//operators
	
	Car_t& 			operator=(const Car_t& _car);
	
	//compare by capacity
	bool 			operator<(const Car_t& _car) const;

	
	protected:
	
	~Car_t();
	
	void SetName(const string& _name);
		
	void SetGearType(const string& _gt);
	
	static unsigned long AquireId();


	private:
		
	//running number for IDs
	static unsigned long m_sNextID;
		
	unsigned int m_capacity;
		
	string m_name;
		
	string m_gearType;
		
	const unsigned long m_ID;

};




#endif //__CAR_T_H__


