#include "Graph.h"
#include "ArrayList.h"
///////////////////////////////////////////////////////////////////////////////
/* GRAPH */
///////////////////////////////////////////////////////////////////////////////
Graph::Graph()
{
	visited=NULL;
	sq=0;
}
Graph::~Graph()
{
	for(int i=0;i<sq;i++)
	{	
		if(visited[i]!=NULL)
			free(visited[i]);
	}
	free(visited);

}
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
void Graph::visited_creation()
{
	int visited_size;
	if(out_index.getSize()>inc_index.getSize())
		visited_size=out_index.getSize();
	else
		visited_size=inc_index.getSize();
	int sqr=visited_size/100+1;
	if(sqr>sq)
	{
		visited=(int**)realloc(visited,sizeof(int*)*(sqr));
		for(int i=sq;i<sqr;i++)
			visited[i]=NULL;
		sq=sqr;
	}
	for(int i=0;i<sq;i++)
	{
		if(visited[i]!=NULL)
		{
			for(int j=0;j<100;j++)
				visited[i][j]=-1;
		}
	}
}
//////////////////////////////////////////////////////////////////////////////
bool Graph::Insert(NodeIndex *index,Buffer *buffer, uint32_t id,uint32_t id2)
{	

	while(id>=index->getSize()) {
		index->reallocation();
	}
	index->setCount(id);
	unsigned int last=buffer->getLast(); 
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
	return true;
}

bool Graph::search(uint32_t id, uint32_t id2)
{
	int count1=out_index.getCount(id);
	int count2=inc_index.getCount(id2);
	if(count1<0 || count2<0 )
		return false;
	NodeIndex *index;
	Buffer *buffer;
	if(count1<count2)
	{
		index = &out_index;
		buffer = &out_buffer;
	}
	else
	{
		index = &inc_index;
		buffer = &inc_buffer;
		id=id2;
	}

	int offset = index->getPosition(id);
	if(offset==-1)
		return false;
	uint32_t* neighbors = buffer->getListNode(offset)->getNeighbors();
	int offset2 = buffer->getListNode(offset)->getOffset();		
	for(int j = 0; j<buffer->getListNode(offset)->getLastNeighbor(); j++)
	{
		if(neighbors[j]==id)
			return true;
	}
	while(offset2!=-1) {
		neighbors = buffer->getListNode(offset2)->getNeighbors();
		for(int j = 0; j<buffer->getListNode(offset2)->getLastNeighbor(); j++)
		{
			if(neighbors[j]==id)
				return true;
		}
		offset2 = buffer->getListNode(offset2)->getOffset();
	}
	
	return false;
}

int Graph::BBFS(uint32_t start , uint32_t target)
{
	visited_creation();
	int bigger;
	int count=0;
	bool result;
	if(start==target)
		return 0;
	inc_oura.Set();
	out_oura.Set();
	out_oura.Insert(start);
	inc_oura.Insert(target);
	if(Update(out_index,out_buffer,count,out_oura,0))
		return count;
	while(!out_oura.empty() && !inc_oura.empty())
	{	
		if(out_oura.get_size()<inc_oura.get_size())
		{
			if(Update(out_index,out_buffer,count,out_oura,0))
				return count;
		}
		else{
			if(Update(inc_index,inc_buffer,count,inc_oura,1))
				return count;
		}
	}	
	return -1;
}

bool Graph::Update(NodeIndex &index,Buffer &buffer,int &count,ArrayList &oura,int situation)
{
	unsigned int off;
	list_node * cells;
	uint32_t* neigh;
	uint32_t id;
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
						int x=neigh[i]/100;
						int y=neigh[i]%100;
						if(visited[x]==NULL)
						{
							visited[x]=(int *)malloc(sizeof(int)*100);
							for(int i=0;i<100;i++)
								visited[x][i]=-1;
						}

						if(visited[x][y]==situation)
							return true;
						if(visited[x][y]!=1-situation)
						{
							oura.Insert(neigh[i]);
							visited[x][y]=1-situation;
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
