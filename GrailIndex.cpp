#include "GrailIndex.h"
#include "Stack.h"

GrailIndex::GrailIndex(uint32_t size)
{
	for(int i=0;i<GRAIL_NUMBER;i++)
	{
		rank[i] = (uint32_t *)malloc(sizeof(uint32_t)*size);
		assert(rank!=NULL);
		min_rank[i] = (uint32_t *)malloc(sizeof(uint32_t)*size);
		assert(min_rank!=NULL);

		/*for(int j=0; j<size; j++)
		{
			rank[i][j]=0;
			min_rank[i][j]=0;
		}*/
	}
}

GrailInfo::GrailInfo()
{
	visited=false;
	from=-1;
	count=0;
	next_off=-1;
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
int GrailInfo::getNext_off()
{
	return next_off;
}
void GrailInfo::setNext_off(int off)
{
	next_off=off;
}

void GrailIndex::buildGrailIndex(Graph* graph, uint32_t size,int flag)
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
	int next_off=-1;

	for(int j=0; j<size; j++)
	{
		if(grailinfo[j].getVisited() == true)
		{
			continue;
		}

		//if(graph->getOutIndex()->getPosition(j)<0 && graph->getIncIndex()->getPosition(j)<0)
			//continue;

		stack.add(j);
		grailinfo[j].setVisited(true);
		last=j;

		while(1)
		{
			if(grailinfo[last].getCount() < graph->getOutIndex()->getCount(last))
			{
				//cerr << "FIRST" << endl;
				
				if(grailinfo[last].getNext_off() == -1)
				{
					offset = graph->getOutIndex()->getPosition(last);
					cells=graph->getOutBuffer()->getListNode(offset);
					neigh=cells->getNeighbors();
					curr=neigh[grailinfo[last].getCount()%N];

				}
				else
				{
					cells=graph->getOutBuffer()->getListNode(grailinfo[last].getNext_off());
					neigh=cells->getNeighbors();
					curr=neigh[grailinfo[last].getCount()%N];
				}
				
				grailinfo[last].raiseCount();

				if(grailinfo[curr].getVisited() == false)
				{
					cerr << "FALSE" << endl;
					stack.add(curr);
					grailinfo[curr].setVisited(true);
					grailinfo[curr].setFrom(last);
					last=curr;
				}

				if(grailinfo[last].getCount()%N == 0)
				{
					grailinfo[last].setNext_off(cells->getOffset());
				}
			}
			else
			{
				//cerr<<"ROPALO2"<<endl;
				if(stack.empty())
					break;
				head = stack.pop();
				rank[flag][head] = r;
				min_rank[flag][head] = find_min(head, graph,flag);
				r++;
				prev=head;
				last = grailinfo[head].getFrom();
				
				cerr<<"~~~~~~~~~~~~~~~~~~"<<flag<<"~~~~~~~~~~~~~~~~~~"<<endl;
				cerr<<"ID :"<<head<<" [ "<<min_rank[flag][head]<<" , "<<rank[flag][head]<<" ]"<<endl;
				cerr<<"~~~~~~~~~~~~~~~~~~"<<flag<<"~~~~~~~~~~~~~~~~~~"<<endl;
				
				if(last == -1)
					break;
			}

		}
	}
	delete []grailinfo;
}

