#include <iostream>
#include "JobScheduler.h"

int main(int argc, char const *argv[])
{
	Job job(1,2,0);
	JobScheduler js(5);
	js.submit_job(job);

	return 0;
}
