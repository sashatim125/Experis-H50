
#include "departmentReporter.h"







int main()
{
	DepartmentReporter* depRepPtr=0;
	
	Department dep("Main","Does nothing",depRepPtr);
	
	depRepPtr = new DepartmentReporterSummary(dep);
	
	dep.SetReporter(depRepPtr);

	Jobs::AddSetJob(1,"manager");
	Jobs::AddSetJob(2,"plain worker");
	
	dep.AddWorker(Worker("John","Doe",1,50000));
	dep.AddWorker(Worker("Joseph","Doe",2,1000));
	dep.AddWorker(Worker("Mary","Doe",2,1500));
	
	dep.Report();

	delete depRepPtr;
	depRepPtr = new DepartmentReporterShort(dep);
	dep.SetReporter(depRepPtr);
	
	dep.Report();

	delete depRepPtr;
	depRepPtr = new DepartmentReporterFull(dep);
	dep.SetReporter(depRepPtr);
	
	dep.Report();







	return 0;
}




