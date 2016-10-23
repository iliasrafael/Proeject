#include "Graph.h"
#include "list.h	"
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

	for(int i = 0; i<graph.getOutIndex()->getSize(); i++) {
		cout<<"Node "<<i<<" :"<<endl;
		int offset = graph.getOutIndex()->getPosition(i);
		if(offset==-1)
			continue;
		uint32_t* neighbors = graph.getOutBuffer()->getListNode(offset)->getNeighbors();
		int offset2 = graph.getOutBuffer()->getListNode(offset)->getOffset();		
		for(int j = 0; j<graph.getOutBuffer()->getListNode(offset)->getLastNeighbor(); j++)
			cout<<neighbors[j]<<"  ";
		while(offset2!=0) {
			neighbors = graph.getOutBuffer()->getListNode(offset2)->getNeighbors();
			for(int j = 0; j<graph.getOutBuffer()->getListNode(offset2)->getLastNeighbor(); j++)
				cout<<neighbors[j]<<"  ";
			offset2 = graph.getOutBuffer()->getListNode(offset2)->getOffset();
		}
		
		cout<<endl;
	}
	/*
		for(int i = 0; i<graph.inc_index.getSize(); i++) {
			cout<<"Node "<<i<<" :"<<endl;
			int offset = graph.inc_index.nodes[i];
			uint32_t* neighbors = graph.inc_buffer.cells[offset].getNeighbors();
			int offset2 = graph.inc_buffer.cells[offset].getOffset();

			for(int j = 0; j<graph.inc_buffer.cells[offset].getLastNeighbor(); j++)
				cout<<neighbors[j]<<"  ";
			while(offset2!=0) {
				neighbors = graph.inc_buffer.cells[offset2].getNeighbors();
				for(int j = 0; j<graph.inc_buffer.cells[offset2].getLastNeighbor(); j++)
					cout<<neighbors[j]<<"  ";
				offset2 = graph.inc_buffer.cells[offset2].getOffset();
		}
		
		cout<<endl;
	}
	*/
	return 0;
}