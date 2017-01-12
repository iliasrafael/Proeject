#ifndef __Job__	
#define __Job__

#include <stdint.h>
#include "Graph.h"

class Job
{
	
public:
	uint32_t source;
	uint32_t target;
	bool kind;
	bool isstatic;
	int order;

	Graph* graph;
	SCC* scc;
	GrailIndex* grailindex;
	
	Job(Graph* graph_, SCC* scc_, GrailIndex* grailindex_, uint32_t source_ , uint32_t target_,bool k, int ord, bool st);
	int run();
};

#endif