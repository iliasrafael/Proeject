#include "ArrayList.h"
#include <iostream>
#include <cstdlib>
using namespace std;
ArrayList::ArrayList(int size)
{
	array=(int *)malloc(sizeof(int)*size);
	if(array==NULL)
	{
		cout<<size<<endl;
		for(int i=0;;i++) i++;
	}
	head=0;
	back=0;
}

ArrayList::~ArrayList()
{
	free(array);
}
void ArrayList::Insert(int id)
{
	array[back]=id;
	back++;
}

int ArrayList::remove()
{
	int id=array[head];
	head++;
	return id;
}
bool ArrayList::empty()
{
	return head==back;
}
int ArrayList::get_size()
{
	return back-head;
}