#include <stdio.h>
#include <stdlib.h>

#define MAX_TREE_HT 100

//struktura wezla drzewa

typedef struct node {
	char value;
	int frequency;
	struct node *left;
	struct node *right;
} node_t;


//struktura do przechowywania wezlow w kolejce priorytetowej

typedef struct line {
	int size;
	int capacity;
	node_t **array;
} line_t;

//Funkcja tworzaca nowy węzeł drzewa z danymi i częstością wystąpienia

node_t * newNode(char value, int frequency) {
    node_t *temp = (node_t *)malloc(sizeof(node_t));
    temp->left = temp->right = NULL;
    temp->value = value;
    temp->frequency = frequency;
    return temp;
}

line_t *createline(int capacity) {
line_t *minHeap = (line_t *)malloc(sizeof(line_t));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (node_t **)malloc(minHeap->capacity * sizeof(node_t *));
    return minHeap;
}

void swapNode(node_t **a, node_t **b) {
    node_t*t = *a;
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

void insertHeap(line_t *minHeap,node_t *minHeapNode) {
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

int leaf(node_t *root){
	return!(root->left) && !(root->right);
}

line_t *build(char data[], int frequency[], int size) {
	line_t *minHeap = createline(size);
	for (int i = 0; i < size; ++i)
		minHeap->array[i] = newNode(data[i], frequency[i]);
	minHeap->size = size;
	buildHeap(minHeap);
	return minHeap;
}

node_t *tree(char data[], int frequency[], int size) {
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

void printCodes(node_t *root, int arr[], int top) {
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
	node_t *root = tree(data, frequency, size);
	int arr[MAX_TREE_HT], top = 0;
	printCodes(root, arr, top);
}

