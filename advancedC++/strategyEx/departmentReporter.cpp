
#include "departmentReporter.h"
#include <iostream>
#include <set>
#include <map>

void DepartmentReporterFull::Report()
{
	std::cout<<std::endl<<"Full report."<<std::endl<<std::endl;
	std::cout<<"Name : "<< GetDepAccess().GetName()<<" , ";
	std::cout<<"Description : "<< GetDepAccess().GetDescription()<<std::endl;

	std::vector<Worker>::const_iterator it = GetDepAccess().GetWorkers().begin();
	std::vector<Worker>::const_iterator end = GetDepAccess().GetWorkers().end();
		
	for (; it != end ; ++it)
	{
		WorkerAccessor wa(*it);
		std::pair<std::string, std::string> name = wa.GetName();
		std::cout<<"Name : "<< name.first<<" "<<name.second<<" , ";
		std::cout<<"Job : "<<Jobs::FindJob(it->GetJobId())<<" , ";
		std::cout<<"Salary : "<<it->GetSalary()<<std::endl;
	}
		
	std::cout<<"End of report."<<std::endl<<std::endl;
}

void DepartmentReporterShort::Report()
{
	std::cout<<std::endl<<"Short report."<<std::endl<<std::endl;
	std::cout<<"Name : "<< GetDepAccess().GetName() <<std::endl;
	
	std::map<JobId_t, std::pair<unsigned,double> > stat;
	std::vector<Worker>::const_iterator it = GetDepAccess().GetWorkers().begin();
	std::vector<Worker>::const_iterator end = GetDepAccess().GetWorkers().end();
		
	for (; it != end ; ++it)
	{
		JobId_t nextJobId = it->GetJobId();
		if(stat.find(nextJobId) == stat.end())
		{
			stat[nextJobId] = std::pair<unsigned,double>(1,it->GetSalary());
		}else
		{
			++(stat[nextJobId].first);
			stat[nextJobId].second += it->GetSalary();
		}
	}
		
	std::map<JobId_t, std::pair<unsigned,double> >::const_iterator jidIt = stat.begin();
	std::map<JobId_t, std::pair<unsigned,double> >::const_iterator jidEnd = stat.end();
	for (; jidIt != jidEnd ; ++jidIt)
	{
		std::cout<<"Job : "<< Jobs::FindJob(jidIt->first) << ", ";
		std::cout<<"Number of employees : "<< jidIt->second.first << ", ";
		std::cout<<"Average salary : "<< (jidIt->second.second / jidIt->second.first);
		std::cout<<std::endl;
	}
	
	std::cout<<"End of report."<<std::endl<<std::endl;	
}


void DepartmentReporterSummary::Report()
{
	std::cout<<std::endl<<"Summary report."<<std::endl<<std::endl;
	std::cout<<"Name : "<< GetDepAccess().GetName() <<std::endl;
	std::cout<<"Number of employees : "<< GetDepAccess().GetWorkers().size() <<std::endl;
	
	std::set<JobId_t> jobIds;
	std::vector<Worker>::const_iterator it = GetDepAccess().GetWorkers().begin();
	std::vector<Worker>::const_iterator end = GetDepAccess().GetWorkers().end();
	
	double totSalary = 0;
	
	for (; it != end ; ++it)
	{
		totSalary += it->GetSalary();
		jobIds.insert(it->GetJobId());
	}
	
	std::cout<<"Number of jobs : "<< jobIds.size() <<std::endl;
	
	std::cout<<"Average salary : "<< (totSalary/(double)GetDepAccess().GetWorkers().size()) <<std::endl;
	
	std::cout<<"End of report."<<std::endl<<std::endl;
}













