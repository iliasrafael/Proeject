#include <iostream>
#include <cstdlib>
#include <stdint.h>
#define NodeIndexSize 5
using namespace std;
///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
class NodeIndex {
	unsigned int size;
	unsigned int* nodes;
	unsigned int* last_bucket;
public:	
	NodeIndex();
	~NodeIndex();
	bool InsertNode(uint32_t id,uint32_t offset);
	void reallocation();
	unsigned int getListHead(uint32_t id);
	unsigned int* getNodes();
	unsigned int getPosition(unsigned int );
	unsigned int getLastBucket(unsigned int );
	unsigned int getSize();
	void setSize(unsigned int);
	void setLastBucket(unsigned int ,unsigned int);
	bool destroyNodeIndex();
};