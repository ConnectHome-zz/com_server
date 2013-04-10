#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include "node.h"

typedef struct List List;

struct List
{
	Node * head;
	int nbElements;
};

List * list_new(void);					// Create a new List without Node
void list_add(List * list, Node * node);		// add the node at the beginning of the list
void list_del(List * list, Node * node); 		// delete the node from the list
void list_add_value(List * list, void * value);		// Add automatically a new Node with the value
Node* list_get_node(List * list, int number);

#endif //LIST_H


