#include <iostream>
#include "JobScheduler.h"

int main(int argc, char const *argv[])
{
	Job job(1,2,0);
	JobScheduler js(5);
	JobList gl;
	gl.Insert(job);
	return 0;
}
