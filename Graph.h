#include "Buffer.h"
#include "NodeIndex.h"
#include "ArrayList.h"
#include <stdint.h>
#include "Components.h"
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
	int BBFS(uint32_t start , uint32_t target);
	NodeIndex* getOutIndex();
	NodeIndex* getIncIndex();
	Buffer* getOutBuffer();
	Buffer* getIncBuffer();
	bool Update(NodeIndex &index,Buffer &buffer,int &count,ArrayList &oura,int situation,uint32_t ** visited);
	bool search(uint32_t id,uint32_t id2);
	void CCSearch();
	void CC_update(uint32_t id,bool* visited);
	void SCC_Search();
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
