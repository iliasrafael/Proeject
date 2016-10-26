#include "Graph.h"
#include "list.h"
///////////////////////////////////////////////////////////////////////////////
/* GRAPH */
///////////////////////////////////////////////////////////////////////////////
NodeIndex* Graph::getOutIndex()
{
	return &out_index;
}
///////////////////////////////////////////////////////////////////////////////
NodeIndex* Graph::getIncIndex()
{
	return &inc_index;
}
//////////////////////////////////////////////////////////////////////////////
Buffer* Graph::getOutBuffer()
{
	return &out_buffer;
}
//////////////////////////////////////////////////////////////////////////////
Buffer* Graph::getIncBuffer()
{
	return &inc_buffer;
}
//////////////////////////////////////////////////////////////////////////////
bool Graph::Insert(NodeIndex *index,Buffer *buffer, uint32_t id,uint32_t id2)
{	

	while(id>=index->getSize()) {
		index->reallocation();
	}

	unsigned int last=buffer->getLast(); //fovamai
	if(index->getPosition(id)==-1)
	{
		if(last>=buffer->getSize())
			buffer->reallocation();
		int offset=buffer->InsertFirstNode(id2);
		index->InsertNode(id,offset);
	}
	else
	{
		int position = index->getPosition(id);
		bool res=buffer->getListNode(position)->Insert(id2);
		if(res==false)
			if(index->getLastBucket(id)!=0)
			{
				res=buffer->getListNode(index->getLastBucket(id))->Insert(id2);
			}
		if(res==false)
		{
			if(last>=buffer->getSize()) {
				buffer->reallocation();
			}

			if(buffer->getListNode(position)->getOffset()==-1)
				buffer->getListNode(position)->setOffset(last);
			else if(buffer->getListNode(index->getLastBucket(id))->getOffset()==-1)
				buffer->getListNode(index->getLastBucket(id))->setOffset(last);
			index->setLastBucket(id,last);
			buffer->getListNode(last)->Insert(id2);
			buffer->setLast(last+1);
		}
	}
}


int Graph::BBFS(uint32_t start , uint32_t target)
{
	List out_oura;
	List inc_oura;
	int count=0;
	bool result;
	//na kanume malloc to megalitero metaksi out k in
	int * visited=(int *)malloc(sizeof(int)*out_index.getSize());
	for(int i=0;i<out_index.getSize();i++)
		visited[i]=-1;
	if(start==target)
	{
		free (visited);
		return 0;
	}
	out_oura.push(start);
	inc_oura.push(target);
	while(!out_oura.empty() && !inc_oura.empty())
	{
		if(Update(out_index,out_buffer,count,out_oura,visited,0) || Update(inc_index,inc_buffer,count,inc_oura,visited,1))
		{
			free(visited);
			return count;
		}
	}	
	free (visited);
	return -1;
}

bool Graph::Update(NodeIndex &index,Buffer &buffer,int &count,List &oura,int *visited,int situation)
{
	unsigned int off;
	list_node * cells;
	uint32_t* neigh;
	int id;
	if(!oura.empty())
	{
		int size=oura.get_size();
		count++;
		for(int i=0;i<size;i++)
		{
			id=oura.remove();
			off=index.getPosition(id);
			while(off!=-1)
			{
				cells=buffer.getListNode(off);
				neigh=cells->getNeighbors();
				for(int i=0;i<cells->getLastNeighbor();i++)
				{
						if(visited[neigh[i]]==situation)
							return true;
						if(visited[neigh[i]]!=1-situation)
						{
							oura.push(neigh[i]);
							visited[neigh[i]]=1-situation;
						}
				}
				off=cells->getOffset();
			}
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
