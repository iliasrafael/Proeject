#include <stdint.h>
#include "SCC.h"

class GrailIndex
{	
	uint32_t* id;
	uint32_t* rank;
	uint32_t* min_rank;
public:
	GrailIndex(uint32_t size_);
	~GrailIndex();
	void buildGrailIndex(SCC* scc);
	uint32_t isReachableGrailIndex(uint32_t source, uint32_t target);
	void setid(uint32_t id, uint32_t i);
	uint32_t getid(uint32_t i);
	void setrank(uint32_t r, uint32_t i);
	uint32_t getrank(uint32_t i);
	void setminrank(uint32_t r, uint32_t i);
	uint32_t getminrank(uint32_t i);
};