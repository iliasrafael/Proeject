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
		cells[i].setLastNeighbor(0);
	}
	last=0;                                           
	size=BufferSize;                                                
}                                                  
////////////////////////////////////////////////////
Buffer::~Buffer()
{
	free(cells);
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
	last_bucket=(uint32_t *)malloc(sizeof(uint32_t)*NodeIndexSize);
	for(int i=0;i<NodeIndexSize;i++){
		nodes[i]=-1;
		last_bucket[i]=0;
	}
	size=NodeIndexSize;
}
void NodeIndex::reallocation()
{
	size*=2;
	nodes = (unsigned int*) realloc(nodes, sizeof(unsigned int)*size);
	last_bucket= (unsigned int*) realloc(last_bucket, sizeof(unsigned int)*size);
	for(int i =size/2; i<size; i++)
	{
		nodes[i]=-1;
		last_bucket[i]=0;
	}
}
////////////////////////////////////////////////////
NodeIndex::~NodeIndex()
{
	free(nodes);
	free(last_bucket);
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
////////////////////////////////////////////////////
unsigned int NodeIndex::getSize()
{
	return size;
}
////////////////////////////////////////////////////

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
	while(id>=index->getSize()) {
		index->reallocation();
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
			if(index->last_bucket[id]!=0)
				res=buffer->cells[index->last_bucket[id]].Insert(id2);
		if(res==false)
		{
			if(last>=buffer->getSize()) {
				buffer->reallocation();
			}

			if(buffer->cells[position].offset==0)
				buffer->cells[position].offset=last;
			index->last_bucket[id]=last;
			buffer->cells[last].Insert(id2);
			buffer->setLast(last+1);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
