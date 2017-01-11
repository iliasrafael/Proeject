#ifndef __JobList__	
#define __JobList__

#include <stdint.h>
#include <assert.h>
#include "Job.h"

class JobList{

	Job *array;
	uint32_t head;
	uint32_t back;
	uint32_t elements;
	uint32_t size;
public:

JobList();
~JobList();
void Insert(Job job);
bool empty();
Job* remove();
uint32_t get_size();
void DoubleSize();
void Set();
};

#endif