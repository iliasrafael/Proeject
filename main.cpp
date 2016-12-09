#include "Graph.h"
#include "Components.h"
#include "SCC.h"
#include "GrailIndex.h"
#include <fstream>
#include <iostream>
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
		cin >> option;	
	}

	ifstream myReadFile;
	if(option==1)
		myReadFile.open("example.txt");
	else if(option==2)
		myReadFile.open("smallGraph.txt");
	else if(option==3)
		myReadFile.open("mediumGraph.txt");
	else if(option==4)
		myReadFile.open("input.txt");

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
	graph.CCSearch();
	cout<<"SCC_Search: "<<endl;
	SCC scc = graph.SCC_Search();
	//scc.Print();
	//cout<<"Find: "<<scc.findSCCid(0)<<endl;
	//uint32_t s=1;
	//uint32_t t=3;
	//cout<<graph.estimateShortestPathStronglyConnectedComponents(&scc,s,t)<<endl;

	Graph hypergraph;

	hypergraph.creation(&scc,&graph);
	/*
	hypergraph.Insert(hypergraph.getOutIndex(),hypergraph.getOutBuffer(),0,1);
	hypergraph.Insert(hypergraph.getIncIndex(),hypergraph.getIncBuffer(),1,0);
	hypergraph.Insert(hypergraph.getOutIndex(),hypergraph.getOutBuffer(),0,2);
	hypergraph.Insert(hypergraph.getIncIndex(),hypergraph.getIncBuffer(),2,0);
	hypergraph.Insert(hypergraph.getOutIndex(),hypergraph.getOutBuffer(),1,3);
	hypergraph.Insert(hypergraph.getIncIndex(),hypergraph.getIncBuffer(),3,1);
	hypergraph.Insert(hypergraph.getOutIndex(),hypergraph.getOutBuffer(),1,4);
	hypergraph.Insert(hypergraph.getIncIndex(),hypergraph.getIncBuffer(),4,1);
	hypergraph.Insert(hypergraph.getOutIndex(),hypergraph.getOutBuffer(),3,4);
	hypergraph.Insert(hypergraph.getIncIndex(),hypergraph.getIncBuffer(),4,3);
	hypergraph.Insert(hypergraph.getOutIndex(),hypergraph.getOutBuffer(),5,1);
	hypergraph.Insert(hypergraph.getIncIndex(),hypergraph.getIncBuffer(),1,5);
	*/

/*
	cout<<"SIZE: "<<hypergraph.getOutIndex()->getSize()<<endl;
  for(int i = 0; i<hypergraph.getOutIndex()->getSize(); i++) {
   cout<<"Node "<<i<<" :"<<endl;
   int offset = hypergraph.getOutIndex()->getPosition(i);
    if(offset == -1)
      continue;
   uint32_t* neighbors = hypergraph.getOutBuffer()->getListNode(offset)->getNeighbors();
   while(offset!=-1) {
    neighbors = hypergraph.getOutBuffer()->getListNode(offset)->getNeighbors();
    for(int j = 0; j<hypergraph.getOutBuffer()->getListNode(offset)->getLastNeighbor(); j++)
      cout<<neighbors[j]<<"  ";
    offset = hypergraph.getOutBuffer()->getListNode(offset)->getOffset();
   }
   
   cout<<endl;
  }
  */

	GrailIndex grailindex(scc.getComponentCount()+1);
	grailindex.buildGrailIndex(&hypergraph, scc.getComponentCount()+1);

	/*
	if(option==1)
		myReadFile.open("tinyWorkload_FINAL.txt");
	else if(option==2)
		myReadFile.open("smallWorkload_FINAL.txt");
	else if(option==3)
		myReadFile.open("mediumWorkload_FINAL.txt");
	char com;
	if(myReadFile.is_open()){
		while(!myReadFile.eof()){
			myReadFile>>com;
			if(com!='F')
				myReadFile>>node>>edge;
			if(com=='A')
			{
				if(graph.search(node,edge))
					continue;
				graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge);
				graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node);
			}
			if(com=='Q')
				cout<<graph.BBFS(node,edge)<<endl;
		}
	}
	myReadFile.close();
	cout<<"SCC_Search: "<<endl;
	graph.SCC_Search();
	*/
	
	end = time(0);
   	currtime = ctime(&end);

   	cerr << "Finished at: " << currtime;
   	cerr << "After running for: "<< end-now<<"secs." <<endl;
	return 0;
}