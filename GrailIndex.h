#ifndef __GRAILINDEX__ 
#define __GRAILINDEX__

#include <stdint.h>
#include "SCC.h"
#include "Graph.h"
#define GRAIL_NUMBER 2
class Graph;
class GrailIndex
{	
	uint32_t* rank[GRAIL_NUMBER];
	uint32_t* min_rank[GRAIL_NUMBER];
public:
	GrailIndex(uint32_t size_);
	~GrailIndex();
	void buildGrailIndex(Graph* graph, uint32_t size,int flag);
	uint32_t find_min(uint32_t node_id, Graph* graph,int flag);
	int isReachableGrailIndex(uint32_t source, uint32_t target,SCC* scc);
	void setrank(uint32_t r, uint32_t i,int flag);
	uint32_t getrank(uint32_t i,int flag);
	void setminrank(uint32_t r, uint32_t i,int flag);
	uint32_t getminrank(uint32_t i,int flag);
};

class GrailInfo
{
	bool visited;
	int from;
	uint32_t count;
	int next_off;

public:
	GrailInfo();
	bool getVisited();
	void setVisited(bool visited);
	int getFrom();
	void setFrom(int from);
	uint32_t getCount();
	void raiseCount();
	void setNext_off(int off);
	int getNext_off();
};

#endif
