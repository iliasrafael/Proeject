#include "Graph.h"
#include "ArrayList.h"
#include "Components.h"
#include "SCC.h"
#include "Stack.h"

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
bool Graph::Insert(NodeIndex *index,Buffer *buffer, uint32_t id,uint32_t id2, int vers)
{	
	if(id == id2)
		return true;
	while(id>=index->getSize()) {
		index->reallocation();
	}
	index->setCount(id);
	uint32_t last=buffer->getLast(); 
	if(index->getPosition(id)==-1)
	{
		if(last>=buffer->getSize())
			buffer->reallocation();
		int offset=buffer->InsertFirstNode(id2, vers);
		index->InsertNode(id,offset);
	}
	else
	{
		int position = index->getPosition(id);
		bool res=buffer->getListNode(position)->Insert(id2, vers);
		if(res==false)
			if(index->getLastBucket(id)!=0)
			{
				res=buffer->getListNode(index->getLastBucket(id))->Insert(id2, vers);
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
			buffer->getListNode(last)->Insert(id2, vers);
			buffer->setLast(last+1);
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////////
bool Graph::search(uint32_t id, uint32_t id2)
{
	int count1=out_index.getCount(id);
	int count2=inc_index.getCount(id2);
	if(count1<=0 || count2<=0 )
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

//////////////////////////////////////////////////////////////////////////////
void visited_del(uint32_t **visited,int sqr)
{
	for(int i=0;i<sqr;i++)
	{	
		if(visited[i]!=NULL)
			free(visited[i]);
	}
	free(visited);
}

int Graph::BBFS(uint32_t start , uint32_t target,SCC *scc,bool scc_flag,GrailIndex * grailindex, int version)
{
	ArrayList inc_oura;
	ArrayList out_oura;

	int visited_size;
	uint32_t x1,y1;
	int scc_target;
	if(scc!=NULL)
		scc_target=scc->findSCCid(start);
	else
		scc_target=-1;
	if(out_index.getSize()>inc_index.getSize())
		visited_size=out_index.getSize();
	else
		visited_size=inc_index.getSize();
	int sqr=visited_size/100+1;
	uint32_t ** visited;
	visited=(uint32_t**)malloc(sizeof(uint32_t*)*(sqr));
	for(int i=0;i<sqr;i++)
		visited[i]=NULL;
	int bigger;
	int count=0;
	bool result;
	if(start==target)
		return 0;
	inc_oura.Set();
	out_oura.Set();
	out_oura.Insert(start);
	inc_oura.Insert(target);
	x1=start/100;
	y1=start%100;
	if(visited[x1]==NULL)
	{
		visited[x1]=(uint32_t *)malloc(sizeof(uint32_t)*100);
		for(int i=0;i<100;i++)
			visited[x1][i]=0;
	}
	visited[x1][y1]=2;
	x1=target/100;
	y1=target%100;
	if(visited[x1]==NULL)
	{
		visited[x1]=(uint32_t *)malloc(sizeof(uint32_t)*100);
		for(int i=0;i<100;i++)
			visited[x1][i]=0;
	}
	visited[x1][y1]=1;
	if(Update(out_index,out_buffer,count,out_oura,1,visited,scc,scc_flag,scc_target,grailindex,target, version))
	{
		visited_del(visited,sqr);
		return count;
	}
	while(!out_oura.empty() && !inc_oura.empty())
	{	
		if(out_oura.get_size()<inc_oura.get_size())
		{
			if(Update(out_index,out_buffer,count,out_oura,1,visited,scc,scc_flag,scc_target,grailindex,target, version))
			{
				visited_del(visited,sqr);
				return count;
			}
		}
		else{
			if(Update(inc_index,inc_buffer,count,inc_oura,2,visited,scc,scc_flag,scc_target,grailindex,start, version))
			{
				visited_del(visited,sqr);
				return count;
			}
		}
	}
	visited_del(visited,sqr);
	return -1;
}

//////////////////////////////////////////////////////////////////////////////
bool Graph::Update(NodeIndex &index,Buffer &buffer,int &count,ArrayList &oura,int situation,uint32_t** visited,SCC *scc,bool scc_flag,int scc_target,GrailIndex * grailindex,int target, int version)
{

	uint32_t off;
	list_node * cells;
	uint32_t* neigh;
	uint32_t id;
	int x;
	int y;
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
					if(version < cells->getProperties()[i]){
						//cerr<<version<<" "<<cells->getProperties()[i]<<endl;
						continue;
					}
					if(scc_flag && scc->findSCCid(neigh[i])!=scc_target)
						continue;
					if(grailindex!=NULL)
					{
						if(situation == 1)
						{
							if(grailindex->isReachableGrailIndex(neigh[i],target,scc)==0)
								continue;
						}
						else
						{
							if(grailindex->isReachableGrailIndex(target,neigh[i],scc)==0)
								continue;
						}
					}
					x=neigh[i]/100;
					y=neigh[i]%100;
					if(visited[x]==NULL)
					{
						visited[x]=(uint32_t *)malloc(sizeof(uint32_t)*100);
						for(int i=0;i<100;i++)
							visited[x][i]=0;
					}
					if(visited[x][y]==situation)
						return true;
					if(visited[x][y]!=3-situation)
					{
						oura.Insert(neigh[i]);
						visited[x][y]=3-situation;
					}
				}
				off=cells->getOffset();
			}
		}
	}
	return false;
}
//////////////////////////////////////////////////////////////////////////////
//                        END OF PART 1                                     //
//////////////////////////////////////////////////////////////////////////////

