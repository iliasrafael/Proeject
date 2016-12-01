#include "Buffer.h"
///////////////////////////////////////////////////////////////////////////////
/* BUFFER */
///////////////////////////////////////////////////////////////////////////////
Buffer::Buffer()                                         
{                                                       
	cells=(list_node *)malloc(sizeof(list_node)*BufferSize);
	assert(cells!=NULL);       	           
	for(int i=0;i<BufferSize;i++)
	{
		cells[i].setOffset(-1);
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
list_node* Buffer::getListNode(uint32_t offset)
{
	if(offset > size)
	{
		cerr << "Offset at buffer > Size "<<endl;
		return NULL;
	}

	return &cells[offset];		
}
////////////////////////////////////////////////////
uint32_t Buffer::getLast()
{
	return last;
}
void Buffer::setLast(uint32_t last_)
{
	last=last_;
}
////////////////////////////////////////////////////
uint32_t Buffer::getSize()
{
	return size;
}
////////////////////////////////////////////////////
void Buffer::setSize(uint32_t size_)
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
	assert(cells!=NULL);    	           
	for(int i=(size/2); i<size; i++)
	{
		cells[i].setOffset(-1);
		cells[i].setLastNeighbor(0);
	}
}
////////////////////////////////////////////////////