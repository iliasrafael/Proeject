#include "NodeIndex.h"
///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
NodeIndex::NodeIndex()
{
	nodes=(unsigned int*)malloc(sizeof(unsigned int)*NodeIndexSize);
	last_bucket=(unsigned int *)malloc(sizeof(unsigned int)*NodeIndexSize);
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
////////////////////////////////////////////////////
unsigned int NodeIndex::getPosition(unsigned int i)
{
	//cout<<"i "<<i<<endl;
	//cout<<"nodes "<<nodes[i]<<endl;
	return nodes[i];
}
////////////////////////////////////////////////////
unsigned int NodeIndex::getLastBucket(unsigned int i)
{
	return last_bucket[i];
}
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
void NodeIndex::setLastBucket(unsigned int i,unsigned int last)
{
	last_bucket[i]=last;
}
////////////////////////////////////////////////////
bool NodeIndex::InsertNode(uint32_t id,uint32_t offset)
{
	nodes[id]=offset;
}
////////////////////////////////////////////////////
////////////////////////////////////////////////////