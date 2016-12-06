#include "GrailIndex.h"

GrailIndex::GrailIndex::GrailIndex(uint32_t size)
{
	id = (uint32_t *)malloc(sizeof(uint32_t)*size);
	assert(id!=NULL);
	rank = (uint32_t *)malloc(sizeof(uint32_t)*size);
	assert(rank!=NULL);
	min_rank = (uint32_t *)malloc(sizeof(uint32_t)*size);
	assert(min_rank!=NULL);

	for(int i=0; i<size; i++)
	{
		id[i]=0;
		rank[i]=0;
		min_rank[i]=0;
	}
}

GrailIndex::buildGrailIndex(SCC* scc)
{
	// to be continued ...
}

int GrailIndex::isReachableGrailIndex(uint32_t source, uint32_t target)
{
	if(min_rank[target] <= min_rank[source] && rank[target] <= rank[source]) //??
		return 1;	//Maybe baby
	return 0;
}

void GrailIndex::setid(uint32_t id, uint32_t i)
{
	id[i] = id;
}

uint32_t GrailIndex::getid(uint32_t i)
{
 return id[i];
}

void GrailIndex::setrank(uint32_t r, uint32_t i)
{
	rank[i] = r;
}

uint32_t GrailIndex::getrank(uint32_t i)
{
	return rank[i];
}

void GrailIndex::setminrank(uint32_t r, uint32_t i)
{
	min_rank[i] = r;
}

uint32_t GrailIndex::getminrank(uint32_t i)
{
	return min_rank[i];
}

GrailIndex::~GrailIndex()
{
	free(id);
	free(rank);
	free(min_rank);
}