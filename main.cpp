#include "Graph.h"
#include "list.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(void)
{	
	int option=0;
	while(option<1 || option>3)
	{
		cerr << ">Please choose Input File  :)"<<endl;
		cerr << ">1 for Tiny File" << endl;
		cerr << ">2 for Small File" << endl;
		cerr << ">3 for Medium File" << endl;
		cin >> option;	
	}

	ifstream myReadFile;

	if(option==1)
		myReadFile.open("tinyGraph.txt");
	else if(option==2)
		myReadFile.open("smallGraph.txt");
	else if(option==3)
		myReadFile.open("mediumGraph.txt");
	

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
	if(option==1)
		myReadFile.open("tinyWorkload_FINAL.txt");
	else if(option==2)
		myReadFile.open("smallWorkload_FINAL.txt");
	else if(option==3)
		myReadFile.open("mediumWorkload_FINAL.txt");
	char com;
	int visited_size;
	if(graph.getOutIndex()->getSize()>graph.getIncIndex()->getSize())
		visited_size=graph.getOutIndex()->getSize();
	else
		visited_size=graph.getIncIndex()->getSize();
	int *visited=(int*)malloc(sizeof(int)*(visited_size));
	for(int i=0;i<visited_size;i++)
		visited[i]= -1;
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
			{
				cout<<graph.BBFS(node,edge,visited)<<endl;
				for(int i=0;i<visited_size;i++)
					visited[i]= -1;
			}
		}
	}
	myReadFile.close();
	return 0;
}
