#include <iostream>
#include <cstdlib>
#include "Components.h"
#define SIZE 20

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
SCC::~SCC()
{
	free(components);
	free(id_belongs_to_component);
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
	size=SIZE;
}
void SCC::doubleSize()
{
	size=size*2;
	components = (Component*)realloc(components, sizeof(Component)*size);
	assert(components!=NULL);

}
void SCC::Insert(uint32_t id , uint32_t element)
{
	if(id>size)
		doubleSize();
	else
	{
		if(components_count<id)
			components_count=id;
		components[id].Insert(element);
		id_belongs_to_component[element]=id;
	}

}
InfoTable::InfoTable()
{
	index=0;
	low_link=0;
	on_stack=false;
	defined=false;
	count=0;
}
bool InfoTable::IsDefined()
{
	return defined;
}
void InfoTable::stacked()
{
	on_stack=true;
}
void InfoTable::do_defined()
{
	defined=true;
}
void InfoTable::setIndex(uint32_t index_)
{
	index=index_;
}
void InfoTable::setLowLink(uint32_t low_link_)
{
	low_link=low_link_;
}
void InfoTable::setCount()
{
	count=0;
}
void InfoTable::setFrom(int from_)
{
	from=from_;
}
uint32_t InfoTable::getCount()
{
	return count;
}
void InfoTable::AddCount()
{
	count++;
}
bool InfoTable::IsStacked()
{
	return on_stack;
}
void InfoTable::UnStacked()
{
	on_stack=false;
}
uint32_t InfoTable::getLowLink()
{
	return low_link;
}
uint32_t InfoTable::getIndex()
{
	return index;
}
int InfoTable::getFrom()
{
	return from;
}