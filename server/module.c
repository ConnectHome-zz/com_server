#include "module.h"

/**
 * \file module/module.c
 * \brief This file is used to close properly connection with a module
 * \author Morgan C.
 * \version 1.0
 * \date 12/04/2013
 */

/**
 * \fn void clear_modules(List * modules)
 * \brief This function is used to close all socket
 * \param[in] modules List of module to close
 */
void clear_modules(List * modules)
{
	int i =0;
	Node * node = NULL;
	Module * module = NULL;

	for(i = 0; i<modules->nbElements ; i++)
	{
		node = list_get_node(modules,i);
		module = (Module *) node->value;

		closesocket(module->sock);
	}
}

/**
 * \fn void remove_module(List * modules, Node * module)
 * \brief This function is used to close all socket
 * \param[in] modules List of module to delete
 * \param[in] module List of module
 */
void remove_module(List * modules, Node * module)
{
	list_del(modules,module);
}
