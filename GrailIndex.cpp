#include "GrailIndex.h"
#include "Stack.h"

GrailIndex::GrailIndex(uint32_t size)
{
	rank = (uint32_t *)malloc(sizeof(uint32_t)*size);
	assert(rank!=NULL);
	min_rank = (uint32_t *)malloc(sizeof(uint32_t)*size);
	assert(min_rank!=NULL);

	for(int i=0; i<size; i++)
	{
		rank[i]=0;
		min_rank[i]=0;
	}
}

GrailInfo::GrailInfo()
{
	visited=false;
	from=-1;
	count=0;
}
bool GrailInfo::getVisited()
{
	return visited;
}
void GrailInfo::setVisited(bool visited_)
{
	visited=visited_;
}
int GrailInfo::getFrom()
{
	return from;
}
void GrailInfo::setFrom(int from_)
{
	from=from_;
}
uint32_t GrailInfo::getCount()
{
	return count;
}
void GrailInfo::raiseCount()
{
	count++;
}


void GrailIndex::buildGrailIndex(Graph* graph, uint32_t size)
{
	int offset;
	uint32_t curr = 0;
	int last;
	Stack stack;
	uint32_t r = 1;
	uint32_t mr = 1;
	uint32_t* neigh;
	GrailInfo * grailinfo=new GrailInfo[size];
	list_node * cells;
	uint32_t head;
	uint32_t prev;

	for(int j=0; j<size; j++)
	{
		if(grailinfo[j].getVisited() == true)
			continue;

		stack.add(j);
		grailinfo[j].setVisited(true);
		last=j;

		while(1)
		{
			if(grailinfo[last].getCount() < graph->getOutIndex()->getCount(last))
			{
				offset = graph->getOutIndex()->getPosition(last);
				cells=graph->getOutBuffer()->getListNode(offset);
				int pos = grailinfo[last].getCount()/N;
				offset=cells->getOffset();
				int metr=0;
				while(metr<pos)
				{	
					cells=graph->getOutBuffer()->getListNode(offset);
					offset=cells->getOffset();
					metr++;
				}
				neigh=cells->getNeighbors();
				curr=neigh[grailinfo[last].getCount()%N];
				grailinfo[last].raiseCount();
				if(grailinfo[curr].getVisited() == false)
				{
					stack.add(curr);
					grailinfo[curr].setVisited(true);
					grailinfo[curr].setFrom(last);
					last=curr;
				}
			}
			else
			{
				if(stack.empty())
					break;
				head = stack.pop();
				rank[head] = r;
				min_rank[head] = find_min(head, graph);
				r++;
				prev=head;
				last = grailinfo[head].getFrom();
				
				//cerr<<"~~~~~~~~~~~~~~~~~~"<<endl;
				//cerr<<"ID :"<<head<<" [ "<<min_rank[head]<<" , "<<rank[head]<<" ]"<<endl;
				//cerr<<"~~~~~~~~~~~~~~~~~~"<<endl;
				
				if(last == -1)
					break;
			}

		}
	}
	delete []grailinfo;
}

uint32_t GrailIndex::find_min(uint32_t node_id, Graph* graph)
{
	uint32_t min=rank[node_id];
	int offset = graph->getOutIndex()->getPosition(node_id);
	//cout<<"OFFSET: "<<offset<<endl;
	if(offset != -1)
	{
		list_node * cells = graph->getOutBuffer()->getListNode(offset);
		uint32_t* neighbors = cells->getNeighbors();

		
		for(int j = 0; j<cells->getLastNeighbor(); j++)
		{
			if(min_rank[neighbors[j]] < min)
				min = min_rank[neighbors[j]];
		}
		offset = cells->getOffset();
		while(offset != -1) {
			neighbors = graph->getOutBuffer()->getListNode(offset)->getNeighbors();
			for(int j = 0; j<graph->getOutBuffer()->getListNode(offset)->getLastNeighbor(); j++)
			{
				if(min_rank[neighbors[j]] < min)
					min = min_rank[neighbors[j]];
			}
			offset = graph->getOutBuffer()->getListNode(offset)->getOffset();
		}
		
	}
	
	
	return min;
}

int GrailIndex::isReachableGrailIndex(uint32_t source, uint32_t target,SCC* scc)
{
	//cerr<<"sourceId: "<<source<<endl;
	uint32_t sourceSccId = scc->findSCCid(source);
	//cerr<<"sourceSccId: "<<sourceSccId<<endl;
	uint32_t targetSccId = scc->findSCCid(target);
	if( sourceSccId == targetSccId )
		return 2;
	if(min_rank[targetSccId] >= min_rank[sourceSccId] && rank[targetSccId] <= rank[sourceSccId]) //??
		return 1;	//Maybe baby
	return 0;
}

void GrailIndex::setrank(uint32_t r, uint32_t i)
{
	rank[i] = r;
}

uint32_t GrailIndex::getrank(uint32_t i)
{
	return rank[i];
}

void GrailIndex::setminrank(uint32_t r, uint32_t i)
{
	min_rank[i] = r;
}

uint32_t GrailIndex::getminrank(uint32_t i)
{
	return min_rank[i];
}

GrailIndex::~GrailIndex()
{
	free(rank);
	free(min_rank);
}