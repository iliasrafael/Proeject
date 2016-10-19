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
    }
}
myReadFile.close();
	return 0;
}