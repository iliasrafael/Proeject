#include <iostream>
#include <cstdlib>
#include "Components.h"

using namespace std;

Component::Component(uint32_t id, uint32_t size_)
{
	component_id = id;
	nodes_count = 0;
	node_ids = (uint32_t*)malloc(sizeof(uint32_t)*size_);
	assert(node_ids!=NULL);
	size = size_;
}

Component::~Component()
{
	free(node_ids);
}
void Component::Deset()
{
	free(node_ids);
}
void Component::SetComponent(uint32_t id)
{
	component_id = id;
	nodes_count = 0;
	node_ids = (uint32_t*)malloc(sizeof(uint32_t)*SIZE);
	assert(node_ids!=NULL);
	size = SIZE;
}

void Component::Insert(uint32_t id)
{
	if(nodes_count>=size)
		doubleSize();
	node_ids[nodes_count]=id;
	nodes_count++;
}

void Component::doubleSize()
{
	size=size*2;
	node_ids = (uint32_t*)realloc(node_ids, sizeof(uint32_t)*size);
	assert(node_ids!=NULL);
}

uint32_t Component::getNodesCount()
{
	return nodes_count;
}

uint32_t Component::getNode(uint32_t id)
{
	return node_ids[id];
}

uint32_t Component::getId()
{
	return component_id;
}

/////////////////////////////////////////////////////////////////////////

