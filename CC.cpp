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

int CC::UpdateIndex(uint32_t id,uint32_t id2)
{
	//cout<<"1 :"<<updateIndex[ccindex[id]]<<" 2 "<<updateIndex[ccindex[id2]]<<endl;
	if(id>size_update || id2>size_update)
		UpdatedoubleSize();
	if(updateIndex[ccindex[id]]==-1 && updateIndex[ccindex[id2]]==-1)//kai ta 2 
		updateIndex[ccindex[id]]=ccindex[id2];
	else if(updateIndex[ccindex[id]]==-1)//to 1o
		updateIndex[ccindex[id]]=updateIndex[ccindex[id2]];
	else if(updateIndex[ccindex[id2]]==-1)//to 2o
		updateIndex[ccindex[id2]]=updateIndex[ccindex[id]];
	else//kanena
	{
		int next=updateIndex[ccindex[id2]];
		int value=updateIndex[ccindex[id]];
		updateIndex[ccindex[id2]]=value;
		//cout<<"Val "<<value << " Next "<<next<<endl;
		while(next!=-1 && next!=value)
		{
			int temp=updateIndex[next];
			updateIndex[next]=value;
			next=temp;
			//cout<<"Val "<<value << " Next "<<next<<endl;
			//char a;
			//cin>>a;
		}
	}
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
void CC::InsertNewEdge(uint32_t id,uint32_t id2, uint32_t &count)
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
		ccindex[id2]=ccindex[id];
	else if(ccindex[id]!=ccindex[id2])
	{
		if(!check(id, id2))
		{	
			UpdateIndex(id, id2);
			count++;
		}
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
	else if(updateIndex[ccindex[id]]==updateIndex[ccindex[id2]] && updateIndex[ccindex[id]]!=-1)
		return true;
	else if(updateIndex[ccindex[id2]]==ccindex[id] || updateIndex[ccindex[id]]==ccindex[id2])
		return true;
	else
	{

		int source = ccindex[id];
		int target = ccindex[id2];
		int next = updateIndex[source];
		int prev = source;

		/*if(id == 224130	&& id2 == 1413549) {
				cout<<"Source : "<<source<<" target: "<<target<<" , "<<updateIndex[source]<<" , "<<updateIndex[target]<<endl;
				char a;
				cin>>a;
			}*/

		while(next!=-1)
		{
			/*if(id == 224130	&& id2 == 1413549) {
				cout<<next<<" , "<<prev<<" < "<<updateIndex[next]<<endl;
				char a;
				cin>>a;
			}*/
			if(prev == updateIndex[next])
			{
				//cout<<"break"<<endl;
				break;
			}	
			if(next == target){
				//cout<<"tr"<<endl;
				return true;
			}

			prev=next;
			next=updateIndex[next];
			
			//cout<<"Next: "<<next<<" Update: "<<updateIndex[next]<<endl;
			//cout<<"~~~~~~~~~~~~~~"<<endl;

		}
		return false;
	}
}

void CC::rebuild()
{
	for(int i=0;i<size_cc;i++)
	{
		if(ccindex[i]==-1)
			continue;
		if(updateIndex[ccindex[i]]!=-1)
			ccindex[i]=updateIndex[ccindex[i]];
	}
}