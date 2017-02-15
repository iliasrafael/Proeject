#include "SCC.h"
#include <iostream>
#include <cstdlib>

using namespace std;

SCC::SCC(uint32_t size_)
{
	components = (Component*) malloc(sizeof(Component)*SIZE);
	assert(components!=NULL);
	for(int i=0;i<SIZE;i++)
		components[i].SetComponent(i);	
	components_count=0;
	id_belongs_to_component = (uint32_t*) malloc(sizeof(uint32_t)*size_);
	assert(id_belongs_to_component!=NULL);
	for(int i=0;i<size_;i++)
		id_belongs_to_component[i]=0;
	size=SIZE;
}

SCC::~SCC()
{	
	for(int i=0;i<size;i++)
		components[i].Deset();
	free(components);
	free(id_belongs_to_component);
}

void SCC::doubleSize()
{
	size=size*2;
	components = (Component*)realloc(components, sizeof(Component)*size);
	for(uint32_t i=size/2 ; i< size ; i ++)
		components[i].SetComponent(i);
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

uint32_t SCC::findSCCid(uint32_t nodeId)
{
	return id_belongs_to_component[nodeId];
}

void SCC::Print()
{

	int count=0;
	for(int i = 0; i <= components_count; i++)
	{
		for(int j = 0; j < components[i].getNodesCount(); j++)
		{

			cout<<components[i].getNode(j)<<" ";
		}
		cout<<endl;

		if(components[i].getNodesCount()>1) {
			count++;
			cout<<"ID "<<i<<": "<<components[i].getNodesCount()<<endl;
		}
	}

}

uint32_t SCC::getComponentCount()
{
	return components_count;
}
Component *SCC::getComponent(int id)
{
	return &components[id];
}
uint32_t SCC::findNodeStronglyConnectedComponentID(uint32_t nodeId)
{
	return id_belongs_to_component[nodeId];
}

bool SCC::iterateStronglyConnectedComponentID(ComponentCursor* cursor)
{
	cursor = (ComponentCursor*) malloc(sizeof(ComponentCursor));
	cursor->setCursor(0);
	cursor->setCurrentComponent(&components[0]);
}

bool SCC::next_StronglyConnectedComponentID(ComponentCursor* cursor)
{
	cursor->setCursor(cursor->getCursor()+1);
	cursor->setCurrentComponent(&components[cursor->getCursor()]);
}
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
uint32_t ComponentCursor::getCursor()
{
	return Cursor;
}
Component* ComponentCursor::getCurrentComponent()
{
	return CurrentComponent;
}
void ComponentCursor::setCursor(uint32_t i)
{
	Cursor = i;
}
void ComponentCursor::setCurrentComponent(Component * component)
{
	CurrentComponent = component;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

InfoTable::InfoTable()
{
	index=0;
	low_link=0;
	on_stack=false;
	count=0;
	from=-1;
	next_off=-1;
}

void InfoTable::stacked()
{
	on_stack=true;
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
int InfoTable::getNext_off()
{
	return next_off;
}
void InfoTable::setNext_off(int off)
{
	next_off = off;
}