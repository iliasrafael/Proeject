#include "JobList.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
#define JOBSIZE 256
//////////////////////////////////////////////////////////////
Jobs::Jobs()
{
	for(int i=0;i<JOBS_NUMBER;i++)
	{
		valid_job[i]=false;
	}
	jobs_counter=0;
}

Job Jobs::getJob(int i)
{
	valid_job[i]=false;
	return jobs[i];
}

bool Jobs::isValid(int i)
{
	return valid_job[i];
}

void Jobs::initializeJobs()
{
	for(int i=0;i<JOBS_NUMBER;i++)
	{
		valid_job[i]=false;
	}
	jobs_counter=0;
}

void Jobs::setJob(int i,Job job)
{
	jobs[i].setJob(job);
	valid_job[i]=true;
	jobs_counter++;
}

void Jobs::setJobs()
{
	for(int i=0;i<JOBS_NUMBER;i++)
	{
		valid_job[i]=false;
	}
}

void Jobs::copyJobs(Jobs jobs_)
{
	for(int i=0;i<JOBS_NUMBER;i++)
	{
		jobs[i].setJob(jobs_.getJob(i));
		valid_job[i]=jobs_.isValid(i);
	} 
}

int Jobs::getJobsCounter()
{
	return jobs_counter;
}
void Jobs::setJobsCounterZero()
{
	jobs_counter=0;
}
void Jobs::incJobsCounter()
{
	jobs_counter++;
}
void Jobs::decJobsCounter()
{
	jobs_counter--;
}
void Jobs::setInValid(int i)
{
	valid_job[i]=false;
}
////////////////////////////////////////////////////////////
JobList::JobList()
{
	array=(Jobs*)malloc(sizeof(Jobs)*JOBSIZE);
	assert(array!=NULL);
	for(int i=0;i<JOBSIZE;i++)
	{
		array[i].initializeJobs();
	}
	head=0;
	elements=0;
	size=JOBSIZE;
	back=0;
}

JobList::~JobList()
{
	free(array);
}
void JobList::Insert(Job job)
{
	if(back==size)
	{
		DoubleSize();
	}

	int pos = elements % JOBS_NUMBER;
	array[back].setJob(pos,job);
	elements++;
	if (pos == JOBS_NUMBER-1)
		back++;
}

Jobs* JobList::pop()
{
	if(empty())
	{
		cerr<<"Queue is empty!"<<endl;
		exit(0);
	}
	return &array[head];
}

void JobList::remove()
{
	//cerr<<"elements = "<<elements<<" head= "<<head<<" back = "<<back<<endl;
	elements-=JOBS_NUMBER;
	head++;
}

bool JobList::empty()
{
	//cerr<<"elements = "<<elements<<" head= "<<head<<" back = "<<back<<endl;
	return (head>=back && elements<=0);
}

void JobList::DoubleSize()
{
	size=size*2;
	cerr<< "ROPALO2"<< size << endl;
	array=(Jobs*)realloc(array,sizeof(Jobs)*size);
	assert(array!=NULL);
	for(int i=size/2;i<size;i++)
	{
		array[i].initializeJobs();
	}
	
}

void JobList::Set()
{
	for(int i=0;i<JOBSIZE;i++)
	{
		array[i].initializeJobs();
	}
	head=0;
	back=0;
	elements=0;
}