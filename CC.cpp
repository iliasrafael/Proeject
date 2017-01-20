#include "CC.h"
#include <iostream>

using namespace std;
CC::CC(uint32_t size_)
{
	ccindex=(int*)malloc(size_*sizeof(int));
	assert(ccindex!=NULL);
	for(int i=0;i<size_;i++)
		ccindex[i]=-1;
	updateIndex = new Graph;
	metricVal=0;
	size_cc=size_;
}
CC::~CC()
{
	free(ccindex);
	delete updateIndex;
}
void CC::Insert(uint32_t nodeId,uint32_t componentId)
{
	ccindex[nodeId]=componentId;
}

int CC::UpdateIndex(int componentId1,int componentId2, int vers)
{
	if(updateIndex->search(componentId1,componentId2))
		return 0;
	updateIndex->Insert(updateIndex->getOutIndex(),updateIndex->getOutBuffer(),componentId1,componentId2,vers);
	updateIndex->Insert(updateIndex->getOutIndex(),updateIndex->getOutBuffer(),componentId2,componentId1,vers);
	updateIndex->Insert(updateIndex->getIncIndex(),updateIndex->getIncBuffer(),componentId1,componentId2,vers);
	updateIndex->Insert(updateIndex->getIncIndex(),updateIndex->getIncBuffer(),componentId2,componentId1,vers);
	return 1;
}

void CC::InsertNewEdge(uint32_t id,uint32_t id2, uint32_t *count, int vers)
{
	if(id>size_cc || id2>size_cc)
		CCDoubleSize();
	if(ccindex[id]==-1 && ccindex[id2]==-1)
	{	
		ccindex[id]=counter;
		ccindex[id2]=counter;
		counter++;//isws lathos
	}
	else if(ccindex[id]==-1)
		ccindex[id]=ccindex[id2];
	else if(ccindex[id2]==-1)
		ccindex[id2]=ccindex[id];
	else if(ccindex[id]!=ccindex[id2])
	{
			if(UpdateIndex(ccindex[id], ccindex[id2], vers))
				(*count)++;
	}
	
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
	//cout<<"Count of Components: "<<componentId+1<<endl;
	counter=componentId+1;
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
int CC::check(uint32_t id,uint32_t id2)
{	
	//cerr << "NodeId1 = " << id << "ComponentId1 = " << ccindex[id] << endl;
	//cerr << "NodeId2 = " << id2 << "ComponentId2 = " << ccindex[id2] << endl;
	if(ccindex[id]==ccindex[id2])
		return 1;
	else  
		return updateIndex->BBFS(ccindex[id],ccindex[id2],NULL,false,NULL,0);
}

void CC::rebuild(Graph * graph)
{
	for(int i=0;i<size_cc;i++)
		ccindex[i]=-1;
	delete updateIndex;
	updateIndex = new Graph;
	CCSearch(graph);
}