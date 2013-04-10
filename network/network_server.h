#ifndef NETWORK_SERVER_H
#define NETWORK_SERVER_H

#include "network.h"

int init_connection_server(const int port);
void end_connection_server(int sock);

int read_module(SOCKET sock, char *buffer);
void write_module(SOCKET sock, const char *buffer);
#endif // NETWORK_SERVER
