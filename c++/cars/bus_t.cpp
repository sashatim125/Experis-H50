
#include "bus_t.h"

//static initialization
 	const unsigned int Bus_t::s_defaultNumOfSeats = 40;
	
	const unsigned int Bus_t::s_defaultLineNum = 0;
	
	const char* Bus_t::s_busName = "Bus";
	
	const char* Bus_t::s_GearType = "manual";


//public:
	
	Bus_t::~Bus_t()
	{}
	
	Bus_t::Bus_t(unsigned int _capacity) : Car_t(_capacity),
			m_numOfSeats(s_defaultNumOfSeats), 
			m_lineNum(s_defaultLineNum)
	{
		SetName(s_busName);
		SetGearType(s_GearType);
	}
	
	Bus_t::Bus_t(const Bus_t& _bus) : Car_t(_bus),
			m_numOfSeats(_bus.m_numOfSeats),
			m_lineNum(_bus.m_lineNum)
	{}
	
	Bus_t& Bus_t::operator=(const Bus_t& _bus)
	{
		if(this!=&_bus)
		{
			Car_t::operator=(_bus);
		
			m_numOfSeats = _bus.m_numOfSeats;
		
			m_lineNum  =_bus.m_lineNum;
		}
		
		return *this;
	}
	
	void Bus_t::SetNumOfSeats(unsigned int _numOfSeats)
	{
		m_numOfSeats = _numOfSeats;
	}
	
	unsigned int Bus_t::GetNumOfSeats() const
	{
		return m_numOfSeats;
	}
	
	void Bus_t::SetLineNum(unsigned int _lineNum)
	{
		m_lineNum = _lineNum;
	}
	
	unsigned int Bus_t::GetLineNum() const
	{
		return m_lineNum;
	}




















