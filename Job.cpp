#include "Job.h"
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "Graph.h"

using namespace std;

Job::Job(Graph* graph_, SCC* scc_, GrailIndex* grailindex_, uint32_t source_ , uint32_t target_ ,bool k, int ord, bool st)
{
	source = source_;
	target = target_;
	kind = k;
	isstatic = st;
	order = ord;

	graph = graph_;
	scc = scc_;
	grailindex = grailindex_;
}

int Job::run()
{
	cout<<"Runnig ..."<<endl;
	if(!isstatic)
	{
		/*
		uint32_t queriesnum=0;
		uint32_t updatenum=0;
		CC cc(size);
		cc.CCSearch(&graph);

		if(!kind)
		{
			queriesnum++;
			if(graph.search(source,target))
				continue;
			graph.Insert(graph.getOutIndex(),graph.getOutBuffer(),source,target);
			graph.Insert(graph.getIncIndex(),graph.getIncBuffer(),target,source);
			cc.InsertNewEdge(source,target, &updatenum);
		}
		if(kind)
		{	 
			queriesnum++;
			check = cc.check(source,target);
			if( check >= 0)
				//cout<<graph.BBFS(source,target,NULL,false,NULL)<<endl;
				return graph.BBFS(source,target,NULL,false,NULL);
			else
				//cout<<"-1"<<endl;
				return -1;		
		}
		if(updatenum > 500)
		{
			cerr<<"rebuilding.. "<<updatenum<<" "<<queriesnum<<endl;
			cc.rebuild(&graph);
			updatenum=0;
			queriesnum=0;
		}
		*/
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