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
	uint32_t size;

public:
	SCC(uint32_t size_);
	~SCC();
	void Insert(uint32_t id,uint32_t element);
	void doubleSize();
};

class InfoTable
{
	uint32_t index;
	uint32_t low_link;
	bool on_stack;
	bool defined;
	uint32_t count;
	int from;
	public:
	InfoTable();
	bool IsDefined();
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