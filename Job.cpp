#include "Job.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "Graph.h"

using namespace std;

Job::Job(Graph* graph_, SCC* scc_, GrailIndex* grailindex_, CC* cc_, uint32_t source_ , uint32_t target_ ,bool k, int ord, bool st, int vers)
{
	source = source_;
	target = target_;
	kind = k;
	isstatic = st;
	order = ord;
	version = vers;

	graph = graph_;
	scc = scc_;
	grailindex = grailindex_;
	cc = cc_;
	//cout<<"Create job "<<source<<endl;
}
Job::Job()
{
	source = 0;
	target = 0;
	kind = false;
	isstatic = false;
	order = -1;
	version = -1;

	graph = NULL;
	scc = NULL;
	grailindex = NULL;
	cc = NULL;
}
Job::Job(const Job& job)
{
	source = job.source;
	target = job.target;
	kind = job.kind;
	isstatic = job.isstatic;
	order = job.order;
	version = job.version;

	graph = job.graph;
	scc = job.scc;
	grailindex = job.grailindex;
	cc = job.cc;
}

void Job::setJob(Job job)
{
	source = job.source;
	target = job.target;
	kind = job.kind;
	isstatic = job.isstatic;
	order = job.order;
	version = job.version;

	graph = job.graph;
	scc = job.scc;
	grailindex = job.grailindex;
	cc = job.cc;
}

int Job::getOrder()
{
	return order;
}

int Job::run()
{
	//cout<<"Runnig ..."<<endl;
	if(!isstatic)
	{
		int check = cc->check(source,target);
		if( check >= 0)
			return graph->BBFS(source,target,NULL,false,NULL,version);
		else
			return -1;		
	}
	else
	{
		
		//uint32_t a = scc->findSCCid(source);
		//uint32_t b = scc->findSCCid(target);
		//cerr<<"--> SCC: "<<scc->findSCCid(1)<<endl;
		if(grailindex->isReachableGrailIndex(source,target,scc)==1)
		{
			//cout<<graph->BBFS(source,target,&scc,false,&grailindex)<<endl;
			return graph->BBFS(source,target,scc,false,grailindex,0);
		}
		else if(grailindex->isReachableGrailIndex(source,target,scc)==2)
		{
			//cout<<graph->BBFS(source,target,&scc,true,NULL)<<endl;
			return graph->BBFS(source,target,scc,true,NULL,0);
		}
		else
		{
			//cout<<"-1"<<endl;
			return -1;
		}
		//return graph->BBFS(source,target,NULL,false,NULL,0);
	}
	//cerr << "RunResult = "<< my_resultt << endl;
}
