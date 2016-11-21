#ifndef __COMPONENTS__ 
#define __COMPONENTS__

#include <stdint.h>
#include <assert.h>

class Component
{
	uint32_t component_id;
	uint32_t nodes_count;
	uint32_t size;
	uint32_t* node_ids;
public:
	Component(uint32_t size);
	~Component();
	

	void Stack::doubleSize();
};

#endif