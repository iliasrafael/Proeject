#include "Buffer.h"
#include "NodeIndex.h"
#include "list.h"
///////////////////////////////////////////////////////////////////////////////
/* GRAPH */
///////////////////////////////////////////////////////////////////////////////
class Graph{
	NodeIndex inc_index;
	Buffer inc_buffer;
	NodeIndex out_index;
	Buffer out_buffer;
public:
	bool Insert(NodeIndex *index ,Buffer *buffer,uint32_t id,uint32_t id2);
	int BBFS(uint32_t start , uint32_t target);
	NodeIndex* getOutIndex();
	NodeIndex* getIncIndex();
	Buffer* getOutBuffer();
	Buffer* getIncBuffer();
	bool Update(NodeIndex &index,Buffer &buffer,int &count,List &oura,int* visited,int situation);
	bool search(uint32_t id,uint32_t id2);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
