#ifndef FUNCS_H
#define FUNCS_H

#define JSMN_HEADER
#include "jsmn/jsmn.h"

typedef struct{
	char *string;
	size_t size;
} string;

typedef struct{
	jsmntype_t type;
	string string;
	int size;
} jsmnstring;

jsmnstring jsmntok_to_string(jsmntok_t *token, char **string){
	jsmnstring to_ret;
	to_ret.type = token->type;
	to_ret.size = token->size;
	to_ret.string.size = token->end - token->start;
	to_ret.string.string = string[token->start];
	return to_ret;
}


#endif
