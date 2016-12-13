#ifndef __CC__ 
#define __CC__
#include <stdint.h>
#include <assert.h>
#include "Graph.h"
#include "ArrayList.h"

class CC{

	int* ccindex; //CCIndex
	int* updateIndex;
	uint32_t metricVal;
	uint32_t size_cc;
	uint32_t size_update;
	uint32_t counter;
public:
	CC(uint32_t size_);
	~CC();
	void Insert(uint32_t nodeId,uint32_t componentId);
	int UpdateIndex(uint32_t componentId1,uint32_t componentId2);
	void CCSearch(Graph* graph);
	void CC_update(Graph* graph,uint32_t id,bool* visited,ArrayList* out_oura);
	bool check(uint32_t id,uint32_t id2);
	void rebuild();
	void UpdatedoubleSize();
	void CCDoubleSize();
	void InsertNewEdge(uint32_t id,uint32_t id2, uint32_t &count);
};



#endif

