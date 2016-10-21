#include "Structs.h"
#include <iostream>
#include <cstdlib>
using namespace std;
///////////////////////////////////////////////////////////////////////////////
/* LIST NODE*/
///////////////////////////////////////////////////////////////////////////////
uint32_t* list_node::getNeighbors()
{
	return neighbor;
}
////////////////////////////////////////////////////
uint32_t* list_node::getProperties()
{
	return edgeProperty;
}
////////////////////////////////////////////////////
unsigned int list_node::getOffset()
{
	return offset;
}
////////////////////////////////////////////////////
unsigned int list_node::getLastOffset()
{
	return last_offset;
}
////////////////////////////////////////////////////
unsigned int list_node::getLastNeighbor()
{
	return last_neighbor;
}
////////////////////////////////////////////////////
void list_node::setOffset(unsigned int off)
{
	offset=off;
}
////////////////////////////////////////////////////
void list_node::setLastOffset(unsigned int off){
	last_offset=off;
}
////////////////////////////////////////////////////
void list_node::setLastNeighbor(unsigned int neighbor){
	last_neighbor=neighbor;
}
////////////////////////////////////////////////////
bool list_node::Insert(uint32_t id)
{
	if(last_neighbor<N)
		neighbor[last_neighbor++]=id;
	else
		return false;
	return true;
}
////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
Buffer::Buffer()                                         
{                                                       
	cells=(list_node *)malloc(sizeof(list_node)*BufferSize);       	           
	for(int i=0;i<BufferSize;i++)
	{
		cells[i].setOffset(0);
		cells[i].setLastOffset(0);
		cells[i].setLastNeighbor(0);
	}
	last=0;                                           
	size=BufferSize;                                 
	cout <<"Buffer Created"<<endl;                  
}                                                  
////////////////////////////////////////////////////
Buffer::~Buffer()
{
	free(cells);
	cout <<"Buffer Deleted"<<endl;
}
////////////////////////////////////////////////////
list_node* Buffer::getListNode(unsigned int offset)
{
	if(offset > size)
	{
		cerr << "Offset > Size "<<endl;
		return NULL;
	}

	return &cells[offset];		
}
////////////////////////////////////////////////////
unsigned int Buffer::getLast()
{
	return last;
}
void Buffer::setLast(unsigned int last_)
{
	last=last_;
}
////////////////////////////////////////////////////
unsigned int Buffer::getSize()
{
	return size;
}
////////////////////////////////////////////////////
void Buffer::setSize(unsigned int size_)
{
	size=size_;
}
////////////////////////////////////////////////////
int Buffer::InsertFirstNode(uint32_t id)
{
	cells[last++].Insert(id);
	return last-1;
}
////////////////////////////////////////////////////
void Buffer::reallocation()
{
	size*=2;
	cells=(list_node *)realloc(cells, sizeof(list_node)*size);       	           
	for(int i=(size/2); i<size; i++)
	{
		cells[i].setOffset(0);
		cells[i].setLastOffset(0);
		cells[i].setLastNeighbor(0);
	}
}
////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
NodeIndex::NodeIndex()
{
	nodes=(unsigned int*)malloc(sizeof(unsigned int)*NodeIndexSize);
	for(int i=0;i<NodeIndexSize;i++)
		nodes[i]=-1;
	last=0;
	size=NodeIndexSize;
	cout <<"Index Created"<<endl;    
}
////////////////////////////////////////////////////
NodeIndex::~NodeIndex()
{
	free(nodes);
	cout <<"Index Deleted"<<endl;
}
////////////////////////////////////////////////////
unsigned int* NodeIndex::getNodes()
{
	return nodes;
}
unsigned int NodeIndex::getPosition(unsigned int i)
{
	return nodes[i];
}
////////////////////////////////////////////////////
unsigned int NodeIndex::getLast()
{
	return last;
}
////////////////////////////////////////////////////
unsigned int NodeIndex::getSize()
{
	return size;
}
////////////////////////////////////////////////////
void NodeIndex::setLast(unsigned int last_)
{
	last=last_;
}
////////////////////////////////////////////////////
void NodeIndex::setSize(unsigned int size_)
{
	size=size_;
}
////////////////////////////////////////////////////
bool NodeIndex::InsertNode(uint32_t id,uint32_t offset)
{
	nodes[id]=offset;
}
////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/* GRAPH */
///////////////////////////////////////////////////////////////////////////////

bool Graph::Insert(NodeIndex *ind,Buffer *buff, uint32_t id,uint32_t id2)
{	

	NodeIndex * index=ind;
	Buffer *buffer=buff;
	while(id>=index->getSize()) 
	{
		//cout<<"Index -> realloc for "<<id<<endl;
		index->setSize(2*index->getSize());
		index->nodes = (unsigned int*) realloc(index->nodes, sizeof(unsigned int)*index->getSize());
		for(int i = (index->getSize()/2); i<index->getSize(); i++)
			index->nodes[i]=-1;
	}

	unsigned int last=buffer->getLast(); //fovamai
	if(index->getPosition(id)==-1)
	{
		if(last>=buffer->getSize()) {
			buffer->reallocation();
			//cout<<"Buffer-> realloc for "<<id<<endl;
		}
		int offset=buffer->InsertFirstNode(id2);
		index->InsertNode(id,offset);
	}
	else
	{
		int position = index->getPosition(id);
		bool res=buffer->cells[position].Insert(id2);

		if(res==false)
			if(buffer->cells[position].last_offset!=0)
				res=buffer->cells[buffer->cells[position].last_offset].Insert(id2);
		if(res==false)
		{
			if(last>=buffer->getSize()) {
				buffer->reallocation();
			}

			if(buffer->cells[position].offset==0)
				buffer->cells[position].offset=last;
			buffer->cells[position].last_offset=last;
			buffer->cells[last].Insert(id2);
			buffer->setLast(last+1);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
