#include "ArrayList.h"
#include <iostream>
#include <cstdlib>
using namespace std;
#define ALSIZE 4000
ArrayList::ArrayList()
{
	array=(uint32_t *)malloc(sizeof(uint32_t)*ALSIZE);
	if(array==NULL)
		cout<<ALSIZE<<endl;
	head=0;
	back=0;
	elements=0;
	size=ALSIZE;
}

ArrayList::~ArrayList()
{
	free(array);
}
void ArrayList::Insert(uint32_t id)
{
	if(back==size)
	{
		DoubleSize();
	}
	array[back]=id;
	back++;
	elements++;
}

uint32_t ArrayList::remove()
{
	uint32_t id=array[head];
	head++;
	elements--;
	return id;
}
bool ArrayList::empty()
{
	return head==back;
}
uint32_t ArrayList::get_size()
{
	return back-head;
}

void ArrayList::DoubleSize()
{
	if(size > 50000)
	{
		size=(uint32_t)size*3/2;
		array=(uint32_t*)realloc(array,sizeof(uint32_t)*size);
		assert(array!=NULL);
		return;
	}

	size=size*2;
	array=(uint32_t*)realloc(array,sizeof(uint32_t)*size);
	assert(array!=NULL);
}

void ArrayList::Set()
{
	head=0;
	back=0;
	elements=0;
}