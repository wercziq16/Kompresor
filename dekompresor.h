#ifndef _DEKOMPRESOR_H_
#define _DEKOMPRESOR_H_

#include <stdio.h>
#include "huffman16.h"
void huffman_decode_12_bit(node_16* root, FILE* in, FILE* out);
void huffman_decode_8_bit(node_16* root, FILE* in, FILE* out);
void huffman_decode_16_bit(node_16* root, FILE* in, FILE* out);

#endif