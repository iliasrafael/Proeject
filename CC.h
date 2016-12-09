#ifndef __CC__ 
#define __CC__
#include <stdint.h>
#include <assert.h>
#include "Graph.h"
#include "ArrayList.h"

class CC{

	uint32_t* ccindex; //CCIndex
	Graph updateIndex;
	uint32_t metricVal;
public:
	CC(uint32_t size_);
	~CC();
	void Insert(uint32_t nodeId,uint32_t componentId);
	void Update(uint32_t componentId1,uint32_t componentId2);
	void CCSearch(Graph* graph);
	void CC_update(Graph* graph,uint32_t id,bool* visited,ArrayList* out_oura);
};



#endif

