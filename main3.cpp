#include <fstream>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "JobScheduler.h"
#include "Graph.h"
#include "Components.h"
#include "SCC.h"
#include "GrailIndex.h"
#include "CC.h"
int thread_flag=1;
int stop_threads=1;
using namespace std;

int main(int argc, char const *argv[])
{

	int option=0;
	while(option<1 || option>7)
	{
		cerr << ">Please choose Input File  :)"<<endl;
		cerr << ">1 for Tiny File" << endl;
		cerr << ">2 for Small File" << endl;
		cerr << ">3 for Medium Dynamic File" << endl;
		cerr << ">4 for Medium Static File" << endl;
		cerr << ">5 for Large Dynamic File" << endl;
		cerr << ">6 for Large Static File" << endl;
		cerr << ">7 for Example File" << endl;
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
	else if(option==7)
		myReadFile.open("small/example.txt");
	time_t now = time(NULL),end;
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
		myReadFile.open("smallWorkload_FINAL.txt");
	else if(option==3)
		myReadFile.open("mediumWorkload_FINAL.txt");
	else if(option==4)
		myReadFile.open("mediumWorkload_static_FINAL.txt");
	else if(option==5)
		myReadFile.open("largeWorkload_6000_20.txt");
	else if(option==6)
		myReadFile.open("largeWorkload_48000_40.txt");
	else if(option==7)
		myReadFile.open("small/exampleWorkload.txt");
		
	char com;
	char r[9];

	//Job job(1,2,0);
	//JobScheduler js(5);
	//js.submit_job(job);


	bool isstatic;
	int order = 0;
	int version = 0;
	bool prev_com = false;

	if(myReadFile.is_open()){
		myReadFile>>r;
		if(strcmp(r,"DYNAMIC")==0)
		{
			isstatic = false;
			uint32_t queriesnum=0;
			uint32_t updatenum=0;
			CC cc(size);
			cc.CCSearch(&graph);
			JobScheduler js(16);
			myReadFile>>com;
			while(!myReadFile.eof())
			{
				//cout<<"A"<<endl;
				stop_threads=1;
				while(com != 'F')
				{
					myReadFile>>node>>edge;
					//cout<<com<<endl;
					if(com == 'A')
					{
						queriesnum++;
						if(graph.search(node,edge))
							continue;
						if(prev_com)
							version++;
						graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge,version);
						graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node,version);
						cc.InsertNewEdge(node,edge, &updatenum, 0);
						if(updatenum > 1000)
						{
							cerr<<"rebuilding.. "<<updatenum<<" "<<queriesnum<<endl;
							cc.rebuild(&graph);
							updatenum=0;
							queriesnum=0;
						}
						prev_com=false;
					}
					else if(com == 'Q')
					{
						queriesnum++;
						Job job(&graph, NULL, NULL, &cc, node, edge, 1, order, isstatic, version);
						if(job.order >= js.get_resultsize())
							js.increase();
						js.submit_job(job);
						order++;
						prev_com=true;
					}
					/*
					if(updatenum > 500)
					{
						cerr<<"rebuilding.. "<<updatenum<<" "<<queriesnum<<endl;
						cc.rebuild(&graph);
						updatenum=0;
						queriesnum=0;
					}*/

					myReadFile>>com;
				}
				js.wait_all_jobs();
				//cout<<"B"<<endl;
				myReadFile>>com;
				//sleep(1);
				js.print_results();
				//js.reset_results();
				order=0;
				prev_com=false;
			}
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
			//grailindex.buildGrailIndex(&hypergraph, scc.getComponentCount()+1,0);
			grailindex.buildGrailIndex22(&hypergraph, scc.getComponentCount()+1,0);
			grailindex.buildGrailIndex22(&hypergraph, scc.getComponentCount()+1,1);
			//grailindex.buildGrailIndex22(&hypergraph, scc.getComponentCount()+1,2);
			//grailindex.buildGrailIndex22(&hypergraph, scc.getComponentCount()+1,3);
			cerr<<"Grail Ready"<<endl;
			myReadFile>>com;
			JobScheduler js(16);
			//cerr<<"SCC: "<<scc.findSCCid(1)<<endl;
			while(!myReadFile.eof())
			{
				stop_threads=1;
				while(com != 'F')
				{
					
					if(com == 'A')
					{
						myReadFile>>node>>edge;
						myReadFile>>com;
						continue;
					}
					myReadFile>>node>>edge;
					//cout<<com;
					//cout<<" Input: "<<node<<" "<<edge<<endl;
					Job job(&graph, &scc, &grailindex, NULL, node, edge, 1, order, isstatic,0);
					if(job.order >= js.get_resultsize())
					{
						//cout<<job.order<<" < "<<js.get_resultsize()<<endl;
						js.increase();
					}
					//cout<<"a"<<endl;
					js.submit_job(job);
					order++;
					//cout<<"Order: "<<order<<endl;
					myReadFile>>com;
				}
				js.wait_all_jobs();
				myReadFile>>com;
				//sleep(1);
				//cout<<"Order: "<<order<<endl;
				js.print_results();
				//js.reset_results();
				order=0;
			}
		}

	}
	myReadFile.close();
	end = time(NULL);
   	currtime = ctime(&end);
   	thread_flag=0;
   	cerr << "Finished at: " << currtime;
   	cerr << "After running for: "<< end-now<<"secs." <<endl;
	return 0;
}
