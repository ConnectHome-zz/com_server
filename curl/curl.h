#ifndef MSG_CURL_H
#define MSG_CURL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
 
//example : msg= "http://127.0.0.1/index.php?index=coucou
int msg_curl(char* msg);

size_t static write_callback_func(	void *buffer,
					size_t size,
					size_t nmemb,
					void *userp);

char *do_web_request(char *msg,char *url);

#endif // MSG_CURL_H
