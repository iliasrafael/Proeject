#include "Structs.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(void)
{
	Graph graph;

	ifstream myReadFile;
	myReadFile.open("tinyGraph.txt");
	unsigned int node;
	unsigned int edge;
	if (myReadFile.is_open()) {
		while (!myReadFile.eof()) {
			myReadFile >> node >>edge;
			if(myReadFile.good())
				cout<<node<<" "<<edge<<endl;
			else break;
			graph.Insert(node,edge);
		}
	}
	myReadFile.close();

	for(int i = 0; i<graph.out_index.getSize(); i++) {
		cout<<"Node "<<i<<" :"<<endl;
		int offset = graph.out_index.nodes[i];
		uint32_t* neighbors = graph.out_buffer.cells[offset].getNeighbors();
		int offset2 = graph.out_buffer.cells[offset].getOffset();

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

	return 0;
}