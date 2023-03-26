#include <stdio.h>
#include <stdlib.h>

//#include "huffman.c"

#define MAX_TREE_HT 100

//struktura wezla drzewa

struct node {
	char value;
	int frequency;
	struct node *left;
	struct node *right;
};


//struktura do przechowywania wezlow w kolejce priorytetowej

struct line{
	int size;
	int capacity;
	struct node **array;
};

//Funkcja tworzaca nowy węzeł drzewa z danymi i częstością wystąpienia

struct node * newNode(char value, int frequency) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->left = temp->right = NULL;
    temp->value = value;
    temp->frequency = frequency;
    return temp;
}

struct line *createline(int capacity) {
struct line *minHeap = (struct line *)malloc(sizeof(struct line));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct node **)malloc(minHeap->capacity * sizeof(struct node *));
    return minHeap;
}

void swapNode(struct node **a, struct node **b) {
    struct node*t = *a;
    *a = *b;
    *b = t;
}

void fixHeap(struct line *minHeap, int i) {
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

int isOne(struct line *minHeap) {
    return (minHeap->size == 1);
}


struct node *extractMin(struct line *minHeap) {
    struct node *temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    fixHeap(minHeap, 0);
    return temp;
}

//Dodanie nowego wezla do kolejki

void insertHeap(struct line *minHeap,struct node *minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->frequency < minHeap->array[(i - 1) / 2]->frequency) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

void buildHeap(struct line *minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
    fixHeap(minHeap, i);
}

void printArr(int arr[], int n, FILE *fptr) {
    

    if ((fptr = fopen("wynik.txt", "w")) == NULL) {
        printf("Nie można otworzyć pliku wynik.txt\n");
        return;
    }

    int i;
    for (i = 0; i < n; ++i) {
        fprintf(fptr, "%d", arr[i]);
    }
    fprintf(fptr, "\n");

    fclose(fptr);
}

int leaf(struct node *root){
	return!(root->left) && !(root->right);
}

struct line *build(char data[], int frequency[], int size) {
	struct line *minHeap = createline(size);
	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], frequency[i]);
	minHeap->size = size;
	buildHeap(minHeap);
	return minHeap;
}

struct node *tree(char data[], int frequency[], int size) {
	struct node *left, *right, *top;
	struct line *minHeap = build(data, frequency, size);
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

void printCodes(struct node *root, int arr[], int top) {
	if (root->left) {
		arr[top] = 0;
		printCodes(root->left, arr, top + 1);
	}
	if (root->right) {
		arr[top] = 1;
		printCodes(root->right, arr, top + 1);
	}
	if (leaf(root)) {
 	  	FILE *fp;
    		fp = fopen("output.txt", "a");
    		fprintf(fp, "%c: ", root->value);
    		printArr(arr, top, fp);
    		fclose(fp);
	}
}

void HuffmanCodes(char data[], int frequency[], int size) {
	struct node *root = tree(data, frequency, size);
	int arr[MAX_TREE_HT], top = 0;
	printCodes(root, arr, top);
}

