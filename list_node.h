#include <iostream>
#include <cstdlib>
#include <stdint.h>
#include <assert.h>
using namespace std;
#define N 10
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define OK_SUCCESS 1
///////////////////////////////////////////////////////////////////////////////
/* LIST NODE*/
///////////////////////////////////////////////////////////////////////////////
class list_node {   
	uint32_t neighbor[N];                 
	uint32_t edgeProperty[N];            
	int offset;
	uint32_t last_neighbor;                       
public:
	bool Insert(uint32_t id);
	uint32_t* getNeighbors();
	uint32_t* getProperties();
	int getOffset();
	uint32_t getLastOffset();
	uint32_t getLastNeighbor();	 
	void setOffset(int off);
	void setLastOffset(uint32_t off);
	void setLastNeighbor(uint32_t neighbor);         
};			