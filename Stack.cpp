#include <iostream>
#include <cstdlib>
#include "Stack.h"

#define STACK_SIZE 100
using namespace std;

Stack::Stack()
{
	head = 0;
	pinakas = (uint32_t*)malloc(sizeof(uint32_t)*STACK_SIZE);
	assert(pinakas!=NULL);
	size = STACK_SIZE;
}

Stack::~Stack()
{
	free(pinakas);
}

bool Stack::empty()
{
	return (head == 0);
}

uint32_t Stack::pop() 
{
	uint32_t stoixeio = pinakas[--head];
	return stoixeio;
}

void Stack::add(uint32_t stoixeio)
{
	if(head==size)
	{
		doubleSize();
	}
	pinakas[head++] = stoixeio;
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