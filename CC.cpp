#include "CC.h"
CC::CC(uint32_t size_)
{
	ccindex=(int*)malloc(size_*sizeof(int));
	assert(ccindex!=NULL);
	for(int i=0;i<size_;i++)
		ccindex[i]=-1;
	metricVal=0;
	size_cc=size_;
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
	if(componentId1>size_update || componentId2>size_update)
		UpdatedoubleSize();
	updateIndex[ccindex[componentId2]]=ccindex[componentId1];
}

void CC::UpdatedoubleSize()
{
	int temp=size_update;
	size_update*=2;
	updateIndex=(int*)realloc(updateIndex,size_update*sizeof(int));
	assert(updateIndex!=NULL);
	for(int i=temp;i<size_update;i++)
		updateIndex[i]=-1;
}
void CC::InsertNewEdge(uint32_t id,uint32_t id2)
{
	if(id>size_cc || id2>size_cc)
		CCDoubleSize();
	if(ccindex[id]==-1 && ccindex[id2]==-1)
	{
		if(counter>size_update)
			UpdatedoubleSize();
		ccindex[id]=counter;
		ccindex[id2]=counter;
		counter++;//isws lathos
	}
	else if(ccindex[id]==-1)
		ccindex[id]=ccindex[id2];
	else if(ccindex[id2]==-1)
		ccindex[id2]==ccindex[id];
}
void CC::CCDoubleSize()
{
	int temp=size_cc;
	size_cc*=2;
	ccindex=(int*)realloc(ccindex,size_cc*sizeof(int));
	for(int i=temp;i<size_cc;i++)
		ccindex[i]=-1;
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
	size_update=componentId+1;
	counter=size_update;
	updateIndex=(int*)malloc(size_update*sizeof(int));
	assert(updateIndex!=NULL);
	for(int i=0;i<size_update;i++)
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
	for(int i=0;i<size_update;i++)
	{
		if(updateIndex[ccindex[i]]!=-1)
			ccindex[i]=updateIndex[ccindex[i]];
	}
}