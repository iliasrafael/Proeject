#ifndef __COMPONENTS__ 
#define __COMPONENTS__

#include <stdint.h>
#include <assert.h>

#define SIZE 2

class Component
{
	uint32_t component_id;
	uint32_t nodes_count;
	uint32_t size;
	uint32_t* node_ids;
public:
	Component(uint32_t id , uint32_t size);
	~Component();
	void SetComponent(uint32_t id);
	void Insert(uint32_t id);
	void doubleSize();
	uint32_t getNodesCount();
	uint32_t getNode(uint32_t id);
	uint32_t getId();
};

#endif