#include "huffman16.h"

uint16_t * data_maker(int compression_type){
    
    uint16_t n;

    if (compression_type == 2) {
        n = (uint16_t)MAX_CHARACTERS_16;
    }
    else if (compression_type == 1) {
        n = (uint16_t)MAX_CHARACTERS_12;
    }
    else {
        n = (uint16_t)MAX_CHARACTERS_8;
    }

    uint16_t * data = malloc(n * sizeof(uint16_t));
    uint16_t i;

    for (i = 0; i < n; i++){
        data[i] = i;
    }

    return data;
}


node_16* createNode(uint16_t data, uint16_t frequency) {
    node_16* node = (node_16*)malloc(sizeof(node_16));
    node->data = data;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void swapNodes(node_16** a, node_16** b) {
    node_16* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(MinHeap* heap, uint16_t index) {
    uint16_t smallest = index;
    uint16_t left = 2 * index + 1;
    uint16_t right = 2 * index + 2;

    if (left < heap->size && heap->array[left]->frequency < heap->array[smallest]->frequency)
        smallest = left;

    if (right < heap->size && heap->array[right]->frequency < heap->array[smallest]->frequency)
        smallest = right;

    if (smallest != index) {
        swapNodes(&heap->array[smallest], &heap->array[index]);
        heapify(heap, smallest);
    }
}

int isSizeOne(MinHeap* heap) {
    return heap->size == 1;
}

node_16* extractMin(MinHeap* heap) {
    node_16* minNode = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];
    --heap->size;
    heapify(heap, 0);
    return minNode;
}

void insertNode(MinHeap* heap, node_16* node) {
    ++heap->size;
    uint16_t i = heap->size - 1;
    while (i && node->frequency < heap->array[(i - 1) / 2]->frequency) {
        heap->array[i] = heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    heap->array[i] = node;
}

int isLeaf(node_16* node) {
    return !(node->left) && !(node->right);
}

node_16* buildHuffmanTree(uint16_t* data, uint16_t* frequency, uint16_t size) {
    MinHeap* heap = (MinHeap*) malloc(sizeof(MinHeap));
    heap->size = 0;
    heap->capacity = size;
    heap->array = (node_16**) malloc(heap->capacity * sizeof(node_16*));

    int charCount = 0;
    for (uint16_t i = 0; i < size; ++i) {
        if (frequency[i] > 0) {
		heap->array[charCount] = createNode(data[i], frequency[i]);
		charCount++;
	}
    }

    heap->size = charCount;
    for (int i = (charCount - 1) / 2; i >= 0; --i)
        heapify(heap, i);

    while (!isSizeOne(heap)) {
        node_16* leftNode = extractMin(heap);
        node_16* rightNode = extractMin(heap);

        node_16* internalNode = createNode(0, leftNode->frequency + rightNode->frequency);
        internalNode->left = leftNode;
        internalNode->right = rightNode;

        insertNode(heap, internalNode);
    }

    node_16* root = extractMin(heap);
    free(heap->array);
    free(heap);
    return root;
}

int* printHuffmanCodes(node_16* node, char* code, int top, FILE * out) {
    int* codes = malloc(256 * sizeof(int));
    
    if (node->left) {
    code[top] = '0';
    printHuffmanCodes(node->left, code, top + 1, out);
    }
    if (node->right) {
    code[top] = '1';
    printHuffmanCodes(node->right, code, top + 1, out);
    }
    if (isLeaf(node)) {
        fprintf(out, "%c: ", node->data);
        for (int i = 0; i < top; ++i)
           fprintf(out, "%c", code[i]);
	codes[(int)node->data] = atoi(code);
	printf("%d  kod %s \n", atoi(code), code);
        fprintf(out, "\n");
    }
    return codes;
}

int* huffmanCodes(uint16_t * data, uint16_t * frequency, uint16_t size, int compression_level, FILE * out) {
    node_16* root = buildHuffmanTree(data, frequency, size);
    int height;

    if (compression_level == 2)
        height = (int)MAX_TREE_16;
    else if (compression_level == 1)
        height = (int)MAX_TREE_12;
    else height = (int)MAX_TREE_8;

    char code[height], c;
    return printHuffmanCodes(root, code, 0, out);
}
