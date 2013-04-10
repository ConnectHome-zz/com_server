#ifndef NODE_H
#define NODE_H

#include <stdlib.h>


typedef struct Node Node;


struct Node
{
	void * value;
	Node * next;
};

//List of function:

Node * node_new(void * value);								//create a new node with a value (which can be NULL)
void node_add(Node * node, void * value );		//add a value to a node
void node_clear(Node * node);									//clear the value
void node_del(Node * node);										//delete the node (malloc)


/*
 * some adds :
 * void node_clear_function(Node * node, void* function);	//use a function to clear the node
 */



#endif //NODE_H
