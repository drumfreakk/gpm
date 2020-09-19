#include "jcon.h"


JCON_parser* jcon_init_parser(const char *json){
	JCON_parser *parser = malloc(sizeof(JCON_parser));
	if(parser == NULL){
		return NULL;
	}

	parser->json_length = strlen(json) + 1;
	parser->json = malloc(sizeof(char) * parser->json_length);
	if(parser->json == NULL){
		return NULL;
	}

	memcpy(parser->json, json, parser->json_length);

	return parser;
}

int addJCONElement(JCON_element **parent, int currentLength){
	if(parent == NULL || *parent == NULL){
		return -1;
	}
	if(currentLength < 1){
		return -2;
	}

	JCON_element *newparent = realloc(*parent, sizeof(JCON_element) * currentLength);
	if(newparent == NULL){
		return -1;
	}

	newparent[currentLength].type = JCON_NULL;
	newparent[currentLength].parent = NULL;
	newparent[currentLength].last = false;
	newparent[currentLength].value_str = "";
	newparent[currentLength].value_str_size = strlen(newparent[currentLength].value_str);
	newparent[currentLength].element_size = 0;

	*parent = newparent;

	return currentLength + 1;
}

int jcon_parse(const JCON_parser *parser, JCON_element **elements){
	*elements = malloc(sizeof(JCON_element));

	int count = 0;

	for(int i = 0; i < parser->json_length; i++){
		switch(parser->json[i]){
			case '{':
				(*elements)[count].type = JCON_OBJECT;
			case ':':
				count++;
			default:
				break;
		}
	}

	return 1;
}

void jcon_free_parser(JCON_parser *parser){
	free(parser->json);
	free(parser);
}

void jcon_free_elements(JCON_element *element){
	free(element);
}
