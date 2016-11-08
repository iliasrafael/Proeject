#include "Graph.h"
#include "list.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(void)
{

	Graph graph;
	ifstream myReadFile;
	myReadFile.open("smallGraph.txt");
	unsigned int node;
	unsigned int edge;
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> node >>edge;
			if(!myReadFile.good())
				break;
			graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge);
			graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node);
		}
	}
	myReadFile.close();
	myReadFile.open("smallWorkload_FINAL.txt");
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
	return 0;
}