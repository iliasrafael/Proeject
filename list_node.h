#include <iostream>
#include <cstdlib>
#include <stdint.h>
using namespace std;
#define N 5
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////
#define OK_SUCCESS 1
///////////////////////////////////////////////////////////////////////////////
/* LIST NODE*/
///////////////////////////////////////////////////////////////////////////////
class list_node {                          
public:
	uint32_t neighbor[N];                 
	uint32_t edgeProperty[N];            
	unsigned int offset;
	unsigned int last_neighbor;
	bool Insert(uint32_t id);
	uint32_t* getNeighbors();
	uint32_t* getProperties();
	unsigned int getOffset();
	unsigned int getLastOffset();
	unsigned int getLastNeighbor();	 
	void setOffset(unsigned int off);
	void setLastOffset(unsigned int off);
	void setLastNeighbor(unsigned int neighbor);         
};			