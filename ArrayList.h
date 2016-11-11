#ifndef __ArrayList__	
#define __ArrayList__
#include <stdint.h>
#include <assert.h>
class ArrayList{

	uint32_t *array;
	uint32_t head;
	uint32_t back;
	uint32_t elements;
	uint32_t size;
public:

ArrayList();
~ArrayList();
void Insert(uint32_t id);
bool empty();
uint32_t remove();
uint32_t get_size();
void DoubleSize();
void Set();
};

#endif