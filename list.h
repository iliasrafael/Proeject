#ifndef __LIST__	
#define __LIST__

class Node
{
	public:
		Node* next;
		int  id;
		Node(int id);
};

class List
{
	Node* back;
	Node* head;	
public:
	int size;
	List();
	~List();
	void push(int id);
	int remove();
	bool find(int id);
	int empty(); 
	int get_size();
	void print();
};
#endif
