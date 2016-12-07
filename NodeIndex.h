#ifndef __NODEINDEX__ 
#define __NODEINDEX__

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
	uint32_t size;
	int* nodes;
	uint32_t* last_bucket;
	uint32_t* count;
public:	
	NodeIndex();
	~NodeIndex();
	bool InsertNode(uint32_t id,uint32_t offset);
	void reallocation();
	uint32_t getListHead(uint32_t id);
	int* getNodes();
	int getPosition(uint32_t );
	uint32_t getLastBucket(uint32_t );
	uint32_t getSize();
	uint32_t getCount(uint32_t);
	void setSize(uint32_t);
	void setCount(uint32_t);
	void setLastBucket(uint32_t ,uint32_t);
	bool destroyNodeIndex();
};

#endif