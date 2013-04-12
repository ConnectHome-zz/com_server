/**
 * \file server.c
 * \brief This file is used to catch and send message from module to the webserver
 * \author Morgan C.
 * \version 0.9
 * \date 12/04/2013
 * \bug If the web server doesn't exist, this program will bug
 * \bug If there are to many data in socket, this program will bug
 */

#include "server.h"


typedef enum mode MODE;
/**
 * \enum mode
 * \deprecated change in the format
 */
enum mode 
{
	CONF, /*!< "Configuration" means we send the configuration mode */
	DATA  /*!< means it's datas to use */
};


/**
 * \fn void message(MODE mode, Module* exp,Module* dest, char* msg,void *data)
 * \brief This function is used for the redirection of messages
 * \param[in] mode deprecated, the data have changed...
 * \param[in] exp the module which send the message
 * \param[in] dest the module which will received the message
 * \param[in] msg the message
 * \param[in] data used to send anything (only used for the web address for the moment)
 * 
 */
void message(MODE mode, Module* exp,Module* dest, char* msg,void *data)
{
	char buff[BUF_SIZE];
	sprintf(buff,"%s",msg);  //add message to the buffer

	//send message to someone
	if(destinataire == NULL) //curl for the web
	{
		printf("<SERVER> CURL TO THE WEB!\n"); //How to know the web address???
		//msg_curl("http://127.0.0.1/index.php");
		//msg_curl("http://192.168.137.94:50082/API/ParseXML");
		msg_curl((char *) data); //data = web address
	}
	else
		write_module(dest->sock, buff);
}

/**
 * \fn char* messageWeb(MODE mode, Module* exp, char* msg,char* url)
 * \brief This function is used for the redirection of messages to the web server
 * \param[in] mode deprecated, the data have changed...
 * \param[in] exp the module which send the message
 * \param[in] msg the message
 * \param[in] url the url to send message to the web server
 * \return NULL
 * \bug return must be delete
 */
char* messageWeb(MODE mode, Module* exp, char* msg,char* url)
{
	char * msg_receive = do_web_request(msg,url);
	printf("(tr : %s)\n",msg_receive);
	
	message(mode,NULL,exp,msg_receive,NULL);
	return NULL;	//not use now
}

/**
 * \fn void app(const int port, char *ip_web)
 * \brief This is the application function which receive and send messages
 * \param[in] port The port where the server listen
 * \param[in] ip_web The ip address with the web server in order to send messages
 */
void app(const int port, char *ip_web)
{
   //Init the socket which is use to connect client
   SOCKET sock = init_connection_server(port);
   
   //Just a buffer to store informations from client or to send to client
   char buffer[BUF_SIZE];

   //to know the last descriptor
   int max = sock;

   // a list of modules connected
   List * modules = list_new();

   //Read descriptor
   fd_set rdfs;

   //Launch the server
   while(1)
   {
      //initialisation 
      int i = 0;
      FD_ZERO(&rdfs);	//it must be set each time to add clients into it

      //add the connection socket into the descriptor
      FD_SET(sock, &rdfs);
      
      // add socket of each modules
      Node * node = NULL;
      Module * module = NULL;
      for(i = 0; i < modules->nbElements ; i++)
      {
	node = list_get_node(modules,i);
	if(NULL != node)
	{
		module = ((Module*)(node->value));
		FD_SET(module->sock,&rdfs);
	}
      }

      //Wait for a state change
      printf("<SERVER> Wait for change...\n");
      if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
	perror("select()");
	exit(errno);
      }

      printf("<SERVER> Out from select() !\n");
      
      //if sock is in the descriptor rdfs
      //We add a module
      if(FD_ISSET(sock, &rdfs))
      {
        // Add a module
        SOCKADDR_IN csin = { 0 };
        size_t sinsize = sizeof csin;
	 
	//Creation of a socket to discuss between server & module
        int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
        if(csock == SOCKET_ERROR)
        {
		perror("accept()");
		continue;
        }
	        // Get the socket to discuss with the application
        if(read_module(csock, buffer) == -1)
        {
		printf("<DEBUG> read_client==-1\n");		   
		/* disconnected */
		continue;
        }

        // what is the new maximum descriptor?
        max = csock > max ? csock : max;

	//add the module in the descriptor
        FD_SET(csock, &rdfs);
	printf("<SERVER> New module !\n");
	//Create a new module
	Module * mod = NULL;
	mod = (Module *) malloc(sizeof(Module));
	mod->sock = csock;
        strncpy(mod->name, buffer, BUF_SIZE - 1);
	list_add_value(modules,mod);
      }
	//we have a message
      else
      {
	      printf("<SERVER> Commmunication\n");
	      // add socket of each modules
	      Node * node = NULL;
	      Module * module = NULL;
	      for(i = 0; i < modules->nbElements ; i++)
				{ 
					//research a module
					node = list_get_node(modules,i);
					if(NULL != node)
					{
						module = ((Module*)(node->value));

						//If we have the module which wants to communicate something
						if(FD_ISSET(module->sock, &rdfs))
						{
							printf("<SERVER> Reading ...\n");
							int c = read_module(module->sock, buffer);
							if(0!=c)
							{
								char buff[500];
								printf("<SERVER> Get : %s\n",buffer);
								printf("<SERVER> I give him a response !\n");

								//modify the message we received...

								char address[255];
								sprintf(address,"http://%s/API/ParseXML",ip_web);
								messageWeb(0,module,buffer,address);	
								//write_module(module->sock, buffer);
							}
							else
							{
								printf("<SERVER> disconnection %s\n",buffer);
								//Module is disconnected
								closesocket(module->sock);
								remove_module(modules, node);
							}
						}
					}
				}
			}
	 }
   clear_modules(modules);
   end_connection_server(sock);
}




/**
 * \fn int main(int argc, char *argv[])
 * \brief This program must be launch as : ./program [port] [ip_web_server]
 * \param[in] argc must be equal to 3
 * \param[in] argv[] 0=program
 *		      1=port 
 * 		      2=ip
 * \return the exit of the application
 */
int main(int argc, char *argv[])
{

   if(argc < 2)
   {
      printf("Usage : %s [port] [ip_web_server]\n", argv[0]);
      return EXIT_FAILURE;
   }
   
   app(atoi(argv[1]),argv[2]);
   return EXIT_SUCCESS;
}

