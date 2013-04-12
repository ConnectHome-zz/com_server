#include "node.h"

/**
 * \file list/node.c
 * \brief This file is used to create nodes in a list
 * \author Morgan C.
 * \date 12/04/2013
 */

/**
 * \fn Node* node_new(void * value)
 * \brief This function create a new node with a value
 * \param[in] value the value to link
 * \return a new node with a value
 */
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

/**
 * \fn void node_add(Node * node, void * value)
 * \brief This function create a new node with a value
 * \param[in] node the node to which add a value
 * \param[in] value the value to link
 */
void node_add(Node * node, void * value)
{
		node->value = value;
}

/**
 * \fn void node_clear(Node * node)
 * \brief This function free a node
 * \param[in] node the node to clear
 */
void node_clear(Node * node)
{
	//if node is just a malloc & no malloc inside
	if(NULL != node)
	{
		if(NULL != node->value)
			free(node->value);
	}
}

/**
 * \fn void node_del(Node * node)
 * \brief This function clear and free a node
 * \param[in] node the node to delete
 */
void node_del(Node * node)
{
	  if(NULL != node)
	  {
	  		node_clear(node);	
	  		free(node);
	  }
}


