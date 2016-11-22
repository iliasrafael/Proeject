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
	Component(uint32_t id , uint32_t size);
	~Component();
	void SetComponent();
	bool Insert(uint32_t id);
	void doubleSize();
};

class SCC
{
	Component* components; // Components index - a vector which stores the components information
	uint32_t components_count;
	uint32_t* id_belongs_to_component; //inverted index 

public:
	SCC(uint32_t size_);
	~SCC();
};
#endif