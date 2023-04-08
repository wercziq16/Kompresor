#ifndef _HUFF_H_
#define _HUFF_H_

#include <stdio.h>
#include <stdlib.h>

//struktura wezla drzewa

typedef struct node {
	unsigned char value;
	unsigned int frequency;
	struct node *left;
	struct node *right;
} node_t;

//struktura do przechowywania wezlow w kolejce priorytetowej

typedef struct line {
	int size;
	int capacity;
	node_t **array;
} line_t;

node_t * newNode(unsigned char value, unsigned int frequency);

int countLeafs (unsigned int * frequency);

node_t ** makeLeafs (unsigned int * frequency);

line_t *createline(int capacity);

void swapNode(node_t **a, node_t **b);

void fixHeap(line_t *minHeap, int i);

int isOne(line_t *minHeap);

node_t *extractMin(line_t *minHeap);

void insertHeap(line_t *minHeap, node_t *minHeapNode);

void buildHeap(line_t *minHeap);

void printRecord(int arr[], int n, FILE * out);

int isLeaf(node_t *root);

line_t *build(unsigned char data[], unsigned int frequency[], int size);

node_t *tree(unsigned char data[], unsigned int frequency[], int size);

void printDict(node_t *root, int * arr, int top, FILE * out);

void HuffmanCodes(unsigned char data[], unsigned int frequency[], int size, FILE * out);
#endif