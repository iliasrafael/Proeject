#include "Graph.h"
#include "Components.h"
#include "SCC.h"
#include "GrailIndex.h"
#include "CC.h"
#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

int main(void)
{	
	int option=0;
	while(option<1 || option>4)
	{
		cerr << ">Please choose Input File  :)"<<endl;
		cerr << ">1 for Tiny File" << endl;
		cerr << ">2 for Small File" << endl;
		cerr << ">3 for Medium File" << endl;
		cerr << ">4 for Large File" << endl;
		cin >> option;	
	}

	ifstream myReadFile;
	if(option==1)
		myReadFile.open("tinyGraph.txt");
	else if(option==2)
		myReadFile.open("smallGraph.txt");
	else if(option==3)
		myReadFile.open("mediumGraph.txt");
	else if(option==4)
		myReadFile.open("large.txt");

	time_t now = time(0),end;
   	char* currtime = ctime(&now);
   	cerr << "Started at: " << currtime;
	Graph graph;
	unsigned int node;
	unsigned int edge;
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> node >>edge;
			if(!myReadFile.good())
				break;
			if(graph.search(node,edge))
				continue;
			graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge);
			graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node);
		}
	}
	myReadFile.close();
	uint32_t size;
	if(graph.getOutIndex()->getSize() > graph.getIncIndex()->getSize())
		size=graph.getOutIndex()->getSize();
	else
		size=graph.getIncIndex()->getSize();
	
	//scc.Print();
	//cout<<"Find: "<<scc.findSCCid(0)<<endl;
	//uint32_t s=1;
	//uint32_t t=3;
	//cout<<graph.estimateShortestPathStronglyConnectedComponents(&scc,s,t)<<endl;

	

	
	if(option==1)
		myReadFile.open("tinyWorkload_FINAL.txt");
	else if(option==2)
		myReadFile.open("smallWorkload_FINAL.txt");
	else if(option==3)
		myReadFile.open("mediumWorkload_static_FINAL.txt");
	else if(option==4)
		myReadFile.open("largeWorkload_48000_40.txt");

	char com;
	char r[8];
	bool kind;
	if(myReadFile.is_open()){
		myReadFile>>r;
		if(strcmp(r,"DYNAMIC")==0)
		{
			kind=1;
			uint32_t queriesnum=0;
			uint32_t updatenum=0;
			CC cc(size);
			cc.CCSearch(&graph);
			while(!myReadFile.eof())
			{
				myReadFile>>com;
				if(com!='F')
					myReadFile>>node>>edge;
				if(com=='A')
				{
					queriesnum++;
					if(graph.search(node,edge))
						continue;
					graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge);
					graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node);
					cc.InsertNewEdge(node,edge,updatenum);
				}
				else if(com=='Q')
				{	
					queriesnum++;
					if(cc.check(node,edge))
						cout<<graph.BBFS(node,edge,NULL)<<endl;
					else 
						cout<<"-1"<<endl;
				}
				if((double)(updatenum/queriesnum)>0.05)
				{
					cout<<"rebuilding.. "<<updatenum<<" "<<queriesnum<<endl;
					cc.rebuild();
					updatenum=0;
					queriesnum=0;
				}
			}
		}
		else
		{
			cout<<"SCC_Search: "<<endl;
			SCC scc = graph.SCC_Search();
			Graph hypergraph;
			hypergraph.creation(&scc,&graph);
			GrailIndex grailindex(scc.getComponentCount()+1);
			grailindex.buildGrailIndex(&hypergraph, scc.getComponentCount()+1);
			while(!myReadFile.eof())
			{
				myReadFile>>com;
				if(com!='F')
					myReadFile>>node>>edge;
				if(com=='Q')
				{
					if(grailindex.isReachableGrailIndex(node,edge)==1)
						cout<<graph.BBFS(node,edge,NULL)<<endl;
					else 
						cout<<"-1"<<endl;
				}
			}
		}
	}
	myReadFile.close();
	
	end = time(0);
   	currtime = ctime(&end);

   	cerr << "Finished at: " << currtime;
   	cerr << "After running for: "<< end-now<<"secs." <<endl;
	return 0;
}