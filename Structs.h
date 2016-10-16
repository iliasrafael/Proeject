/* domes */

typedef struct list_node {
	int neighbor[N];
	int edgeProperty[N];
	int offset;	
}list_node;

typedef struct NodeIndex {
	list_node* list_head;
}NodeIndex;

NodeIndex* createNodeIndex();
int InsertNode(NodeIndex* index, int id);
list_node* getListHead(NodeIndex* index, int id);
int destroyNodeIndex(NodeIndex* index);
