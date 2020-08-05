#ifndef JCON_H
#define JCON_H

#define JCON_datatype enum JCON_datatype

JCON_datatype {
	JCON_STRING,
	JCON_NUMBER,
	JCON_OBJECT,
	JCON_ARRAY,
	JCON_BOOL,
	JCON_NULL
};

struct JCON_element {
	char *start;			// Pointer to the start of json element in the json string
	int keyend;				// Bytes from the start of the element to the end of the key
	int end;				// Bytes from the start of the element to the end of the element
	JCON_datatype type;		// Datatype of the element
};


#include <stdio.h>

void test(void);


#endif
