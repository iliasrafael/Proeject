#include "JobScheduler.h"
#include <iostream>

using namespace std;

JobScheduler::JobScheduler(uint32_t size_)
{
	size=size_;
	workers = (pthread_t*)malloc(sizeof(pthread_t)*size);
	assert(workers!=NULL);
	//mut = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t)*size);
    //for(int i=0;i<size;i++)
        //pthread_mutex_init(&mut[i],0);	//attribute?
	//mtx = (pthread_mutex_t)malloc(sizeof(pthread_mutex_t));

	//pthread_mutexattr_t Attr;
	//pthread_mutexattr_init(&Attr);
	//pthread_mutexattr_settype(&Attr, PTHREAD_MUTEX_RECURSIVE);

	pthread_mutex_init(&mtx, NULL);
	//pthread_mutex_init(&mut,NULL);
    for(int i=0;i<size;i++)
    {   
    	//cout<<"Creating worker "<<i<<endl;
        pthread_create(&workers[i], NULL, &JobScheduler::send_wrapper, this);  //dimiourgeia threads
    }

    results = (int*)malloc(sizeof(int)*64);
    for(int i=0;i<64;i++)
    { 
    	results[i] = -2;
    }
    results_size = 64;
    //cond_nonempty=PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&cond_nonempty, 0);
    pthread_cond_init(&cond_empty, 0);
}

JobScheduler::~JobScheduler()
{
	free(workers);
	free(results);
	//pthread_mutex_destroy(&mtx);
}
void JobScheduler::increase()
{
	uint32_t s = results_size;
	results_size *= 2;
	results=(int*)realloc(results,sizeof(int)*results_size);
	for(int i=s;i<results_size;i++)
    { 
    	results[i] = -2;
    }
	assert(results!=NULL);
}


uint32_t JobScheduler::get_resultsize()
{
	return results_size;
}

int JobScheduler::get_results(uint32_t i){
	return results[i];
}

void JobScheduler::reset_results()
{
	for(int i=0;i<results_size;i++)
    { 
    	results[i] = -2;
    }
}

void JobScheduler::submit_job(Job job)
{
	pthread_mutex_lock(&mtx); 
    queue.Insert(job);
    //cerr<<"QueuSizeInsert"<<queue.get_size() <<endl;
    pthread_cond_broadcast(&cond_nonempty);
    pthread_mutex_unlock(&mtx);
}

void* JobScheduler::execute_all_jobs()
{
	Job* job;
	//cout<<"execute_all_jobs"<<endl;
	while(1)
	{
		while(queue.get_size()==0){}
		pthread_mutex_lock(&mtx);
		//cerr<<"QueuSize"<<queue.get_size() <<endl;
		while(queue.get_size()<=0)
			pthread_cond_wait(&cond_nonempty,&mtx);
	    job=queue.pop();
	    queue.remove();
	    if(queue.empty())
	    	pthread_cond_broadcast(&cond_empty);
	    pthread_mutex_unlock(&mtx);
	    //cout<<"Job: "<<job->source<<endl;
	    //cout<<"wtf"<<endl;
	    //cout<<"->"<<job->order<<endl;
	    //cout<<"-->"<<results_size<<endl;
	    results[job->order] = job->run();	    
   	}
   	pthread_exit(0);
}	

void JobScheduler::print_results()
{
	pthread_mutex_lock(&mtx);
	while(queue.get_size()>0)
		pthread_cond_wait(&cond_empty,&mtx);
	for(int i=0; i< results_size; i++)
	{
		//cout<<"i="<<i<<" size="<<results_size<<endl;
		if(results[i]==-2)
			break;
		cout<<results[i]<<endl;
	}
	pthread_mutex_unlock(&mtx);
}