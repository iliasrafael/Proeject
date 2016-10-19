/* domes */
#include <stdint.h>
#define N 100

bool OK_SUCCESS;

class list_node {
	uint32_t neighbor[N];
	uint32_t edgeProperty[N];
	unsigned int offset;	
};

class Buffer{
	list_node *cells;
public:
	Buffer();
	unsigned int allocNewNode();
	list_node* getListNode(unsigned int);
	bool destroyBuffer();
};

class NodeIndex {
	unsigned int* Nodes;
public:
	NodeIndex();
	bool InsertNode(uint32_t id);
	unsigned int getListHead(uint32_t id);
	bool destroyNodeIndex();
};

class Graph{
	NodeIndex * inc_index;
	NodeIndex * out_index;
	Buffer * inc_buffer;
	Buffer * out_buffer;
};
