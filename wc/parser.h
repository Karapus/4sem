#ifndef PARSER_CLASS
#define PARSER_CLASS
#include "reader.h"
typedef struct parser {
	char *(*get_word)(struct parser *this);
} parser;

#endif
