#include <iostream>
#include <cstdlib>
#include "Components.h"

using namespace std;

Components::Component(uint32_t id, uint32_t size_)
{
	Component_id = id;
	nodes_count = 0;
	node_ids = (uint32_t*)malloc(sizeof(uint32_t)*size_);
	size = size_;
}

Components::~Component()
{
	free(node_ids);
}



void Stack::doubleSize()
{
	size=size*2;
	node_ids = (uint32_t*)realloc(node_ids, sizeof(uint32_t)*size);
	assert(node_ids!=NULL);
}