#ifndef __BUFFER__ 
#define __BUFFER__

#include "list_node.h"
#define BufferSize 20
///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
class Buffer{
	uint32_t last;
	uint32_t size;
	list_node *cells;
public:
	Buffer();
	~Buffer();
	uint32_t allocNewNode();
	int InsertFirstNode(uint32_t id, int vers);
	list_node* getListNode(uint32_t);
	uint32_t getLast();
	void setLast(uint32_t);
	uint32_t getSize();
	void setSize(uint32_t);
	void reallocation();
	bool destroyBuffer();
};

#endif