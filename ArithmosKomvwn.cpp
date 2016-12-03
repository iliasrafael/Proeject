#include "Graph.h"
#include "ArrayList.h"
#include "Stack.h"
#include "Components.h"
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
		myReadFile.open("tinyGraph.txt");
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
	int count=0;
	for(uint32_t i=0; i < graph.getIncIndex()->getSize();i++)
	{
		if(graph.getIncIndex()->getPosition(i)>=0 || graph.getOutIndex()->getPosition(i)>=0 )
			count++;
	}
	cout<<"IncSize = " << graph.getIncIndex()->getSize() << endl;
	cout<<"OutSize = " << graph.getOutIndex()->getSize() << endl;
	cout<<"NodesNumber = " << count << endl;

	return 0;
}