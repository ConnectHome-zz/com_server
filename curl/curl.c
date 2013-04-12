/**
 * \file curl/curl.c
 * \brief This file is used to do web resquest with curl
 * \author Morgan C.
 * \date 12/04/2013
 */

#include "curl.h"

/**
 * \fn char *do_web_request(char *msg,char *url)
 * \brief This function do a web request with a POST method
 * \param[in] msg the message to transfert
 * \param[in] url the url of the web server
 * \return the response from the web server
 */
char *do_web_request(char *msg,char *url)
{
	/* keeps the handle to the curl object */
	CURL *curl_handle = NULL;
	/* to keep the response */
	char *msg_;
	char *response = NULL;
	
	//printf("URL : %s </>\n");
	/* initializing curl and setting the url */
	curl_handle = curl_easy_init();
	curl_easy_setopt(curl_handle, CURLOPT_URL, url);
	curl_easy_setopt(curl_handle, CURLOPT_POST, 1);

	/* follow locations specified by the response header */
	curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1);

	/* setting a callback function to return the data */
	//printf("<server go>\n");
	curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_callback_func);

	msg_ = (char*) malloc((strlen(msg)+5) * sizeof(char));
	sprintf(msg_,"xml=%s",msg);
	curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, msg_);

	/* passing the pointer to the response as the callback parameter */
	curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &response);

	/* perform the request */
	curl_easy_perform(curl_handle);

	/* cleaning all curl stuff */
	curl_easy_cleanup(curl_handle);
	free(msg_);
	//printf("<server>%s<//>",response);

	return response;
}



/**
 * \fn size_t static write_callback_func(void *buffer,size_t size,size_t nmemb,void *userp)
 * \brief the function to invoke as the data received
 * \param[in] buffer 
 * \param[in] size 
 * \param[in] nmemb 
 * \param[out] userp
 * \return 
 */
size_t static write_callback_func(	void *buffer,
					size_t size,
					size_t nmemb,
					void *userp)
{
	char **response_ptr =  (char**)userp;
	if(*response_ptr != NULL)
	{
		free(*response_ptr);
	}
	*response_ptr = (char *) malloc(size*nmemb); //sizeof(char));
	/* assuming the response is a string */
	*response_ptr = strndup(buffer, (size_t)(size *nmemb));
	printf("<SERVERres>%s\n</SERVER>",*response_ptr);
}
