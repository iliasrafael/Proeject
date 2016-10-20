/* Structs.h */
#include <stdint.h>
#define N 100
#define BufferSize 90
#define NodeIndexSize 100
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define OK_SUCCESS 1
///////////////////////////////////////////////////////////////////////////////
/* LIST NODE*/
///////////////////////////////////////////////////////////////////////////////
class list_node {                          
public:
	uint32_t neighbor[N];                 
	uint32_t edgeProperty[N];            
	unsigned int offset;
	unsigned int last_neighbor;
	unsigned int last_offset;
	bool Insert(uint32_t id);
	uint32_t* getNeighbors();
	uint32_t* getProperties();
	unsigned int getOffset();
	unsigned int getLastOffset();
	unsigned int getLastNeighbor();	 
	void setOffset(unsigned int off);
	void setLastOffset(unsigned int off);           
};								       
///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
class Buffer{
public:
	list_node *cells;
	unsigned int last;
	unsigned int size;
	Buffer();
	~Buffer();
	unsigned int allocNewNode();
	int InsertFirstNode(uint32_t id);
	list_node* getListNode(unsigned int);
	unsigned int getLast();
	unsigned int getSize();
	bool destroyBuffer();
};
///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
class NodeIndex {
	unsigned int* nodes;
	unsigned int last;
	unsigned int size;
public:
	NodeIndex();
	~NodeIndex();
	bool InsertNode(uint32_t id,uint32_t offset);
	unsigned int getListHead(uint32_t id);
	unsigned int* getNodes();
	unsigned int getPosition(unsigned int );
	unsigned int getLast();
	unsigned int getSize();
	void setLast(unsigned int);
	void setSize(unsigned int);
	bool destroyNodeIndex();
};
///////////////////////////////////////////////////////////////////////////////
/* GRAPH */
///////////////////////////////////////////////////////////////////////////////
class Graph{
	NodeIndex inc_index;
	NodeIndex out_index;
	Buffer inc_buffer;
	Buffer out_buffer;
public:
	bool Insert(uint32_t id,uint32_t id2);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
