#include "reader_shrdr.h"
#include "parser_wprsr.h"

int main() {
	struct reader_shrdr rdr;
	struct parser_wprsr psr;
	struct counter c;
	reader_shrdr_ctor(&rdr);
	parser_wprsr_ctor(&psr, (reader *)&rdr);
	free(psr.get_word(&psr));
}
