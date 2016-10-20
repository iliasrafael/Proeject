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
unsigned int list_node::getLastOffset()
{
	return last_offset;
}
unsigned int list_node::getLastNeighbor()
{
	return last_neighbor;
}
void list_node::setOffset(unsigned int off)
{
	offset=off;
}
void list_node::setLastOffset(unsigned int off){
	last_offset=off;
}

///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
Buffer::Buffer()                                         //
{                                                       //
	cells=(list_node *)malloc(sizeof(list_node)*BufferSize);       	           //
	for(int i=0;i<BufferSize;i++)
	{
		cells[i].setOffset(0);
		cells[i].setLastOffset(0);
	}
	last=0;                                           //
	size=BufferSize;                                 //
	cout <<"Buffer Created"<<endl;                  //
}                                                  //
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
////////////////////////////////////////////////////
unsigned int Buffer::getSize()
{
	return size;
}
///////////////////////////////////////////////////////////////////////////////
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
NodeIndex::~NodeIndex()
{
	free(nodes);
	cout <<"Index Deleted"<<endl;
}
unsigned int NodeIndex::getLast()
{
	return last;
}
////////////////////////////////////////////////////
unsigned int NodeIndex::getSize()
{
	return size;
}

bool NodeIndex::InsertNode(uint32_t id,uint32_t offset)
{
	nodes[id]=offset;
}

int Buffer::InsertFirstNode(uint32_t id)
{
	cells[last++].Insert(id);
	return last-1;
}

bool Graph::Insert(uint32_t id,uint32_t id2)
{	
	/*
	if(id>=size)
	{
		//realloc to index
	}*/
	if(out_index.nodes[id]==-1)
	{
		/*
		if(out_buffer.last>=BufferSize)
		{
			//realloc
		}*/
			int offset=out_buffer.InsertFirstNode(id2);
			out_index.InsertNode(id,offset);
	}
	else
	{
		int position = out_index.nodes[id];
		bool res=out_buffer.cells[position].Insert(id2);
		if(res==false)
		{
				//if(out_buffer.last>=BufferSize)
				//reallox
					if(out_buffer.cells[position].offset==0)
						out_buffer.cells[position].offset=out_buffer.last;
					out_buffer.cells[position].last_offset=out_buffer.last;
					out_buffer.cells[out_buffer.last].Insert(id2);
					out_buffer.last++;
			}
	}
}

bool list_node::Insert(uint32_t id)
{
	if(last_neighbor<N)
		neighbor[last_neighbor++]=id;
	else
		return false;
	return true;
}