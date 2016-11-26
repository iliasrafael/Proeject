#include "NodeIndex.h"
///////////////////////////////////////////////////////////////////////////////
/* NODE INDEX */
///////////////////////////////////////////////////////////////////////////////
NodeIndex::NodeIndex()
{
	nodes=(int*)malloc(sizeof(int)*NodeIndexSize);
	assert(nodes!=NULL);
	last_bucket=(unsigned int *)malloc(sizeof(unsigned int)*NodeIndexSize);
	assert(last_bucket!=NULL);
	count=(unsigned int *)malloc(sizeof(unsigned int)*NodeIndexSize);
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
	//cout<<"REALLOCED"<<endl;
	size*=2;
	nodes = (int*) realloc(nodes, sizeof(int)*size);
	assert(nodes!=NULL);
	last_bucket= (unsigned int*) realloc(last_bucket, sizeof(unsigned int)*size);
	assert(last_bucket!=NULL);
	count= (unsigned int*) realloc(count, sizeof(unsigned int)*size);
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
int NodeIndex::getPosition(unsigned int i)
{
	if(i>=size)
		return -1;
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
unsigned int NodeIndex::getCount(unsigned int id)
{
	//cout<<"Size: "<<size<<" id: "<<id<<endl;
	//cout<<"Count: "<<count[id]<<endl;
	if(count!=NULL &&  id < size){
		//cout<<"---->1"<<endl;
		return count[id];
	}
	else {
		//cout<<"---->2"<<endl;
		return 0;
	}
}
void NodeIndex::setCount(unsigned int id)
{
	count[id]++;
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