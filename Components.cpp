#include <iostream>
#include <cstdlib>
#include "Components.h"
#define SIZE 2

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

SCC::SCC(uint32_t size_)
{
	components = (Component*) malloc(sizeof(Component)*SIZE);
	assert(components!=NULL);
	for(int i=0;i<SIZE;i++)
		components[i].SetComponent(i+1);
	components_count=0;
	id_belongs_to_component = (uint32_t*) malloc(sizeof(uint32_t)*size_);
	assert(id_belongs_to_component!=NULL);
	for(int i=0;i<size_;i++)
		id_belongs_to_component[i]=0;
	size=SIZE;
}

SCC::~SCC()
{
	free(components);
	free(id_belongs_to_component);
}

void SCC::doubleSize()
{
	size=size*2;
	components = (Component*)realloc(components, sizeof(Component)*size);
	for(uint32_t i=size/2 ; i< size ; i ++)
		components[i].SetComponent(i+1);
	assert(components!=NULL);

}

void SCC::Insert(uint32_t id , uint32_t element)
{
	if(id>=size)
		doubleSize();

	if(components_count<id)
		components_count=id;
	components[id].Insert(element);
	id_belongs_to_component[element]=id;

}

void SCC::Print()
{
	cout<<"------------ PRINT ---------------"<<endl;
	for(int i = 0; i < components_count; i++)
	{
		cout<<"ID "<<components[i].getId()<<":"<<endl;
		for(int j = 0; j < components[i].getNodesCount(); j++)
		{
			if(components[i].getNode(j) != 0)
				cout<<components[i].getNode(j)<<" ";
		}
		cout<<endl;
	}
	cout<<"--------------------------------------"<<endl;
}

uint32_t SCC::getComponentCount()
{
	return components_count;
}

/////////////////////////////////////////////////////////////////////////////

InfoTable::InfoTable()
{
	index=0;
	low_link=0;
	on_stack=false;
	//defined=false;
	count=0;
}
/*bool InfoTable::IsDefined()
{
	return defined;
}*/
void InfoTable::stacked()
{
	on_stack=true;
}
/*void InfoTable::do_defined()
{
	defined=true;
}*/
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