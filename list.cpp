#include "list.h"
#include <cstring>
#include <iostream>
using namespace std;


Node::Node(int id) : next(NULL),id(id)
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
	//if(find(id))
		//return;
	if(head==NULL)
	{
		back = new Node(id);
		head=back;
	}
	else
	{
		back->next=new Node(id);
		back=back->next;
	}
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
	if(head==NULL)
		back=NULL; 
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