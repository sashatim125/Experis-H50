#ifndef __CITY_T__
#define __CITY_T__

#include <vector>

#include "street_t.h"

using namespace std;

template<class T1,class T2, class T3>
class City_t
{
	public:
	
				City_t();

				City_t(const City_t<T1, T2, T3>& _s);
	
	City_t<T1, T2, T3>& operator=(const City_t<T1, T2, T3>& _s);
	
	const T1&	GetCityID() const;
	
	void 		SetCityID(const T1& _id);
	
	void 		AddStreet(const Street_t<T2, T3>& _s);
	
	const Street_t<T2, T3>& GetStreet(const T2& _sID) const;
	
	
	
	

	private:
	
	T1 m_ID;
	
	vector<Street_t<T2,T3> > m_streets;

};


template<class T1,class T2, class T3>
	City_t<T1, T2, T3>::City_t() {}
	
template<class T1,class T2, class T3>
	City_t<T1, T2, T3>::City_t(const City_t<T1, T2, T3>& _c) :
		m_ID(_c.m_ID),m_streets(_c.m_streets)  {}

template<class T1,class T2, class T3>
	City_t<T1, T2, T3>& City_t<T1, T2, T3>::operator=(const City_t<T1, T2, T3>& _c)
	{
		if(&_c != this)
		m_ID = _c.m_ID;
		m_streets = _c.m_streets;
		
		return *this;
	}

template<class T1,class T2, class T3>
	const T1& City_t<T1, T2, T3>::GetCityID() const
	{
		return m_ID;
	}

template<class T1,class T2, class T3>
	void City_t<T1, T2, T3>::SetCityID(const T1& _id)
	{
		m_ID = _id;
	}
	
template<class T1,class T2, class T3>
	void City_t<T1, T2, T3>::AddStreet(const Street_t<T2,T3>& _s)
	{
		m_streets.push_back(_s);
	}
	
template<class T1,class T2, class T3>
	const Street_t<T2,T3>& City_t<T1, T2, T3>::GetStreet(const T2& _sID) const
	{
		size_t i;
		size_t size = m_streets.size();
		
		for(i=0 ; i< size ; ++i)
		{
			if (_sID == m_streets[i].GetStreetID())
			{
				break;
			}
		}
		
		if(i == size)
		{
			throw "No such street";
		}
		
		return m_streets[i];
	}




















#endif //__CITY_T__

