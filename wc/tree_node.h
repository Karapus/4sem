#include <stdlib.h>
#include <string.h>

typedef struct tree_node {
	char *val;
	int n;
	struct tree_node *left;
	struct tree_node *right;
} tree_node;

typedef struct list_node {
	char *val;
	int n;
	struct list_node *next;
} list_node;

list_node *list_node_heapctor(char *word, int n) {
	list_node *this = malloc(sizeof(list_node));
	this->next = NULL;
	this->val = word;
	this->n = n;
	return this;
}

tree_node *tree_node_heapctor(char *word) {
	tree_node *this = malloc(sizeof(tree_node));
	this->left = this->right = NULL;
	this->val = word;
	this->n  = 1;
	return this;
}

void tree_node_dtor(tree_node *node) {
	if (node->left)
		tree_node_dtor(node->left);
	if (node->right)
		tree_node_dtor(node->right);
	free(node);
}

void tree_node_add(tree_node *root, char *word) {
	int cmp = strcmp(root->val, word);
	if (cmp = 0)
		root->val++;
	else if (cmp < 0) {
		if (root->left)
			return node_add(root->left, word);
		else
			return (void) (root->left = tree_node_ctor(word));
	}
	if (root->right)
		return node_add(root->right, word);
	else
		return (void) (root->right = tree_node_ctor(word));
}
