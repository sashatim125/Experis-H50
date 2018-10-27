
#include "departmentReporter.h"



void Department::Report() const
{
	if(0!=m_reporter)
	{
		m_reporter->Report();
	}
}


