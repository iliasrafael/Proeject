#ifndef __SCC__ 
#define __SCC__
#include "Components.h"


class ComponentCursor 
{
	uint32_t Cursor;
	Component* CurrentComponent;

public:
	uint32_t getCursor();
	Component* getCurrentComponent();
	void setCursor(uint32_t );
	void setCurrentComponent(Component *);

};

class SCC
{
	Component* components; // Components index - a vector which stores the components information
	uint32_t components_count;
	uint32_t* id_belongs_to_component; //inverted index 
	uint32_t size;
	ComponentCursor* cursor;

public:
	SCC(uint32_t size_);
	~SCC();
	void Insert(uint32_t id,uint32_t element);
	void doubleSize();
	uint32_t findSCCid(uint32_t nodeId);
	void Print();
	uint32_t getComponentCount();
	uint32_t findNodeStronglyConnectedComponentID(uint32_t nodeId);
	bool iterateStronglyConnectedComponentID(ComponentCursor* _cursor);
	bool next_StronglyConnectedComponentID(ComponentCursor* _cursor);

};



class InfoTable
{
	uint32_t index;
	uint32_t low_link;
	bool on_stack;
	uint32_t count;
	int from;
	public:
	InfoTable();
	void stacked();
	void setIndex(uint32_t index);
	void setLowLink(uint32_t low_link_);
	void setCount();
	void AddCount();
	void setFrom(int from_);
	uint32_t getCount();
	bool IsStacked();
	void UnStacked();
	uint32_t getLowLink();
	uint32_t getIndex();
	int getFrom();
};

#endif