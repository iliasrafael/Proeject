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
	pthread_mutex_init(&mtx,NULL);
	pthread_mutex_init(&mut,NULL);
    for(int i=0;i<size;i++)
    {   
    	cout<<"Creating worker "<<i<<endl;
        pthread_create(&workers[i], NULL, &JobScheduler::send_wrapper, this);  //dimiourgeia threads
    }

    JobList queue;

    results = (int*)malloc(sizeof(int)*size);
    for(int i=0;i<size;i++)
    { 
    	results[i] = -2;
    }
    results_size = size;
    //cond_nonempty=PTHREAD_COND_INITIALIZER;
    pthread_cond_init(&cond_nonempty, 0);
}

JobScheduler::~JobScheduler()
{
	free(workers);
}
void JobScheduler::increase()
{
	results_size *= 2;
	results=(int*)realloc(results,sizeof(int)*results_size);
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
    cerr<<"QueuSizeInsert"<<queue.get_size() <<endl;
    pthread_cond_broadcast(&cond_nonempty);
    pthread_mutex_unlock(&mtx);
}

void* JobScheduler::execute_all_jobs()
{
	Job* job;
	cout<<"execute_all_jobs"<<endl;
	int i=0;
	while(queue.get_size()==0)
	{

	}	
	while(1)
	{

		pthread_mutex_lock(&mtx);
		cerr<<"QueuSize"<<queue.get_size() <<endl;
		while(queue.get_size()<=0)
			pthread_cond_wait(&cond_nonempty,&mtx);
	    job=queue.pop();
	    queue.remove();
	    pthread_mutex_unlock(&mtx);
	    cout<<"Job: "<<job->source<<endl;
	    cout<<"wtf"<<endl;
	    results[job->order] = job->run();	    
   	}
   	pthread_exit(0);
}	
