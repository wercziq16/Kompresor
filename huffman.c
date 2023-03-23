#include <stdio.h>
#include <stdlib.h>

#include "huffman.c"

typedef struct node {
	char value;
	int frequency;
	struct node *left;
	struct node *right;
} node_t;

//stworzenie wezla drzewa

node_t createNode (char value, int frequency) {
	node_t * node = (node_t *) malloc (sizeof(node_t));

	node->left = NULL;
	node->right = NULL;
	node->parent = NULL;
	node->value = value;
	node->frequency = frequency;

	return node;
}

//funkcja porownujaca dla qsorta - do usuniecia

int compare (const void *a, const void *b) {
	int x = ((node_t*)a)->frequency;
	int y = ((node_t*)b)->frequency;
	return (x-y);
}

//tworzymy drzewo - do zmiany

node_t * createTree (node_t * leafs) {
	
	int i;
	int size = sizeof(leafs) / sizeof(leafs*);
	
	node_t ** tree = (node_t**) malloc (size * sizeof(node_t *));

	//brzydkie ale zawsze cos... najlepiej zamienic to na heap (kopiec?), tablica jest slaba

	while (size > 1) {
		qsort (tree, size, sizeof(node_t*), compare);

		node_t* left = tree[0];
		node_t* right = tree[1];
		node_t* parent = createNode ('\0', left->frequency, right->frequency);
		parent->left = left;
		parent->right = right;
		
		tree[0] = parent;

		for (i = 2; i < size; i++)
			tree[i-1] = tree[i];
		
		size--;
	}

	return * tree;
}

//zakodowac szyfrowanie pojedynczego znaku
void code_char (node_t root){}

//zakodowac calosc
void code_text (node_t * root){}

//ustawienie - kodowanie
void encode(FILE *in, FILE *out){
}
//ustawienie - odkodowanie
void decode(FILE *in, FILE *out){
}
