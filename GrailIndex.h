#ifndef __GRAILINDEX__ 
#define __GRAILINDEX__

#include <stdint.h>
#include "SCC.h"
#include "Graph.h"

class Graph;
class GrailIndex
{	
	uint32_t* rank;
	uint32_t* min_rank;
public:
	GrailIndex(uint32_t size_);
	~GrailIndex();
	void buildGrailIndex(Graph* graph, uint32_t size);
	uint32_t find_min(uint32_t node_id, Graph* graph);
	int isReachableGrailIndex(uint32_t source, uint32_t target);
	void setrank(uint32_t r, uint32_t i);
	uint32_t getrank(uint32_t i);
	void setminrank(uint32_t r, uint32_t i);
	uint32_t getminrank(uint32_t i);
};

#endif