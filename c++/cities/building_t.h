#ifndef __BUILDING_T__
#define __BUILDING_T__



template<class T>
class Building_t
{
	public:
	
				Building_t();

				Building_t(const Building_t<T>& _b);
	
	Building_t<T>& operator=(const Building_t<T>& _b);
	
	const T&	GetBuildingID()	const ;
	
	void 		SetBuildingID(const T& _id);

	private:
	
	T m_ID;

};


template<class T>
	Building_t<T>::Building_t() {}

template<class T>	
	Building_t<T>::Building_t(const Building_t<T>& _b) : m_ID(_b.m_ID) {}

template<class T>
	Building_t<T>& Building_t<T>::operator=(const Building_t<T>& _b)
	{
		if(&_b != this)
		{
			m_ID = _b.m_ID;
		}
		
		return *this;
	}

template<class T>
	const T& Building_t<T>::GetBuildingID() const
	{
		return m_ID;
	}

template<class T>
	void Building_t<T>::SetBuildingID(const T& _id)
	{
		m_ID = _id;
	}






















#endif //__BUILDING_T__

