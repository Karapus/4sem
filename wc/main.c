#include "reader_shrdr.h"
#include "parser_wprsr.h"

int main() {
	struct reader_shrdr rdr;
	struct parser_wprsr psr;
//	struct counter c;
//	struct dictionary d;
//	struct formater f;
//	struct writer w;
	reader_shrdr_ctor(&rdr);
	parser_wprsr_ctor(&psr, (reader *)&rdr);
	free(psr.get_word(&psr));
}
