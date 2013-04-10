#include "module.h"

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


void remove_module(List * modules, Node * module)
{
	list_del(modules,module);
}