/*CC Graph::CCSearch()
{
	int componentId=-1;
	uint32_t visited_size;
	if(out_index.getSize()>inc_index.getSize())
		visited_size=out_index.getSize();
	else
		visited_size=inc_index.getSize();
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
		if(out_index.getCount(i)<=0 && inc_index.getCount(i)<=0)
			continue;
		out_oura.Set();
		componentId++;
		visited[i]=true;
		cc.Insert(i,componentId);
		CC_update(i,visited);
		while(out_oura.empty()==false)
		{
			current_node=out_oura.remove();
			CC_update(current_node,visited);
			cc.Insert(current_node,componentId);
		}
	}
	cout<<"Count of Components: "<<componentId+1<<endl;
	free(visited);
}

//////////////////////////////////////////////////////////////////////////////

void Graph::CC_update(uint32_t id,bool* visited)
{
	int off,off2;
	list_node * cells;
	uint32_t* neigh;
	off=out_index.getPosition(id);
	while(off!=-1)
	{
		cells=out_buffer.getListNode(off);
		neigh=cells->getNeighbors();
		for(int j=0;j<cells->getLastNeighbor();j++)
		{
			if(visited[neigh[j]]==true)
				continue;
			out_oura.Insert(neigh[j]);
			visited[neigh[j]]=true;
		}
		off=cells->getOffset();
	}
	off2=inc_index.getPosition(id);
	while(off2!=-1)
	{
		cells=inc_buffer.getListNode(off2);
		neigh=cells->getNeighbors();
		for(int j=0;j<cells->getLastNeighbor();j++)
		{
			if(visited[neigh[j]]==true)
				continue;
			out_oura.Insert(neigh[j]);
			visited[neigh[j]]=true;
		}
		off2=cells->getOffset();
	}

}*/

