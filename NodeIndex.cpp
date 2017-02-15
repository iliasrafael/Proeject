#include "NodeIndex.h"
///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
NodeIndex::NodeIndex()
{
	nodes=(int*)malloc(sizeof(int)*NodeIndexSize);
	assert(nodes!=NULL);
	last_bucket=(uint32_t *)malloc(sizeof(uint32_t)*NodeIndexSize);
	assert(last_bucket!=NULL);
	count=(uint32_t *)malloc(sizeof(uint32_t)*NodeIndexSize);
	assert(count!=NULL);
	for(int i=0;i<NodeIndexSize;i++){
		nodes[i]=-1;
		last_bucket[i]=0;
		count[i]=0;
	}
	size=NodeIndexSize;
}
void NodeIndex::reallocation()
{

	size*=2;
	nodes = (int*) realloc(nodes, sizeof(int)*size);
	assert(nodes!=NULL);
	last_bucket= (uint32_t*) realloc(last_bucket, sizeof(uint32_t)*size);
	assert(last_bucket!=NULL);
	count= (uint32_t*) realloc(count, sizeof(uint32_t)*size);
	assert(count!=NULL);
	for(int i =size/2; i<size; i++)
	{
		nodes[i]=-1;
		last_bucket[i]=0;
		count[i]=0;
	}
}
////////////////////////////////////////////////////
NodeIndex::~NodeIndex()
{
	free(nodes);
	free(last_bucket);
	free(count);
}
////////////////////////////////////////////////////
int* NodeIndex::getNodes()
{
	return nodes;
}
////////////////////////////////////////////////////
int NodeIndex::getPosition(uint32_t i)
{
	if(i>=size)
		return -1;
	return nodes[i];
}
////////////////////////////////////////////////////
uint32_t NodeIndex::getLastBucket(uint32_t i)
{
	return last_bucket[i];
}
////////////////////////////////////////////////////
uint32_t NodeIndex::getSize()
{
	return size;
}
////////////////////////////////////////////////////

////////////////////////////////////////////////////
void NodeIndex::setSize(uint32_t size_)
{
	size=size_;
}
uint32_t NodeIndex::getCount(uint32_t id)
{

	if(count!=NULL &&  id < size){
		return count[id];
	}
	else {
		return 0;
	}
}
void NodeIndex::setCount(uint32_t id)
{
	count[id]++;
}
////////////////////////////////////////////////////
void NodeIndex::setLastBucket(uint32_t i,uint32_t last)
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