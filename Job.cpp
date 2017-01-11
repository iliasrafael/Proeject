#include "Job.h"
#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

Job::Job(uint32_t source_ , uint32_t target_ ,bool k)
{
	source = source_;
	target = target_;
	kind = k;
}

void Job::run()
{
	cout<<"Runnig ..."<<endl;
}