#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
class HashList{

	bool ** List;
	uint32_t my_size;

public:
	HashList(uint32_t size);
	~HashList();
	bool Insert(uint32_t start,uint32_t target);
	bool Search(uint32_t start,uint32_t target);
	void DoubleSize();
};

