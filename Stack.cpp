#include <iostream>
#include <cstdlib>
#include "Stack.h"

using namespace std;

Stack::Stack(uint32_t size_)
{
	head = -1;
	pinakas = (uint32_t*)malloc(sizeof(uint32_t)*size);
	size = size_;
}

Stack::~Stack()
{
	free(pinakas);
}

bool Stack::empty()
{
	return (head == -1);
}

uint32_t Stack::pop() 
{
	uint32_t stoixeio = pinakas[head];
	head--;
	return stoixeio;
}

void Stack::add(uint32_t stoixeio)
{
	if(head==size)
	{
		doubleSize();
	}

	head++;
	pinakas[head] = stoixeio;
}

uint32_t Stack::get_size()
{
	return size;
}

void Stack::doubleSize()
{
	size=size*2;
	pinakas = (uint32_t*)realloc(pinakas, sizeof(uint32_t)*size);
	assert(pinakas!=NULL);
}