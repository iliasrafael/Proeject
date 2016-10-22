#include "Graph.h"
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
			graph.Insert(&graph.out_index,&graph.out_buffer,node,edge);
			graph.Insert(&graph.inc_index,&graph.inc_buffer,edge,node);
		}
	}
	myReadFile.close();

	for(int i = 0; i<graph.out_index.getSize(); i++) {
		cout<<"Node "<<i<<" :"<<endl;
		int offset = graph.out_index.nodes[i];
		if(offset==-1)
			continue;
		uint32_t* neighbors = graph.out_buffer.cells[offset].getNeighbors();
		int offset2 = graph.out_buffer.cells[offset].getOffset();		
		if(i==13)
			cout<<graph.out_index.nodes[1]<<"  "<<graph.out_index.last_bucket[12]<<endl;
		for(int j = 0; j<graph.out_buffer.cells[offset].getLastNeighbor(); j++)
			cout<<neighbors[j]<<"  ";
		while(offset2!=0) {
			neighbors = graph.out_buffer.cells[offset2].getNeighbors();
			for(int j = 0; j<graph.out_buffer.cells[offset2].getLastNeighbor(); j++)
				cout<<neighbors[j]<<"  ";
			offset2 = graph.out_buffer.cells[offset2].getOffset();
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