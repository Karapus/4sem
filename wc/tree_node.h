#include "list_node.h"

typedef struct tree_node {
	char *val;
	int n;
	struct tree_node *left;
	struct tree_node *right;
} tree_node;

tree_node *tree_node_heapctor(char *word);

void tree_node_dtor(tree_node *node);

void tree_node_add(tree_node *root, char *word);

list_node *tree_to_list(tree_node *tree) {
	list_node *less = tree->left	? tree_to_list(tree->left)	: NULL;
	list_node *more = tree->right	? tree_to_list(tree->right)	: NULL;
	list_node *node = less ? list_node_add(less, tree->val, tree->n) : list_node_heapctor(tree->val, tree->n);
	node->next = more;
	return less ? less : node;
}
