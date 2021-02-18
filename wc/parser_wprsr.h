#include "parser.h"

typedef struct parser_wprsr {
	struct parser;
	reader *rdr;
} parser_wprsr;

void parser_wprsr_ctor(parser_wprsr *this, reader *rdr);
