#ifndef JCON_H
#define JCON_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

typedef enum JCON_elementtype JCON_elementtype;
typedef struct JCON_element JCON_element;
typedef struct JCON_parser JCON_parser;

enum JCON_elementtype {
	JCON_STRING,
	JCON_NUMBER,
	JCON_OBJECT,
	JCON_ARRAY,
	JCON_BOOL,
	JCON_NULL
};

struct JCON_element {
	char *start;			// Pointer to the start of the value in 
	int keyend;				// 
	int end;
	int size;
	JCON_elementtype type;
};

struct JCON_parser {
	char *json;
	int json_length;
	JCON_element *top;
};

JCON_parser* jcon_init_parser(char *json);
void jcon_free_parser(JCON_parser *parser);

#endif
