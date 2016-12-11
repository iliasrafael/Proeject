#include "GrailIndex.h"
#include "Stack.h"

GrailIndex::GrailIndex::GrailIndex(uint32_t size)
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

void GrailIndex::buildGrailIndex(Graph* graph, uint32_t size)
{
	int offset;
	uint32_t curr = 0;
	int last;
	Stack stack;
	bool *visited;
	visited=(bool*)malloc(sizeof(bool)*size);
	uint32_t r = 1;
	uint32_t mr = 1;
	uint32_t* neigh;
	int* from;
	uint32_t* count;
	from=(int*)malloc(sizeof(int)*size);
	count=(uint32_t*)malloc(sizeof(uint32_t)*size);
	for(int i=0; i<size; i++)
	{
		visited[i]=false;
		from[i]=-1;
		count[i]=0;
	}
	list_node * cells;
	uint32_t head;
	uint32_t prev;

	for(int j=0; j<size; j++)
	{
		if(visited[j] == true)
			continue;

		stack.add(j);
		visited[j] = true;
		last=j;

		while(1)
		{
			if(count[last] < graph->getOutIndex()->getCount(last))
			{
				offset = graph->getOutIndex()->getPosition(last);
				cells=graph->getOutBuffer()->getListNode(offset);
				int pos=count[last]/N;
				offset=cells->getOffset();
				int metr=0;
				while(metr<pos)
				{	
					cells=graph->getOutBuffer()->getListNode(offset);
					offset=cells->getOffset();
					metr++;
				}
				neigh=cells->getNeighbors();
				curr=neigh[count[last]%N];
				count[last]++;
				if(visited[curr] == false)
				{
					stack.add(curr);
					visited[curr] = true;
					from[curr]=last;
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
				last = from[head];
				/*
				cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
				cout<<"ID :"<<head<<" [ "<<min_rank[head]<<" , "<<rank[head]<<" ]"<<endl;
				cout<<"~~~~~~~~~~~~~~~~~~"<<endl;
				*/
				if(last == -1)
					break;
			}

		}
	}
	free(visited);
	free(from);
	free(count);
}

uint32_t GrailIndex::find_min(uint32_t node_id, Graph* graph)
{
	uint32_t min=rank[node_id];
	int offset = graph->getOutIndex()->getPosition(node_id);
	//cout<<"OFFSET: "<<offset<<endl;
	if(offset == -1)
		return min;
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
	return min;
}

int GrailIndex::isReachableGrailIndex(uint32_t source, uint32_t target)
{
	if(min_rank[target] <= min_rank[source] && rank[target] <= rank[source]) //??
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