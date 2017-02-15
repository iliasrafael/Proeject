#include "Graph.h"
#include "Components.h"
#include "SCC.h"
#include "GrailIndex.h"
#include "CC.h"
#include <fstream>
#include <iostream>
#include <cstring>
int thread_flag=1;
int stop_threads=1;
using namespace std;

int main(void)
{	
	int option=0;
	while(option<1 || option>6)
	{
		cerr << ">Please choose Input File  :)"<<endl;
		cerr << ">1 for Tiny File" << endl;
		cerr << ">2 for Small File" << endl;
		cerr << ">3 for Medium Dynamic File" << endl;
		cerr << ">4 for Medium Static File" << endl;
		cerr << ">5 for Large Dynamic File" << endl;
		cerr << ">6 for Large Static File" << endl;
		cin >> option;	
	}

	ifstream myReadFile;
	if(option==1)
		myReadFile.open("tinyGraph.txt");
	else if(option==2)
		myReadFile.open("smallGraph.txt");
	else if(option==3 || option==4)
		myReadFile.open("mediumGraph.txt");
	else if(option==6 || option==5)
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
			graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge,0);
			graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node,0);
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
		myReadFile.open("smallWorkload.txt");
	else if(option==3)
		myReadFile.open("mediumWorkload_FINAL.txt");
	else if(option==4)
		myReadFile.open("mediumWorkload_static_FINAL.txt");
	else if(option==5)
		myReadFile.open("largeWorkload_6000_20.txt");
	else if(option==6)
		myReadFile.open("largeWorkload_48000_40.txt");
		
	char com;
	char r[9];
	bool kind;
	int check;
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
					graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge,0);
					graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node,0);
					cc.InsertNewEdge(node,edge, &updatenum,0);
				}
				if(com=='Q')
				{	 
					queriesnum++;
					check = cc.check(node,edge);
					if( check >= 0)
						cout<<graph.BBFS(node,edge,NULL,false,NULL,0)<<endl;
					else
						cout<<"-1"<<endl;		
				}
				if(updatenum > 500)
				{
					cerr<<"rebuilding.. "<<updatenum<<" "<<queriesnum<<endl;
					cc.rebuild(&graph);
					updatenum=0;
					queriesnum=0;
				}
			}
			cerr << "UpdateNum = " << updatenum << endl;

		}
		else
		{

			SCC scc = graph.SCC_Search();
			Graph hypergraph;

			hypergraph.creation(&scc,&graph);

			GrailIndex grailindex(scc.getComponentCount()+1);
			grailindex.buildGrailIndex(&hypergraph, scc.getComponentCount()+1,0);

			while(!myReadFile.eof())
			{
				myReadFile>>com;
				if(com!='F')
					myReadFile>>node>>edge;
				if(com=='Q')
				{

					if(grailindex.isReachableGrailIndex(node,edge,&scc)==1)
						cout<<graph.BBFS(node,edge,&scc,false,&grailindex,0)<<endl;
					else if(grailindex.isReachableGrailIndex(node,edge,&scc)==2)
						cout<<graph.BBFS(node,edge,&scc,true,NULL,0)<<endl;
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
