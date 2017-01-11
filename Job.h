#ifndef __Job__	
#define __Job__

#include <stdint.h>

class Job
{
	
public:
	uint32_t source;
	uint32_t target;
	bool kind;
	
	Job(uint32_t source_ , uint32_t target_,bool k);
	void run();
};

#endif