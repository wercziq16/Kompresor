#ifndef _HUFFMAN_16_H_
#define _HUFFMAN_16_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARACTERS_8 256
#define MAX_CHARACTERS_12 4096
#define MAX_CHARACTERS_16 65536 

#define MAX_TREE_8 16
#define MAX_TREE_12 64
#define MAX_TREE_16 256

typedef struct node_16 {
    uint16_t data;
    uint16_t frequency;
    struct node_16* left;
    struct node_16* right;
} node_16;

typedef struct MinHeap {
    uint16_t size;
    uint16_t capacity;
    node_16** array;
} MinHeap;

uint16_t * data_maker(int compression_type);
node_16* createNode(uint16_t data, uint16_t frequency);
void swapNodes(node_16** a, node_16** b);
void heapify(MinHeap* heap, uint16_t index);
int isSizeOne(MinHeap* heap);
node_16* extractMin(MinHeap* heap);
void insertNode(MinHeap* heap, node_16* node);
int isLeaf(node_16* node);
node_16* buildHuffmanTree(uint16_t* data, uint16_t* frequency, uint16_t size);
void printHuffmanCodes(node_16* node, char* code, int top, FILE * out);
void huffmanCodes(uint16_t* data, uint16_t* frequency, uint16_t size, int compression_level, FILE * out);

#endif
