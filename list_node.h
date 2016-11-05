#include <iostream>
#include <cstdlib>
#include <stdint.h>
using namespace std;
#define N 100
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
	unsigned int last_neighbor;                       
public:
	bool Insert(uint32_t id);
	uint32_t* getNeighbors();
	uint32_t* getProperties();
	int getOffset();
	unsigned int getLastOffset();
	unsigned int getLastNeighbor();	 
	void setOffset(int off);
	void setLastOffset(unsigned int off);
	void setLastNeighbor(unsigned int neighbor);         
};			