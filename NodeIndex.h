#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <assert.h>

#define NodeIndexSize 10
using namespace std;
///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
class NodeIndex {
	unsigned int size;
	unsigned int* nodes;
	unsigned int* last_bucket;
	unsigned int* count;
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
	unsigned int getCount(unsigned int);
	void setSize(unsigned int);
	void setCount(unsigned int);
	void setLastBucket(unsigned int ,unsigned int);
	bool destroyNodeIndex();
};