#include "list_node.h"
#define BufferSize 10
///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
class Buffer{
	unsigned int last;
	unsigned int size;
public:
	list_node *cells;
	Buffer();
	~Buffer();
	unsigned int allocNewNode();
	int InsertFirstNode(uint32_t id);
	list_node* getListNode(unsigned int);
	unsigned int getLast();
	void setLast(unsigned int);
	unsigned int getSize();
	void setSize(unsigned int);
	void reallocation();
	bool destroyBuffer();
};