#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "gpmConfig.h"
#include "jcon/jcon.h"
#include "str.h"

int main(void){
	return 0;
}
/*
size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

int main(void){

	char *json = "{\"key\": \"valuestring\"}";
	JCON_parser *parser;
	parser = jcon_init_parser(json);
	
	JCON_element *elements;
	int size = jcon_parse(parser, &elements);
	jcon_free_elements(elements);
	jcon_free_parser(parser);
	return 0;

	CURL *curl;
	CURLcode res;
 
 	struct string output;
	output.string = malloc(1);
	output.size = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();
	
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/kippenjongen/gpm-test-repo/releases");
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &output);

		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	printf("\n%s\n", output.string);

	free(output.string); 
	return 0;
}

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp){
	struct string *output = (struct string *) userp;


	char *ptr = realloc(output->string, output->size + nmemb + 1);
	if(ptr  == NULL){
		printf("well fuck\n");
		return 0;
	}

	output->string = ptr;
	memcpy(&(output->string[output->size]), buffer, nmemb);
	output->size += nmemb;
	output->string[output->size] = 0;

	return nmemb;
}
*/
