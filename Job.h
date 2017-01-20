#ifndef __Job__	
#define __Job__

#include <stdint.h>
#include "Graph.h"
#include "CC.h"

class Job
{
	
public:
	uint32_t source;
	uint32_t target;
	bool kind;
	bool isstatic;
	int order;
	int version;

	Graph* graph;
	SCC* scc;
	GrailIndex* grailindex;
	CC* cc;
	
	Job(Graph* graph_, SCC* scc_, GrailIndex* grailindex_, CC* cc_, uint32_t source_ , uint32_t target_,bool k, int ord, bool st, int vers);
	Job(const Job& job);
	Job();
	int getOrder();
	void setJob(Job job);
	int run();
};

#endif