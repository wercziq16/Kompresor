#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_HT 100

typedef struct node {
	char value;
	int frequency;
	struct node *left;
	struct node *right;
} node_t;


typedef struct line{
	int size;
	int capacity;
	node_t **array;
}line_t;

node_t * newNode(char value, int frequency);
line_t *createline(int capacity);
void swapNode(node_t **a, node_t **b);
void fixHeap(line_t *minHeap, int i);
int isOne(line_t *minHeap);
node_t *extractMin(line_t *minHeap);
void insertHeap(line_t *minHeap,node_t *minHeapNode);
void buildHeap(line_t *minHeap);
void printArr(int arr[], int n) ;
int Leaf(node_t *root);
line_t *build(char data[], int frequency[], int size);
node_t *tree(char data[], int frequency[], int size) ;
void printCodes(node_t *root, int arr[], int top);
void HuffmanCodes(char data[], int frequency[], int size);
