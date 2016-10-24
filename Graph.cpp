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
	List* out_oura = new List();
	List* inc_oura = new List();
	int * visited = (int *)malloc(sizeof(unsigned int)*out_index.getSize());
	for(int i=0;i<out_index.getSize();i++)
		visited[i]=-1;
	int count=0;
	list_node * cells;
	uint32_t* neigh;
	if(start==target)
		return 0;
	out_oura->push(start);
	inc_oura->push(target);
	int visit_count=0;

	unsigned int off;
	int id;
	unsigned int off2;
	while(!out_oura->empty() && !inc_oura->empty())
	{
		if(visit_count == out_index.getSize()-1) {
			return -1;
		}
		if(!out_oura->empty())
		{
			int size=out_oura->get_size();
			count++;
			for(int i=0;i<size;i++)
			{
				id=out_oura->remove();
				//cout<<"id "<<id<<endl;
				off=out_index.getPosition(id);
				if(visited[id]==-1) 
				{
					visited[id]=1;
					visit_count++;
				}
					
				while(off!=-1)
				{
					cells=out_buffer.getListNode(off);
					neigh=cells->getNeighbors();
					for(int i=0;i<cells->getLastNeighbor();i++)
					{
						if(visited[neigh[i]]==0)
							return count-1;
						if(visited[neigh[i]]!=1)
							out_oura->push(neigh[i]);
					}
					off=cells->getOffset();
				}
			}
		}
		if(!inc_oura->empty())
		{
			int size=inc_oura->get_size();
			count++;
			for(int i=0;i<size;i++)
			{
				id=inc_oura->remove();
				//cout<<"id tou inc "<<id<<endl;
				off2=inc_index.getPosition(id);
				if(visited[id]==-1) 
				{
					visited[id]=0;
					visit_count++;
				}
					
				while(off2!=-1)
				{
					cells=inc_buffer.getListNode(off2);
					neigh=cells->getNeighbors();
					for(int i=0;i<cells->getLastNeighbor();i++)
					{
						if(visited[neigh[i]]==1)
							return count-1;
						if(visited[neigh[i]]!=0)
							inc_oura->push(neigh[i]);
					}
					off2=cells->getOffset();
				}
			}
		}
	}
	return -1;
}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
