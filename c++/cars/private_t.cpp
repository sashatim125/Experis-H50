

#include "private_t.h"

//static initialization
const char* Private_t::s_privateName = "private";

const char* Private_t::s_GearType = "automatic";

const unsigned int Private_t::s_initialSpeed = 0;

const unsigned int Private_t::s_speedStep = 10;


//public:
	
	Private_t::~Private_t()
	{}
	
	Private_t::Private_t(unsigned int _capacity): Car_t(_capacity),
			m_speed(s_initialSpeed)
	{
		SetName(s_privateName);
		SetGearType(s_GearType);
	}
	
	Private_t::Private_t(const Private_t& _priv): Car_t(_priv),
			m_speed(s_initialSpeed)						//the speed is NOt pereserved
	{}
	
	Private_t& Private_t::operator=(const Private_t& _priv)
	{
		if(this!=&_priv)
		{
			Car_t::operator=(_priv);
		
			m_speed = s_initialSpeed;					//the speed is NOt pereserved
		}
		
		return *this;
	}
	
	void Private_t::Accelerate()
	{
		m_speed+=s_speedStep;
	}
	
	void Private_t::ReduceSpeed()
	{
		m_speed -= (m_speed >= s_speedStep) ? s_speedStep : m_speed;
	}
	
	unsigned int Private_t::GetSpeed() const
	{
		return m_speed;
	}

	







