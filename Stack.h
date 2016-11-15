#ifndef __STACK__ 
#define __STACK__

#include <stdint.h>
#include <assert.h>

class Stack
{
	uint32_t head;
	uint32_t size;
	uint32_t* pinakas;
public:
	Stack(uint32_t size);
	~Stack();
	bool empty();
	uint32_t pop();
	void add(uint32_t stoixeio);
	uint32_t get_size();
	void doubleSize();
};

#endif