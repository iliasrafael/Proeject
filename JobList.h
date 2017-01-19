#ifndef __JobList__	
#define __JobList__
#define JOBS_NUMBER 64
#include <stdint.h>
#include <assert.h>
#include "Job.h"

class Jobs
{
	int jobs_counter;
	bool valid_job[JOBS_NUMBER];
	Job jobs[JOBS_NUMBER];

public:
	Jobs();
	Job getJob(int i);
	void setJob(int i,Job job);
	void setJobs();
	void copyJobs(Jobs jobs_);
	bool isValid(int i);
	int getJobsCounter();
	void incJobsCounter();
	void decJobsCounter();
	void setJobsCounterZero();
	void initializeJobs();
	void setInValid(int i);

};

class JobList{

	Jobs *array;
	uint32_t head;
	uint32_t back;
	int elements;
	uint32_t size;
public:

JobList();
~JobList();
void Insert(Job job);
bool empty();
Jobs* pop();
void remove();
uint32_t get_size();
void DoubleSize();
void Set();
};

#endif