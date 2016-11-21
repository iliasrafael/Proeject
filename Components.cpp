#include <iostream>
#include <cstdlib>
#include "Components.h"

using namespace std;

Component::Component(uint32_t id, uint32_t size_)
{
	component_id = id;
	nodes_count = 0;
	node_ids = (uint32_t*)malloc(sizeof(uint32_t)*size_);
	size = size_;
}

Component::~Component()
{
	free(node_ids);
}

bool Component::Insert(uint32_t id)
{
	if(nodes_count==size)
		doubleSize();
	node_ids[nodes_count]=id;
	nodes_count++;
	return true;
}

void Component::doubleSize()
{
	size=size*2;
	node_ids = (uint32_t*)realloc(node_ids, sizeof(uint32_t)*size);
	assert(node_ids!=NULL);
}