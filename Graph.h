#include "Buffer.h"
#include "NodeIndex.h"
#include "ArrayList.h"
#include <stdint.h>
#include "Components.h"
#include "SCC.h"
///////////////////////////////////////////////////////////////////////////////
/* GRAPH */
///////////////////////////////////////////////////////////////////////////////
class Graph{
	NodeIndex inc_index;
	Buffer inc_buffer;
	NodeIndex out_index;
	Buffer out_buffer;
	ArrayList inc_oura;
	ArrayList out_oura;
public:
	bool Insert(NodeIndex *index ,Buffer *buffer,uint32_t id,uint32_t id2);
	int BBFS(uint32_t start , uint32_t target,SCC *scc);
	NodeIndex* getOutIndex();
	NodeIndex* getIncIndex();
	Buffer* getOutBuffer();
	Buffer* getIncBuffer();
	bool Update(NodeIndex &index,Buffer &buffer,int &count,ArrayList &oura,int situation,uint32_t ** visited,SCC *scc,int scc_target);
	bool search(uint32_t id,uint32_t id2);
	void CCSearch();
	void CC_update(uint32_t id,bool* visited);
	SCC SCC_Search();
	int estimateShortestPathStronglyConnectedComponents(SCC *scc,uint32_t source_node, uint32_t target_node);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////