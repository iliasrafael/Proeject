#include "Graph.h"
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
			{
				res=buffer->cells[index->last_bucket[id]].Insert(id2);
			}
		if(res==false)
		{
			if(last>=buffer->getSize()) {
				buffer->reallocation();
			}

			if(buffer->cells[position].offset==0)
				buffer->cells[position].offset=last;
			else if(buffer->cells[index->last_bucket[id]].offset==0)
				buffer->cells[index->last_bucket[id]].offset=last;
			index->last_bucket[id]=last;
			buffer->cells[last].Insert(id2);
			buffer->setLast(last+1);
		}
	}
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
