#include "dictionary_treedict.h"
#include "tree_node.h"
#include <stdlib.h>
#include <string.h>

void dictionary_treedict_ctor(dictionary_treedict *this) {
	this->root = NULL;
}

void dictionary_treedict_dtor(dictionary_treedict *this) {
	if (this->root)
		tree_node_dtor(this->root);
}

void dictionary_treedict_add_word(dictionary_treedict *this, char *word) {
	tree_node_add(this->root, word);
}

list_node *dictionary_treedict_to_list(dictionary_treedict *this) {
	return tree_node_to_list(this->root);
}
