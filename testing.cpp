#include "Graph.h"
#include "ArrayList.h"
#include "Stack.h"
#include "Components.h"
#include "SCC.h"
#include <fstream>
#include <iostream>
using namespace std;


int main(void)
{

	Graph graph_test;
	ArrayList lista;
	if(graph_test.getOutIndex()->getPosition(1)==-1)//arxikopoihsh
		cout<<"Initialization ok "<<endl;
	else
		cerr<<"Wrong initialization value"<<endl;
	if(graph_test.getOutIndex()->getLastBucket(1)==0)//arxikopoihsh
		cout<<"Initialization on last bucket ok "<<endl;
	else
		cerr<<"Wrong initialization last bucket value"<<endl;
	if(!graph_test.Insert(graph_test.getOutIndex(),graph_test.getOutBuffer(),1,0))
		cerr<<"Wrong on Insert"<<endl;
	else
		cout<<"Insert successfull"<<endl;
	graph_test.Insert(graph_test.getOutIndex(),graph_test.getOutBuffer(),2,0);
	if(graph_test.getOutIndex()->getPosition(2)==1)
		cout<<"Entry ok"<<endl;
	else
		cerr<<"Error on entry"<<endl;
	lista.Insert(2);
	lista.Insert(3);
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

	Stack stack_test;
	if(!stack_test.empty())
		cerr<<"Wrong empty stack"<<endl;
	else
		cout<<"Empty stack successfull"<<endl;
	stack_test.add(1);
	stack_test.add(2);
	stack_test.add(3);
	if(stack_test.empty())
		cerr<<"Wrong empty stack"<<endl;
	else
		cout<<"Empty stack successfull"<<endl;
	if(stack_test.get_size() != 4)
		cerr<<"Wrong on Size of stack "<<stack_test.get_size()<<endl;
	else
		cout<<"Size of stack successfull"<<endl;
	if(stack_test.pop() != 3)
		cerr<<"Wrong pop stack"<<endl;
	else
		cout<<"Pop stack successfull"<<endl;
	if(stack_test.pop() != 2)
		cerr<<"Wrong pop stack"<<endl;
	else
		cout<<"Pop stack successfull"<<endl;

	return 0;
}