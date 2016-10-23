#include "list.h"
#include <cstring>
#include <iostream>
using namespace std;


Node::Node(Node* next, int id) : next(next),id(id)
{

}

List::List() : size(0), head(NULL)
{

}
List::~List()
{
	cout<<"ola telos"<<endl;
}

void List::push(int id)
{
	size++;
	back = new Node(back , id);
}

bool List::find(int data)
{
	Node* temp = head;
	while (temp)
	{
		if (temp->id==data) return true;
		temp = temp->next;
	}
	return false;
}

int List::get_size()
{
	return size;
}
int List::remove()
{
	Node* node=head;
	size--;
	head=node->next; 
	int res = node->id;
	delete node;
	return res;
}
int List::empty()
{
	return head == NULL;
}

void List::print()
{
	Node * temp=head;
	while (temp!=NULL)
	{
		cout<<temp->id<<endl;
		temp=temp->next;
	}
}