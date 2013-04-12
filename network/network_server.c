#include "network_server.h"

/**
 * \file network/network_server.c
 * \brief This file is used for the server communication
 * \author Morgan C.
 * \date 12/04/2013
 */

/**
 * \fn int init_connection_server(const int port)
 * \brief This function is used to initialize the server communication system
 * \param[in] port the port to connect
 * \return The socket between the modele and the server
 */
int init_connection_server(const int port)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = { 0 };

   if(sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   sin.sin_addr.s_addr = htonl(INADDR_ANY);
   sin.sin_port = htons(port);
   sin.sin_family = AF_INET;
   
   printf("Launch bind() ... ");
   if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR)
   {
      perror("bind()");
      exit(errno);
   }
   printf("completed !\n");


   printf("Launch listen() ... ");
   if(listen(sock, MAX_CLIENTS) == SOCKET_ERROR)
   {
      perror("listen()");
      exit(errno);
   }
   printf("completed !\n");

   return sock;
}

/**
 * \fn void end_connection_server(int sock)
 * \brief This function is used to close a communication between a module program and a server
 * \param[in] sock the socket between the module and the server
 */
void end_connection_server(int sock)
{
   closesocket(sock);
}


/**
 * \fn void write_module(SOCKET sock, const char *buffer)
 * \brief This function is used to write messages
 * \param[in] sock the socket between the module and the server
 * \param[in] buffer the buffer is the data to write to the module
 * \return number of character in the message
 */
void write_module(SOCKET sock, const char *buffer)
{
   if(send(sock, buffer, strlen(buffer), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
   else
	printf("<SERVER> sending OK!\n");
}


/**
 * \fn int read_module(SOCKET sock, char *buffer)
 * \brief This function is used to read messages
 * \param[in] sock the socket between the module and the server
 * \param[out] buffer the buffer is the reading data which comes from 			      the module
 * \return number of character in the buffer message
 */
int read_module(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      /* if recv error we disonnect the client */
      n = 0;
   }

   buffer[n] = 0;

   return n;
}


