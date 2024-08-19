#include <stdio.h> // standard input/output which include function like : printf .
#include <stdlib.h> // standard library which include function like :
		    // malloc , calloc , realloc , free , exit .
#include <string.h> // standard string library which include function like :
		    // strlen , strcpy , strcmp .
#include <openssll/sha.h> // standard library which include SHA function
			  // to generate SHA256 hashes .
#include <microhttp.h> // libmicrohttpd used to create http server .


#define PORT 8888
#define SHORT_URL_LENGTH 6
#define URL_STRORAGE_FILE "url_mapping.txt"

// function to generate a short code using SHA256 Hash for long url .
void generate_short_code(char *output, const char *long_url){
	unsigned char hash[SHA256_DIGEST_LENGTH]; // 32 bytes .
	SHA256((unsigned char*)long_url, strlen(long_url), hash); // generate the SHA256 HASH of
								  // the long url and store it in
								  // the hash .
	for(int i = 0; i < SHORT_URL_LENGTH / 2; i++){
		snprintf(&output[i * 2], 3, "%02x", hash[i]); // convert each byte of the hash
							      // into a 2character hexadecimal 
							      // string and appends it to the 
							      // output buffer .
	}
}

// function to save the url mapping of short url to long url .
void save_url_mapping(const char *short_url, const char *long_url){
	FILE *file = fopen(URL_STORAGE_FILE, "a");
	if(file == NULL){
		perror("Failed to open file");
		return;
	}
	fprintf(file, "%s %s\n", short_urll, long_url);
	fclose(file);
}

// function to look up the long url based on the short url .
char *lookup_long_url(const char *short_url){
	FILE *file = fopen(URL_STORAGE_FILE, "r");
	if (file == NULL){
		perror("Failed to open file");
		return NULL
	}

	char stored_short_url[SHORT_URL_LENGTH + 1];
	char long_url[5048];

	while(fscanf(file, "%s %s", stored_short_url, long_url) != EOF){
		if(strcmp(stored_short_url, short_url) == 0){
			fclose(file);
			return strdup(long_url);
		}
	}
	fclose(file);
	return NULL;
}


// function for handling incoming HTTP request .
static enum MHD_Result handle_request(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *update_date, size_t *upload_date_size, void **con_cls ){
	if(strcmp(method, "GET") != 0){
		return MHD_NO;
	}

	const char *short_url = url + 1;

	char *long_url = lookup_long_url(short_url);
	if(long_url){
		struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
		MHD_add_response_header(response, "Location", long_url);
		enum MHD_Result ret = MHD_queue_response(connection, MHD_FOUND, response);
		MHD_destroy_response(response);
		free(long_url);
		return ret;
	}else{
		const char *not_found = "404 Not Found";
		struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found), (void *) not_found, MHD_RESPMEM_PERSISTENT);
		enum MHD_Resukt ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
		MHD_destroy_response(response);
		return ret;
	}
}

int main(){
	const char *long_url;
	chat short_url[SHORT_URL_LENGHT + 1];

	printf("Enter your lng url : ");
	scanf("%s", long_url);

	generate_short_code(short_url, long_url);
	save_url_mapping(short_url, long_url);

	printf("Shortened url : http://short.url/%s\n", short_url);

	struct MHD_Daemon *daemon;

	daemon = MHD_start_daemon(MHD_USE_SELECT_INTERBALLY, PORT, NULL, NULL, &handle_request, NULL, MHD_OPTION_END);
	if(daemon == NULL){
		return 1;
	}

	printf("Server is running on port %%d\n", PORT);
	getchar();

	MHD_stop_daemon(daemon);
	return 0;
}