uint32_t GrailIndex::find_min(uint32_t node_id, Graph* graph,int flag)
{
	uint32_t min=rank[flag][node_id];
	int offset = graph->getOutIndex()->getPosition(node_id);
	//cout<<"OFFSET: "<<offset<<endl;
	if(offset != -1)
	{
		list_node * cells = graph->getOutBuffer()->getListNode(offset);
		uint32_t* neighbors = cells->getNeighbors();

		
		for(int j = 0; j<cells->getLastNeighbor(); j++)
		{
			if(min_rank[flag][neighbors[j]] < min)
				min = min_rank[flag][neighbors[j]];
		}
		offset = cells->getOffset();
		while(offset != -1) {
			neighbors = graph->getOutBuffer()->getListNode(offset)->getNeighbors();
			for(int j = 0; j<graph->getOutBuffer()->getListNode(offset)->getLastNeighbor(); j++)
			{
				if(min_rank[flag][neighbors[j]] < min)
					min = min_rank[flag][neighbors[j]];
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

	int counter=0;
	for(int i=0;i<GRAIL_NUMBER;i++)
	{
		if(min_rank[i][targetSccId] >= min_rank[i][sourceSccId] && rank[i][targetSccId] <= rank[i][sourceSccId]) //??
			continue;
		else
			return 0;
	}

	return 1;
}

void GrailIndex::setrank(uint32_t r, uint32_t i,int flag)
{
	rank[flag][i] = r;
}

uint32_t GrailIndex::getrank(uint32_t i,int flag)
{
	return rank[flag][i];
}

void GrailIndex::setminrank(uint32_t r, uint32_t i,int flag)
{
	min_rank[flag][i] = r;
}

uint32_t GrailIndex::getminrank(uint32_t i,int flag)
{
	return min_rank[flag][i];
}

GrailIndex::~GrailIndex()
{
	for(int i=0;i<GRAIL_NUMBER;i++)
	{
		free(rank[i]);
		free(min_rank[i]);
	}

	//free(rank);
	//free(min_rank);
		
}

/*void GrailIndex::buildGrailIndex22(Graph* graph, uint32_t size,int flag)
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
	int next_off=-1;
	int jj=-1;
	for(int j=0; j<size; j++)
	{
		if(j==size)
		{
			j=0;
			size=jj;
		}
		if(jj==-1)
		{
			while(j<size)
			{
				j++;
				if(graph->getIncIndex()->getPosition(j)<0)
				{	jj=j;
					break;
				}
			}
		}
		if(grailinfo[j].getVisited() == true)
		{
			//cerr<<"ROPALO"<<endl;
			continue;
		}

		//if(graph->getOutIndex()->getPosition(j)<0 && graph->getIncIndex()->getPosition(j)<0)
			//continue;

		stack.add(j);
		grailinfo[j].setVisited(true);
		last=j;

		while(1)
		{
			if(grailinfo[last].getCount() < graph->getOutIndex()->getCount(last))
			{
				//offset = graph->getOutIndex()->getPosition(last);
				//cells=graph->getOutBuffer()->getListNode(offset);
				//int pos = grailinfo[last].getCount()/N;
				//offset=cells->getOffset();
				//int metr=0;
				/*while(metr<pos)
				{	
					cells=graph->getOutBuffer()->getListNode(offset);
					offset=cells->getOffset();
					metr++;
				}
				//cerr<<"--->"<<metr<<endl;

				
				if(grailinfo[last].getNext_off() == -1)
				{
					offset = graph->getOutIndex()->getPosition(last);
					cells=graph->getOutBuffer()->getListNode(offset);
					neigh=cells->getNeighbors();
					curr=neigh[grailinfo[last].getCount()%N];

				}
				else
				{
					cells=graph->getOutBuffer()->getListNode(grailinfo[last].getNext_off());
					neigh=cells->getNeighbors();
					curr=neigh[grailinfo[last].getCount()%N];
				}
				
				grailinfo[last].raiseCount();

				if(grailinfo[curr].getVisited() == false)
				{
					//cerr<<"ROPALO11"<<endl;
					stack.add(curr);
					grailinfo[curr].setVisited(true);
					grailinfo[curr].setFrom(last);
					last=curr;
				}

				if(grailinfo[last].getCount()%N == 0)
				{
					grailinfo[last].setNext_off(cells->getOffset());
				}
			}
			else
			{
				if(stack.empty())
					break;
				head = stack.pop();
				rank[flag][head] = r;
				min_rank[flag][head] = find_min(head, graph,flag);
				r++;
				prev=head;
				last = grailinfo[head].getFrom();
				
				/*cerr<<"~~~~~~~~~~~~~~~~~~"<<flag<<"~~~~~~~~~~~~~~~~~~"<<endl;
				cerr<<"ID :"<<head<<" [ "<<min_rank[flag][head]<<" , "<<rank[flag][head]<<" ]"<<endl;
				cerr<<"~~~~~~~~~~~~~~~~~~"<<flag<<"~~~~~~~~~~~~~~~~~~"<<endl;
				
				if(last == -1)
					break;
			}

		}
	}
	delete []grailinfo;
}*/
void GrailIndex::buildGrailIndex22(Graph* graph, uint32_t size,int flag)
{
	int offset;
	int start=0;
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
	int next_off=-1;
	time_t t;
	srand((unsigned)time(&t));
	int first_source=0;
	uint32_t i;
	
	int start_flag=1;
	uint32_t pinakas[GRAIL_NUMBER],found=0;
	for (uint32_t i=0;i<size;i++){
		if(graph->getOutIndex()->getPosition(i)<0)
		{
			pinakas[found++]=i;
		}
		if(found>=GRAIL_NUMBER)
			break;
	}

	if(found<GRAIL_NUMBER)
	{
		for(int i=found;i<GRAIL_NUMBER;i++)
			pinakas[i]=pinakas[0];
	}
	int jj=pinakas[flag];
	int j = jj;
	do
	{
		if(j>=size)
			j=0;
		if(graph->getOutIndex()->getPosition(j)<0 && graph->getIncIndex()->getPosition(j)<0)
			continue;
		
		if(grailinfo[j].getVisited() == true)
		continue;
		stack.add(j);
		grailinfo[j].setVisited(true);
		last=j;

		while(1)
		{
			if(grailinfo[last].getCount() < graph->getOutIndex()->getCount(last))
			{
			
				if(grailinfo[last].getNext_off() == -1)
				{
					offset = graph->getOutIndex()->getPosition(last);
					cells=graph->getOutBuffer()->getListNode(offset);
					neigh=cells->getNeighbors();
					curr=neigh[grailinfo[last].getCount()%N];
				}
				else
				{
					cells=graph->getOutBuffer()->getListNode(grailinfo[last].getNext_off());
					neigh=cells->getNeighbors();
					curr=neigh[grailinfo[last].getCount()%N];
				}
				
				grailinfo[last].raiseCount();

				if(grailinfo[curr].getVisited() == false)
				{
					//cerr << "FALSE2" << endl;
					stack.add(curr);
					grailinfo[curr].setVisited(true);
					grailinfo[curr].setFrom(last);
					last=curr;
				}

				if(grailinfo[last].getCount()%N == 0)
				{
					grailinfo[last].setNext_off(cells->getOffset());
				}
			}
			else
			{
				if(stack.empty())
					break;
				head = stack.pop();
				rank[flag][head] = r;
				min_rank[flag][head] = find_min(head, graph,flag);
				r++;
				prev=head;
				last = grailinfo[head].getFrom();
				
				/*cerr<<"~~~~~~~~~~~~~~~~~~"<<flag<<"~~~~~~~~~~~~~~~~~~"<<endl;
				cerr<<"ID :"<<head<<" [ "<<min_rank[flag][head]<<" , "<<rank[flag][head]<<" ]"<<endl;
				cerr<<"~~~~~~~~~~~~~~~~~~"<<flag<<"~~~~~~~~~~~~~~~~~~"<<endl;*/
				
				if(last == -1)
					break;
			}
		}
	}while(!(jj==0 && j==size-1) && ++j!=jj );
	delete []grailinfo;
}
