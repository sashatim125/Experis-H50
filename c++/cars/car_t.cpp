

#include "car_t.h"


//static initialization
unsigned long Car_t::m_sNextID = 1;

//public:
	
	Car_t::Car_t (unsigned int _capacity) : m_capacity(_capacity) ,
			m_ID(AquireId()){}
	
	Car_t::Car_t (const Car_t& _car) : m_capacity(_car.m_capacity),
			m_name(_car.m_name), m_gearType(_car.m_gearType),
			m_ID(AquireId()){}
	
	Car_t& Car_t::operator=(const Car_t& _car)
	{
		if(this != &_car)
		{
			this->m_capacity	= _car.m_capacity;
		
//			this->m_name		= _car.m_name;
		
//			this->m_gearType	= _car.m_gearType;
		}
		return *this;
	}
	
	bool Car_t::operator<(const Car_t& _car) const
	{
		return m_capacity < _car.m_capacity;
	}
	
	bool Car_t::Compare(const Car_t& _car) const
	{
		return (m_name == _car.m_name);
	}

	unsigned long Car_t::GetID() const
	{
		return m_ID;
	}

	const string& Car_t::GetName() const
	{
		return m_name;
	}
	
	const string& Car_t::GetGearType() const
	{
		return m_gearType;
	}
	
	unsigned int Car_t::GetCapacity() const
	{
		return m_capacity;
	}

	
//protected:

	Car_t::~Car_t()
	{}
	
	void Car_t::SetName(const string& _name)
	{
		m_name = _name;
	}
		
	void Car_t::SetGearType(const string& _gt)
	{
		m_gearType = _gt;
	}
	
	unsigned long Car_t::AquireId()
	{
		return m_sNextID++ ;
	}


		





