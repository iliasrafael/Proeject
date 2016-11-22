#include <iostream>
#include <cstdlib>
#include "Components.h"
#define SIZE 1000

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

void Component::SetComponent()
{
	component_id = 0;
	nodes_count = 0;
	node_ids = (uint32_t*)malloc(sizeof(uint32_t)*SIZE);
	assert(node_ids!=NULL);
	size = SIZE;
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

SCC::SCC(uint32_t size_)
{
	components = (Component*) malloc(sizeof(Component)*SIZE);
	assert(components!=NULL);
	for(int i=0;i<SIZE;i++)
		components[i].SetComponent();
	components_count=0;
	id_belongs_to_component = (uint32_t*) malloc(sizeof(uint32_t)*size_);
	assert(id_belongs_to_component!=NULL);
	for(int i=0;i<size_;i++)
		id_belongs_to_component[i]=0;
}

SCC::~SCC()
{
	free(components);
	free(id_belongs_to_component);
}