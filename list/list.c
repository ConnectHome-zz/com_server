#include "list.h"

void list_add_value(List * list, void * value)
{
	Node * node = node_new(value);
	list_add(list,node);
}

void list_add(List * list, Node * node)
{
	//is the list initilized ?
	if(NULL == list)
	{
		printf("Error in the List\n");
		perror("LL_add()");
	}	
	//Can we add something ?
	else if(NULL != node)
	{
		if(list->nbElements > 0)
		{
			Node * head = list->head;
			list->head = node;
			node->next = head;
			list->nbElements++;
		}
		else
		{	//add the first element
			list->head = node;
			node->next = NULL;
			list->nbElements++;
		}
	}
	else
	{
		printf("Nothing to add in the list\n");
		perror("LL_add()");
	}
}

void list_del(List * list, Node * node)
{
	Node * node_found = NULL;
	Node ** previous = NULL;

	node_found = list->head;
	previous = &(list->head);
	
	while(node_found)
	{
		if(node_found == node)
		{
			*previous = node->next;
			node_del(node);
			list->nbElements--;
			return;
		}
		previous = &((*previous)->next);
		node_found = node_found->next;
	}
}


// Return NULL if problems occur
List * list_new(void)
{
	List * list = NULL;
	list = (List*) malloc(sizeof(List));

	//initialisation
	if(NULL != list)
	{
		list->head = NULL;
		list->nbElements = 0;
	}

	return list;
}



//return the node or NULL
Node * list_get_node(List * list, int number)
{
	Node * research = NULL;
	int i;

	for(i=0; i<=number && i < list->nbElements ;i++)
	{
		if(0==i)
		{
			research = list->head;
		}
		else
		{
			research = research->next;
		}
	}

	return research;
}
