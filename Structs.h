/* domes */
#include <stdint.h>
#define N 100

bool OK_SUCCESS;

class list_node {
	uint32_t neighbor[N];
	uint32_t edgeProperty[N];
	int offset;	
};

class NodeIndex {
	list_node* list_head;

	NodeIndex* createNodeIndex();
	int InsertNode(NodeIndex* index, int id);
	list_node* getListHead(NodeIndex* index, int id);
	int destroyNodeIndex(NodeIndex* index);
};

class Buffer{
	list_node *cells;


	Buffer* createBuffer();
	int allocNewNode(Buffer*);
	list_node* getListNode(int);
	OK_SUCCESS destroyBuffer(Buffer*);
};

class Graph{
	NodeIndex * inc_index;
	NodeIndex * out_index;
	Buffer * inc_buffer;
	Buffer * out_buffer;
};
/*
Graph::Graph()
{
	
}
*/