#ifndef _DEKOMPRESOR_H_
#define _DEKOMPRESOR_H_

#include <stdio.h>
#include <stdlib.h>

#include "huff.h"

void huffman_decode_12_bit(node_t* root, FILE* input_file, FILE* output_file);
void huffman_decode_8_bit(node_t* root, FILE* input_file, FILE* output_file);
void huffman_decode_16_bit(node_t* root, FILE* input_file, FILE* output_file);

#endif