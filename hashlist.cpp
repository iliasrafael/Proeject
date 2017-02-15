#include "hashlist.h"
HashList::HashList(uint32_t size)
{
	my_size=size;
	List=(bool**)malloc(size*sizeof(bool*));
	for(uint32_t i = 0;i<size;i++)
		List[i]=NULL;
}
HashList::~HashList()
{
	for(uint32_t i = 0;i<my_size;i++)
	{
		if(List[i]!=NULL)
			free(List[i]);
	}
	free(List);
		
}
bool HashList::Insert(uint32_t start,uint32_t target)
{
	if(start < target)
	{
		if(List[start] == NULL)
		{
			List[start] = (bool*) malloc(my_size*sizeof(bool));
			for(uint32_t i=0;i<my_size;i++)
				List[start][i]=false;
		}
		if(List[start][target]==false)
		{
			List[start][target]=true;
			return true;
		}
		return false;	
	}
	else if(target < start)
	{
		if(List[target] == NULL)
		{
			List[target] = (bool*) malloc(my_size*sizeof(bool));
			for(uint32_t i=0;i<my_size;i++)
				List[target][i]=false;
		}
		if(List[target][start]==false)
		{
			List[target][start]=true;
			return true;
		}
		return false;
	}
	return false;
}
bool HashList::Search(uint32_t start,uint32_t target)
{
	if(start < target)
	{
		if(List[start]!=NULL)
			return List[start][target];
		else
			return false;
	}
	else if(target < start)
	{
		if(List[target]!=NULL)
			return List[target][start];
		else
			return false;
	}
}

void HashList::DoubleSize()
{
	my_size=my_size*2;
	List=(bool**)realloc(List,my_size*sizeof(bool*));
	assert(List!=NULL);
	for(uint32_t i=my_size/2;i<my_size;i++)
		List[i]=NULL;
}