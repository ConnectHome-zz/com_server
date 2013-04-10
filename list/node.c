#include "node.h"

Node* node_new(void * value)
{
	Node * node = NULL;

	node = (Node*) malloc(sizeof(Node));

	//initialisation
	if(NULL != node)
	{
		 node->value = value;
		 node->next = NULL;
	}

	return node;
}

void node_add(Node * node, void * value)
{
		node->value = value;
}

//if node is just a malloc & no malloc inside
void node_clear(Node * node)
{
	if(NULL != node)
	{
		if(NULL != node->value)
			free(node->value);
	}
}

void node_del(Node * node)
{
	  if(NULL != node)
	  {
	  		node_clear(node);	
	  		free(node);
	  }
}


