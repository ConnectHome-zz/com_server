#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "module.h"

void app(const char *address, const char *name, const int port)
{
	SOCKET sock = init_connection_module(address,port);
	char buffer[BUF_SIZE];

	//use of a descriptor in order to use non-blocking sockets
	fd_set rdfs;

	// send the Applcation's name
	write_server(sock, name);


	//infinite loop = program
	while(1)
	{
		// reset the descriptor
		FD_ZERO(&rdfs);
 		FD_SET(STDIN_FILENO, &rdfs);
	  	// add the socket in the descriptor
 		FD_SET(sock, &rdfs);

 		// wait for state change in the descriptor
		if(select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
		{
			perror("select()");
			exit(errno);
		}

      
		if(FD_ISSET(STDIN_FILENO, &rdfs))
		{
			fgets(buffer,BUF_SIZE -1, stdin);
			char *p = NULL;
			p = strstr(buffer,"\n");
			if(p != NULL)
			{
				*p=0;
			}
			else
			{
				buffer[BUF_SIZE -1] = 0;
			}

			write_server(sock,buffer);
		}
		else
		{
			// look if something is coming
			if(FD_ISSET(sock, &rdfs))
			{
				int n = read_server(sock, buffer);
				// server down
				if(n == 0)
				{
					printf("Server disconnected !\n");
					break;
				}
				puts(buffer);
			}
			else
			{
				puts("no\n");
			}
		}

	}
   end_connection_module(sock);
}

int main(int argc, char **argv)
{
   if(argc < 3)
   {
      printf("Usage : %s [address] [name] [port]\n", argv[0]);
      return EXIT_FAILURE;
   }

   app(argv[1], argv[2], atoi(argv[3]));

   return EXIT_SUCCESS;
}
