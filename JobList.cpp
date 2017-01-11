#include "JobList.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
using namespace std;
#define ALSIZE 20
JobList::JobList()
{
	array=(Job *)malloc(sizeof(Job)*ALSIZE);
	if(array==NULL)
		cout<<ALSIZE<<endl;
	head=0;
	back=0;
	elements=0;
	size=ALSIZE;
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
	//memcpy((Job)array[back], (Job)job, sizeof(Job));
	array[back]=job;
	cout<<"Insert: "<<array[back].source<<endl;
	back++;
	elements++;
}

Job* JobList::remove()
{
	Job* job;
	memcpy((Job *)&array[head], (Job *)&job, sizeof(Job));
	//job=array[head];
	cout<<"Remove: "<<job->source<<endl;
	head++;
	elements--;
	return job;
}
bool JobList::empty()
{
	return head==back;
}
uint32_t JobList::get_size()
{
	return back-head;
}

void JobList::DoubleSize()
{
	if(size > 50000)
	{
		size=(uint32_t)size*3/2;
		array=(Job*)realloc(array,sizeof(Job)*size);
		assert(array!=NULL);
		return;
	}

	size=size*2;
	array=(Job*)realloc(array,sizeof(Job)*size);
	assert(array!=NULL);
}

void JobList::Set()
{
	head=0;
	back=0;
	elements=0;
}