
#include <stdlib.h>

#include "huff.h"

#define MAX_TREE_HT 16

#define MAX_VALUE_8_BIT 255
#define MAX_VALUE_12_BIT 4095
#define MAX_VALUE_16_BIT 65535

//Funkcja tworzaca nowy węzeł drzewa z danymi i częstością wystąpienia

node_t * newNode(unsigned char value, unsigned int frequency) {
	
	node_t *temp = (node_t *)malloc(sizeof(node_t));
    	
	temp->left = temp->right = NULL;
	temp->value = value;
    	temp->frequency = frequency;
    	
	return temp;
}

int countLeafs (unsigned int * frequency) {
	int i;
	int counter = 0;
	for (i = 0; i < MAX_CHARS; i++)
		if (frequency[i] != 0)
			counter++;
	return counter;
}

node_t ** makeLeafs (unsigned int * frequency) {
	int i;
	int counter = countLeafs (frequency);

	node_t ** leafs = malloc(counter * sizeof(node_t*));

	for (i = 0; i < MAX_CHARS; i++) {
		if (frequency[i] != 0)
			leafs[i] = newNode ('0' + i, frequency[i]);
	}

	return leafs;
}

line_t *createline(int capacity) {
	line_t *minHeap = (line_t *)malloc(sizeof(line_t));
    	minHeap->size = 0;
    	minHeap->capacity = capacity;
    	minHeap->array = (node_t **)malloc(minHeap->capacity * sizeof(node_t *));
    	return minHeap;
}

void swapNode(node_t **a, node_t **b) {
    	node_t *t = *a;
    	*a = *b;
    	*b = t;
}

void fixHeap(line_t *minHeap, int i) {
    	int smallest = i;
    	int left = 2 * i + 1;
    	int right = 2 * i + 2;
    	if (left < minHeap->size && minHeap->array[left]->frequency < minHeap->array[smallest]->frequency)
        	smallest = left;
    	if (right < minHeap->size && minHeap->array[right]->frequency < minHeap->array[smallest]->frequency)
        	smallest = right;
    	if (smallest != i) {
        	swapNode(&minHeap->array[smallest], &minHeap->array[i]);
        	fixHeap(minHeap, smallest);
    	}
}

//Usuwanie wezlow kolejki priorytetowej

int isOne(line_t *minHeap) {
    	return (minHeap->size == 1);
}


node_t *extractMin(line_t *minHeap) {
    	node_t *temp = minHeap->array[0];
    	minHeap->array[0] = minHeap->array[minHeap->size - 1];
    	--minHeap->size;
    	fixHeap(minHeap, 0);
    	return temp;
}

//Dodanie nowego wezla do kolejki

void insertHeap(line_t *minHeap, node_t *minHeapNode) {
    	++minHeap->size;
    	int i = minHeap->size - 1;
    	while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        	minHeap->array[i] = minHeap->array[(i - 1) / 2];
        	i = (i - 1) / 2;
    	}
    	minHeap->array[i] = minHeapNode;
}

void buildHeap(line_t *minHeap) {
    	int n = minHeap->size - 1;
    	int i;
    	for (i = (n - 1) / 2; i >= 0; --i)
    		fixHeap(minHeap, i);
}

void printRecord(int arr[], int n, FILE * out) {
    	int i;
	for (i = 0; i < n; ++i)
        	fprintf(out, "%d", arr[i]);
    	fprintf(out, "\n");
}

int isLeaf(node_t *root){
	return!(root->left) && !(root->right);
}

line_t *build(unsigned char data[], unsigned int frequency[], int size) {
	line_t *minHeap = createline(size);
	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], frequency[i]);
	minHeap->size = size;
	buildHeap(minHeap);
	return minHeap;
}

node_t *tree(unsigned char data[], unsigned int frequency[], int size) {
	node_t *left, *right, *top;
	line_t *minHeap = build(data, frequency, size);
	while (!isOne(minHeap)) {
		left = extractMin(minHeap);
		right = extractMin(minHeap);
		top = newNode('$', left->frequency + right->frequency);
		top->left = left;
		top->right = right;
		insertHeap(minHeap, top);
	}
	return extractMin(minHeap);
}

//tworzenie slownika

void printDict(node_t *root, char * arr, int top, FILE * out) {
	if (root->left) {
		arr[top] = 0;
		printRecord(root->left, arr, top + 1);
	}

	if (root->right) {
		arr[top] = 1;
		printRecord(root->right, arr, top + 1);
	}

	if (isLeaf(root)) {
 	  	fprintf(out, "%c: ", root->value);
    		printRecord(arr, top, out);
	}
}

void HuffmanCodes(unsigned char data[], unsigned int frequency[], int size, FILE * out) {
	node_t *root = tree(data, frequency, size);
	int arr[MAX_TREE_HT], top = 0;
	printDict(root, arr, top, out);
}

/*
void compress(FILE *in, FILE *out, unsigned char data[], unsigned int frequency[]) {


*/




