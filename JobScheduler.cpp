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
	pthread_mutex_init(&mtx,0);
	pthread_mutex_init(&mut,0);
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

    pthread_cond_init(&cond_nonempty, 0);
}

JobScheduler::~JobScheduler()
{
	free(workers);
}

void JobScheduler::submit_job(Job job)
{
	pthread_mutex_lock(&mut); 
    queue.Insert(job);
    pthread_cond_broadcast(&cond_nonempty);
    pthread_mutex_unlock(&mut);
}



void* JobScheduler::execute_all_jobs()
{
	Job* job;
	cout<<"execute_all_jobs"<<endl;
	while(1)
	{
		pthread_mutex_lock(&mtx);
	    while (queue.get_size() <= 0) 
	    {
	        pthread_cond_wait(&cond_nonempty ,&mut);//perimenei mexri na ginei broadcoast oti iparxei stoixeio stin oura
	    }
	    //cout<<"eftasa"<<endl;
	    job=queue.pop();
	    queue.remove();
	    cout<<"Job: "<<job->source<<endl;
	    pthread_cond_broadcast(&cond_nonempty);
	    pthread_mutex_unlock(&mtx );

	    if(job->order >= results_size)
	    {
	    	results_size *= 2;
	    	results=(int*)realloc(results,sizeof(int)*results_size);
			assert(results!=NULL);
	    }
	    results[job->order] = job->run();
   	}
   	pthread_exit(0);
}	
