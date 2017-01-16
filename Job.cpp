#include "Job.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "Graph.h"

using namespace std;

Job::Job(Graph* graph_, SCC* scc_, GrailIndex* grailindex_, CC* cc_, uint32_t source_ , uint32_t target_ ,bool k, int ord, bool st)
{
	source = source_;
	target = target_;
	kind = k;
	isstatic = st;
	order = ord;

	graph = graph_;
	scc = scc_;
	grailindex = grailindex_;
	cc = cc_;
	//cout<<"Create job "<<source<<endl;
}

int Job::run()
{
	//cout<<"Runnig ..."<<endl;
	if(!isstatic)
	{
		int check = cc->check(source,target);
		if( check >= 0)
			return graph->BBFS(source,target,NULL,false,NULL);
		else
			return -1;		
	}
	else
	{
		
		uint32_t a = scc->findSCCid(source);
		uint32_t b = scc->findSCCid(target);
		if(grailindex->isReachableGrailIndex(source,target,scc)==1)
			//cout<<graph->BBFS(source,target,&scc,false,&grailindex)<<endl;
			return graph->BBFS(source,target,scc,false,grailindex);
		else if(grailindex->isReachableGrailIndex(source,target,scc)==2)
			//cout<<graph->BBFS(source,target,&scc,true,NULL)<<endl;
			return graph->BBFS(source,target,scc,true,NULL);
		else 
			//cout<<"-1"<<endl;
			return -1;

	}
}