//////////////////////////////////////////////////////////////////////////////
SCC Graph::SCC_Search()
{
	uint32_t visited_size;
	list_node * cells;
	uint32_t* neigh;
	uint32_t scc_id=0;
	if(out_index.getSize()>inc_index.getSize())
		visited_size=out_index.getSize();
	else
		visited_size=inc_index.getSize();
	//cout<<"SIZE: " <<visited_size<<endl;
	SCC scc(visited_size); // thelei free
	Stack stack;
	InfoTable * table=new InfoTable[visited_size];
	uint32_t index=1;
	uint32_t last;
	int offset=-1;
	uint32_t current=0;

	for(uint32_t i=0;i<visited_size;i++)
	{

		////cout<<"kombos "<<i<<endl;
		////cout<<" b"<<out_index.getPosition(i)<<endl;
		if(table[i].getIndex() != 0 || (out_index.getPosition(i)<0 && inc_index.getPosition(i)<0))
			continue;

		table[i].setIndex(index);
		table[i].setLowLink(index);
		index++;
		stack.add(i);
		table[i].stacked();
		table[i].setCount();
		table[i].setFrom(-1);
		//table[i].do_defined();
		last=i;
		while(1)
		{	
			if(table[last].getCount()<out_index.getCount(last))
			{
				//cout<<"Last : "<<last<<endl;
				//cout<<table[last].getCount()<<" < "<<out_index.getCount(last)<<endl;
				//off=out_index.getPosition(last);
				//cout<<"Last: "<<last<<"Offset: "<<off<<endl;
				//cells=out_buffer.getListNode(off);
				//int pos=table[last].getCount()/N;
				//off=cells->getOffset();
				//int metr=0;
				/*while(metr<pos)
				{	
					cells=out_buffer.getListNode(off);
					off=cells->getOffset();
					metr++;
				}*/
				//neigh=cells->getNeighbors();
				//uint32_t current=neigh[table[last].getCount()%N];
				//table[last].AddCount();

				if(table[last].getNext_off() == -1)
				{
					offset = getOutIndex()->getPosition(last);
					cells = getOutBuffer()->getListNode(offset);
					neigh = cells->getNeighbors();
					current = neigh[table[last].getCount()%N];
				}
				else
				{
					cells = getOutBuffer()->getListNode(table[last].getNext_off());
					neigh = cells->getNeighbors();
					current = neigh[table[last].getCount()%N];
				}

				table[last].AddCount();

				if(table[last].getCount()%N == 0)
				{
					table[last].setNext_off(cells->getOffset());
				}
				
				if(table[current].getIndex() == 0)
				{
					table[current].setFrom((int)last);
					table[current].setCount();
					table[current].setIndex(index);
					table[current].setLowLink(index);
					index++;
					stack.add(current);
					table[current].stacked();
					//table[current].do_defined();
					last=current;
				}
				else if(table[current].IsStacked())
				{
					if(table[last].getLowLink()<table[current].getIndex())
						table[last].setLowLink(table[last].getLowLink());
					else
						table[last].setLowLink(table[current].getIndex());
				}

				
			}
			else
			{
				//cout<<"ELSE"<<endl;
				if(table[last].getLowLink() == table[last].getIndex())
				{
					uint32_t head;
						head=stack.pop();
						table[head].UnStacked();

						scc.Insert(scc_id,head);
						while(head!=last) {
							head=stack.pop();
							//cout<<"kefalaki "<<table[head].getFrom()<<" apo "<<head<<endl;
							table[head].UnStacked();
							scc.Insert(scc_id,head);
							//counter++;
						}  //isws dn xriazetai elegxos to evala gia to segm
						scc_id++;	
					//}
				}	
				uint32_t from;
				from=table[last].getFrom();
				if(from!=-1)
				{
					if(table[from].getLowLink()<table[last].getLowLink())
						table[from].setLowLink(table[from].getLowLink());
					else
						table[from].setLowLink(table[last].getLowLink());
					last=from;
				}
				else
				{
					//cout<<"Freeedom"<<endl;
					break;
				}
			}
		}
	}
	//scc.Print();
	cout<<scc.getComponentCount()+1<<endl;
	delete []table;
	return scc;
}
/*int Graph::estimateShortestPathStronglyConnectedComponents(SCC *scc,uint32_t source_node, uint32_t target_node)
{
	if(scc->findSCCid(source_node)!=scc->findSCCid(target_node))
		return -1;
	else
		return BBFS(source_node,target_node,scc,true,NULL);
}*/


void Graph::creation(SCC *scc,Graph * graph)
{
	uint32_t current;
	list_node * cells;
	uint32_t* neigh;
	uint32_t off;
	NodeIndex * index =graph->getOutIndex();
	Buffer * buffer=graph->getOutBuffer();
	for(int i=0;i<=scc->getComponentCount();i++)
	{
		Component *comp=scc->getComponent(i);
		for(uint32_t j=0;j<comp->getNodesCount();j++)
		{
			current=comp->getNode(j);
			off=index->getPosition(current);
			while(off!=-1)
			{
				cells=buffer->getListNode(off);
				neigh=cells->getNeighbors();
				for(int y=0;y<cells->getLastNeighbor();y++)
				{
					uint32_t target=scc->findSCCid(neigh[y]);
					if(target!=i)
					{
						Insert(getOutIndex(),getOutBuffer(),i,target,0);
						Insert(getIncIndex(),getIncBuffer(),target,i,0);
					}
				}
				off=cells->getOffset();
			}
		}
	}

}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////