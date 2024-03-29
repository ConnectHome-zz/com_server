#ifndef MODULE_H
#define MODULE_H

#include "../network/network_server.h"
#include "../list/list.h"

typedef struct
{
  SOCKET sock;
  char name[BUF_SIZE];
}Module;

void clear_modules(List * modules);
void remove_module(List * modules, Node * module);

#endif
