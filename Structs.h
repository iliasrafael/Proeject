/* domes */
#define N 100

class list_node {
	int neighbor[N];
	int edgeProperty[N];
	int offset;	
};

class NodeIndex {
	list_node* list_head;
};

class Buffer{
	list_node cells[N];
};

NodeIndex* createNodeIndex();
int InsertNode(NodeIndex* index, int id);
list_node* getListHead(NodeIndex* index, int id);
int destroyNodeIndex(NodeIndex* index);
