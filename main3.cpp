#include <fstream>
#include <iostream>
#include <cstring>
#include "JobScheduler.h"
#include "Graph.h"
#include "Components.h"
#include "SCC.h"
#include "GrailIndex.h"
#include "CC.h"

using namespace std;

int main(int argc, char const *argv[])
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
		myReadFile.open("tiny/tinyGraph.txt");
	else if(option==2)
		myReadFile.open("small/example.txt");
	else if(option==3 || option==4)
		myReadFile.open("medium/mediumGraph.txt");
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
		myReadFile.open("tiny/tinyWorkload_FINAL.txt");
	else if(option==2)
		myReadFile.open("small/exampleWorkload.txt");
	else if(option==3)
		myReadFile.open("medium/mediumWorkload_FINAL.txt");
	else if(option==4)
		myReadFile.open("medium/mediumWorkload_static_FINAL.txt");
	else if(option==5)
		myReadFile.open("largeWorkload_6000_20.txt");
	else if(option==6)
		myReadFile.open("largeWorkload_48000_40.txt");
		
	char com;
	char r[9];

	//Job job(1,2,0);
	JobScheduler js(5);
	//js.submit_job(job);


	bool isstatic;
	int order = 0;

	if(myReadFile.is_open()){
		myReadFile>>r;
		if(strcmp(r,"DYNAMIC")==0)
		{
			isstatic = false;

		}
		else
		{
			isstatic = true;

			cerr<<"SCC_Search: "<<endl;
			SCC scc = graph.SCC_Search();
			Graph hypergraph;
			cerr<<"Building HyperGraph . . . "<< endl;
			hypergraph.creation(&scc,&graph);
			cerr<<"Running Grail . . ."<<endl;
			GrailIndex grailindex(scc.getComponentCount()+1);
			grailindex.buildGrailIndex(&hypergraph, scc.getComponentCount()+1);
			cerr<<"Grail Ready"<<endl;

			while(!myReadFile.eof())
			{
				myReadFile>>com;
				while(com != 'F')
				{
					if(com == 'A')
					{
						myReadFile>>node>>edge;
						continue;
					}
					myReadFile>>node>>edge;
					cout<<com;
					cout<<" Input: "<<node<<" "<<edge<<endl;
					Job job(&graph, &scc, &grailindex, node, edge, 1, order, isstatic);
					js.submit_job(job);
					order++;
				}
			}

		}

	}
	return 0;
}
