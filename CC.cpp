#include "CC.h"
CC::CC(uint32_t size_)
{
	ccindex=(uint32_t*)malloc(size_*sizeof(uint32_t));
	assert(ccindex!=NULL);
	metricVal=0;
	size=size_;
}
CC::~CC()
{
	free(ccindex);
}
void CC::Insert(uint32_t nodeId,uint32_t componentId)
{
	ccindex[nodeId]=componentId;
}
int CC::UpdateIndex(uint32_t componentId1,uint32_t componentId2)
{
	//if(componentId1>size || componentId2>size)
		//doubleSize();
	updateIndex[ccindex[componentId2]]=ccindex[componentId1];
}


void CC::CCSearch(Graph* graph)
{
	ArrayList out_oura;
	int componentId=-1;
	uint32_t visited_size;
	if(graph->getOutIndex()->getSize()>graph->getIncIndex()->getSize())
		visited_size=graph->getOutIndex()->getSize();
	else
		visited_size=graph->getIncIndex()->getSize();
	bool *visited;
	visited=(bool*)malloc(sizeof(bool)*visited_size);
	for(uint32_t i=0;i<visited_size;i++)
		visited[i]=false;
	uint32_t current_node;
	int off;
	CC cc(visited_size);
	for(uint32_t i=0;i<visited_size;i++)
	{
		if(visited[i]==true)
			continue;
		if(graph->getOutIndex()->getCount(i)<=0 && graph->getIncIndex()->getCount(i)<=0)
			continue;
		out_oura.Set();
		componentId++;
		visited[i]=true;
		Insert(i,componentId);
		CC_update(graph,i,visited,&out_oura);
		while(out_oura.empty()==false)
		{
			current_node=out_oura.remove();
			CC_update(graph,current_node,visited,&out_oura);
			Insert(current_node,componentId);
		}
	}
	cout<<"Count of Components: "<<componentId+1<<endl;
	size=componentId+1;
	updateIndex=(int*)malloc(size*sizeof(int));
	assert(updateIndex!=NULL);
	for(int i=0;i<size;i++)
		updateIndex[i]=-1;
	free(visited);
}

//////////////////////////////////////////////////////////////////////////////

void CC::CC_update(Graph* graph,uint32_t id,bool* visited,ArrayList* out_oura)
{
	int off,off2;
	list_node * cells;
	uint32_t* neigh;
	off=graph->getOutIndex()->getPosition(id);
	while(off!=-1)
	{
		cells=graph->getOutBuffer()->getListNode(off);
		neigh=cells->getNeighbors();
		for(int j=0;j<cells->getLastNeighbor();j++)
		{
			if(visited[neigh[j]]==true)
				continue;
			out_oura->Insert(neigh[j]);
			visited[neigh[j]]=true;
		}
		off=cells->getOffset();
	}
	off2=graph->getIncIndex()->getPosition(id);
	while(off2!=-1)
	{
		cells=graph->getIncBuffer()->getListNode(off2);
		neigh=cells->getNeighbors();
		for(int j=0;j<cells->getLastNeighbor();j++)
		{
			if(visited[neigh[j]]==true)
				continue;
			out_oura->Insert(neigh[j]);
			visited[neigh[j]]=true;
		}
		off2=cells->getOffset();
	}

}
bool CC::check(uint32_t id,uint32_t id2)
{
	if(ccindex[id]==ccindex[id2])
		return true;
	else if(updateIndex[ccindex[id2]]==ccindex[id])
		return true;
	return false;
}

void CC::rebuild()
{
	for(int i=0;i<size;i++)
	{
		if(updateIndex[ccindex[i]]!=-1)
			ccindex[i]=updateIndex[ccindex[i]];
	}
}