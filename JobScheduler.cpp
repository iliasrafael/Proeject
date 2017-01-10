#include "JobScheduler.h"
#include <iostream>

JobScheduler::JobScheduler(uint32_t size_)
{
	size=size_;
	workers=malloc(sizeof(pthread_t)*size);
	assert(workers!=NULL);
	mut=malloc(sizeof(pthread_mutex_t)*size);
    for(i=0;i<size;i++)
        pthread_mutex_init(&mut[i],0);	//attribute?
    for(i=0;i<size;i++)
    {   
        pthread_create(&threadA[i], NULL, execute, NULL);  //dimiourgeia threads
    }
}

void JobScheduler::submit_job(Job * job)
{
	pthread_mutex_lock (& mtx); 
    list.insert(job);
    pthread_cond_broadcast(&cond_nonempty);
    pthread_mutex_unlock(& mtx);
}

void JobScheduler::execute_all_jobs()
{
	while(1)
	{
		pthread_mutex_lock (& mtx );
	    while (list.size <= 0) 
	    {
	        pthread_cond_wait (&cond_nonempty ,&mtx );//perimenei mexri na ginei broadcoast oti iparxei stoixeio stin oura
	    }
	    job=list.remove();
	    job.do_task();
	    pthread_mutex_unlock (& mtx );
   	}
}	