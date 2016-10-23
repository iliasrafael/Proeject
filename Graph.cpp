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

			if(buffer->getListNode(position)->getOffset()==0)
				buffer->getListNode(position)->setOffset(last);
			else if(buffer->getListNode(index->getLastBucket(id))->getOffset()==0)
				buffer->getListNode(index->getLastBucket(id))->setOffset(last);
			index->setLastBucket(id,last);
			buffer->getListNode(last)->Insert(id2);
			buffer->setLast(last+1);
		}
	}
}

int Graph::BBFS(uint32_t start , uint32_t target)
{
	list* out_oura=new list();
	list* inc_oura=new list();
	int * visited=malloc(sizeof(int)*out_index.getSize());
	for(int i=0;i<out_index.getSize();i++)
		visited=-1;
	int count=0;
	if(start==target)
		return 0;
	out_oura->push(start);
	inc_oura->push(target);

	unsigned int off;
	int id;
	unsigned int off2;=inc_buffer.nodes[target];
	while(!out_oura->empty() && !inc_oura->empty())
	{
		if(!out_oura->empty())
		{
			id=out_oura->remove();
			off=out_index.nodes[id];
			if(visited[id]!=-1)
				return visited[id];
			else
				visited[id]==
			while(off!=0)
			{
				cells=buffer->getListNode(off);
				for(int i=0;i<cells.getLastNeighbor();i++)
					oura->push(neighbors[i]);
				off=cells.getOffset();
			}
		}




	}

	/*
	while(!oura->empty())
	{
		list_node *cells;
		uint32_t* neighbors =cells->getNeighbors();
		while(off!=0)
		{
			cells=buffer->getListNode(off);
			for(int i=0;i<cells.getLastNeighbor();i++) //na ginei sinartisulitsa
			{
				bool t=oura->find();
				if(t) return count;
				else oura->push(neighbors[i]);
			}
			off=cells.getOffset();
		}

		count++;
	}*/

}


///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
