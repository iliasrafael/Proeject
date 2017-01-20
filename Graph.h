#ifndef __GRAPH__ 
#define __GRAPH__

#include "Buffer.h"
#include "NodeIndex.h"
#include "ArrayList.h"
#include <stdint.h>
#include "Components.h"
#include "SCC.h"
#include "GrailIndex.h"
///////////////////////////////////////////////////////////////////////////////
/* GRAPH */
///////////////////////////////////////////////////////////////////////////////
class GrailIndex;
class Graph{
	NodeIndex inc_index;
	Buffer inc_buffer;
	NodeIndex out_index;
	Buffer out_buffer;
	
public:
	bool Insert(NodeIndex *index ,Buffer *buffer,uint32_t id,uint32_t id2);
	int BBFS(uint32_t start , uint32_t target,SCC *scc,bool scc_flag,GrailIndex * grailindex);
	NodeIndex* getOutIndex();
	NodeIndex* getIncIndex();
	Buffer* getOutBuffer();
	Buffer* getIncBuffer();
	bool Update(NodeIndex &index,Buffer &buffer,int &count,ArrayList &oura,int situation,uint32_t ** visited,SCC *scc,bool scc_flag,int scc_target,GrailIndex *grailindex,int target);
	bool search(uint32_t id,uint32_t id2);
	SCC SCC_Search();
	int estimateShortestPathStronglyConnectedComponents(SCC *scc,uint32_t source_node, uint32_t target_node);
	void creation(SCC *scc,Graph *graph);
};

#endif
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////