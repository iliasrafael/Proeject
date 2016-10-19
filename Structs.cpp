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
unsigned int list_node::getNext()
{
	return offset;
}


///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
Buffer::Buffer()                                         //
{                                                       //
	cells=(list_node *)malloc(sizeof(list_node)*BufferSize);       	           //
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