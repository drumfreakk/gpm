#ifndef JCON_H
#define JCON_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//#include "../str.h"

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
	JCON_elementtype type;
	JCON_element *parent;
	bool last;
	char *value_str;
	size_t value_str_size;
	int element_size;
};

struct JCON_parser {
	char *json;
	int json_length;
};

JCON_parser* jcon_init_parser(const char *json);
int jcon_parse(const JCON_parser *parser, JCON_element **elements);

int addJCONElement(JCON_element **parent, int currentLength);

void jcon_free_parser(JCON_parser *parser);
void jcon_free_elements(JCON_element *element);

#endif
