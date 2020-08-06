#include "jcon.h"


JCON_parser* jcon_init_parser(char *json){
	JCON_parser *parser = malloc(sizeof(JCON_parser));
	if(parser == NULL){
		return NULL;
	}

	parser->top = NULL;
	parser->json_length = strlen(json) + 1;
	parser->json = malloc(sizeof(char) * parser->json_length);
	if(parser->json == NULL){
		return NULL;
	}

	memcpy(parser->json, json, parser->json_length);

	return parser;
}

void jcon_free_parser(JCON_parser *parser){
	free(parser->json);
	free(parser);
}

