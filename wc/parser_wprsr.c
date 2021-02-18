#include "parser_wprsr.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define INIT_LEN 5
#define GROW_RATE 2

char *parser_wprsr_get_word(parser_wprsr *this) {
	size_t sz = INIT_LEN;
	char *buf = malloc(sizeof(char) * sz);
	char c;
	while (isspace(c = this->rdr->get_char()))
		;
	size_t i = 0;
	buf[i++] = c;
	while (!isspace(c = this->rdr->get_char())) {
		if (i == sz)
			buf = realloc(buf, sz *= GROW_RATE);
		buf[i++] = c;
	}
	buf[i] = '\0';
	printf("%s\n", buf);
	return buf;
}

void parser_wprsr_ctor(parser_wprsr *this, reader *rdr) {
	this->get_word = parser_wprsr_get_word;
	this->rdr = rdr;
}
