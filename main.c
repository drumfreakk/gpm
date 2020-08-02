#include <stdio.h>
#include <curl/curl.h>
#include "config.h"

size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp);

int main(void){
	CURL *curl;
	CURLcode res;
 
	curl_global_init(CURL_GLOBAL_DEFAULT);
 
	curl = curl_easy_init();
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.github.com/repos/kippenjongen/gpm-test-repo/releases");
		curl_easy_setopt(curl, CURLOPT_USERAGENT, USER_AGENT);
//		curl_easy_setopt(easyhandle, CURLOPT_WRITEFUNCTION, write_data); 

		res = curl_easy_perform(curl);
		if(res != CURLE_OK){
			fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
		}
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
	return 0;
}


size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp){
	return 0;
}
