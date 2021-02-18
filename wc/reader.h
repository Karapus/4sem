#ifndef READER_CLASS
#define READER_CLASS

typedef struct reader {
	int (*get_char)();
} reader;

#endif
