#include "curl.h"
 
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

/* the function to invoke as the data recieved */
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







































//exemple : msg= "http://127.0.0.1/index.php?index=coucou

int msg_curl(char* msg)
{
	CURL *curl;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) 
	{
		curl_easy_setopt(curl, CURLOPT_URL, msg);
		/* example.com is redirected, so we tell libcurl to follow redirection */ 
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		


		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
		curl_easy_strerror(res));

		/* always cleanup */ 
		curl_easy_cleanup(curl);
		return 0;
	}
	return 1;
}
