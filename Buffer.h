#include "list_node.h"
#define BufferSize 20
///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
class Buffer{
	unsigned int last;
	unsigned int size;
	list_node *cells;
public:
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