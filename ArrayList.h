#ifndef __ArrayList__	
#define __ArrayList__
class ArrayList{

	int *array;
	int head;
	int back;
public:

ArrayList(int );
~ArrayList();
void Insert(int id);
bool empty();
int remove();
int get_size();
};

#endif