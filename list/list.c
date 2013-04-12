#include "list.h"

/**
 * \file list/list.c
 * \brief This file is used to create nodes in a list
 * \author Morgan C.
 * \date 12/04/2013
 */

/**
 * \fn void list_add_value(List * list, void * value)
 * \brief This function create a new node with a value
 * \param[in] list the list
 * \param[in] value the value to add in a new node
 */
void list_add_value(List * list, void * value)
{
	Node * node = node_new(value);
	list_add(list,node);
}

/**
 * \fn void list_add(List * list, Node * node)
 * \brief This function add a node in the list
 * \param[in] list the list
 * \param[in] node the node to add to the list
 */
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

/**
 * \fn void list_del(List * list, Node * node)
 * \brief This function delete a list and its nodes
 * \param[in] list the list
 * \param[in] node the node to delete from the list
 */
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

/**
 * \fn List * list_new(void)
 * \brief This function create a new list
 * \return a new list or NULL if problems occur
 */
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



/**
 * \fn Node * list_get_node(List * list, int number)
 * \brief This function return a node according to is number
 * \return a node or NULL if problems occur
 */
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
