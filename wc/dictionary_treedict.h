#include "dictionary.h"

typedef struct tree_node tree_node;

typedef struct dictionary_treedict {
	dictionary;
	tree_node *root;
} dictionary_treedict;

void dictionary_treedict_ctor(dictionary_treedict *this);
void dictionary_treedict_dtor(dictionary_treedict *this);
