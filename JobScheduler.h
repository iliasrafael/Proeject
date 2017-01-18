#ifndef __JobScheduler__ 
#define __JobScheduler__

#include <pthread.h>
#include <stdlib.h>
#include "JobList.h"
#include "Job.h"

class JobScheduler{

	uint32_t size;
	pthread_mutex_t mtx;
	pthread_mutex_t mut;
	pthread_mutex_t mylock;
	pthread_cond_t cond_nonempty;
	pthread_cond_t non_done;
	pthread_t * workers; 
	JobList queue;
	int* results;
	int counter;
	uint32_t results_size;

public:
	JobScheduler(uint32_t size);
	~JobScheduler();

	void submit_job(Job job);
	void* execute_all_jobs();

	static void* send_wrapper(void* object)
	{
		return ((JobScheduler*)object)->execute_all_jobs();
	    //static_cast<JobScheduler*>(object)->execute_all_jobs();
	    //return 0;
	}

	uint32_t get_resultsize();
	int get_results(uint32_t i);
	void reset_results();
	void print_results();
	void increase();
};

#endif