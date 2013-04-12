#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "module.h"

/**
 * \file module/module.c
 * \brief This file is an example of a module
 * \author Morgan C.
 * \version 1.0
 * \date 12/04/2013
 */

/**
 * \fn void app(const char *address, const char *name, const int port)
 * \brief This is the application function
 * \param[in] address the address of the server
 * \param[in] name the name of this module
 * \param[in] port the port where the server listen
 */
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


/**
 * \fn int main(int argc, char *argv[])
 * \brief This program must be launch as : ./program [port] [ip_web_server]
 * \param[in] argc must be equal to 3
 * \param[in] argv[] 0=program
 *		      1=address 
 * 		      2=name
 * 		      3=port
 * \return the exit of the application
 */
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
