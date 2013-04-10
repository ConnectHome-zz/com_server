#include "network_server.h"

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

void end_connection_server(int sock)
{
   closesocket(sock);
}



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


//Cette fonction me semble pas génial, il faudrait renvoyer -1 et non 0 ?
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


