/* Structs.h */
#include <stdint.h>
#define N 5
#define BufferSize 10
#define NodeIndexSize 5
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
	void setLastNeighbor(unsigned int neighbor);         
};								       
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
///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
class NodeIndex {
	
	unsigned int last;
	unsigned int size;
public:
	unsigned int* nodes;
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
	
	Buffer inc_buffer;
	
public:
	NodeIndex out_index;
	Buffer out_buffer;
	bool Insert(uint32_t id,uint32_t id2);
};

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
