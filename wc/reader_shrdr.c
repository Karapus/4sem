#include "reader_shrdr.h"
#include <stdio.h>

void reader_shrdr_ctor(struct reader_shrdr *this) {
	this->get_char = getchar;
}
