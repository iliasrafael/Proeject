#include "Graph.h"
#include "list.h"
#include <fstream>
#include <iostream>
using namespace std;

int main(void)
{

	Graph graph_test;
	List lista;
	if(!graph_test.Insert(graph_test.getOutIndex(),graph_test.getOutBuffer(),1,0))
		cerr<<"Wrong on Insert"<<endl;
	else
		cout<<"Insert successfull"<<endl;
	lista.push(2);
	lista.push(3);
	if(lista.get_size()!=2)
		cerr<<"Wrong on Size of List"<<endl;
	else
		cout<<"Size of list successfull"<<endl;
	if(lista.remove()!=2)
		cerr<<"Wrong on List"<<endl;
	else
		cout<<"Remove successfull"<<endl;
	if(graph_test.getOutIndex()->getPosition(1)==0)
		cout<<"Positon ok"<<endl;
	else 
		cerr<<"Wrong position"<<endl;

	getchar();




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
				graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),node,edge);
				graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),edge,node);
			}
			if(com=='Q')
				cout<<graph.BBFS(node,edge)<<endl;
		}
	}
	/*
	for(int i = 0; i<graph.getOutIndex()->getSize(); i++) {
		cout<<"Node "<<i<<" :"<<endl;
		int offset = graph.getOutIndex()->getPosition(i);
		if(offset==-1)
			continue;
		uint32_t* neighbors = graph.getOutBuffer()->getListNode(offset)->getNeighbors();
		int offset2 = graph.getOutBuffer()->getListNode(offset)->getOffset();		
		for(int j = 0; j<graph.getOutBuffer()->getListNode(offset)->getLastNeighbor(); j++)
			cout<<neighbors[j]<<"  ";
		while(offset2!=-1) {
			neighbors = graph.getOutBuffer()->getListNode(offset2)->getNeighbors();
			for(int j = 0; j<graph.getOutBuffer()->getListNode(offset2)->getLastNeighbor(); j++)
				cout<<neighbors[j]<<"  ";
			offset2 = graph.getOutBuffer()->getListNode(offset2)->getOffset();
		}
		
		cout<<endl;
	}*/
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