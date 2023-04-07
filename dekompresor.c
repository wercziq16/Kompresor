#include "dekompresor.h"
#include "huff.h"

void huffman_decode_16_bit(node_t* root, FILE* input_file, FILE* output_file) {
    node_t* current = root;
    unsigned char buffer[2];
    buffer[1] = fgetc(input_file);
    while (!feof(input_file)) {
        buffer[0] = buffer[1];
        buffer[1] = fgetc(input_file);
        unsigned short code = (buffer[0] << 8)| buffer[1];
        for (int i = 0; i < 16; i++) {
            if ((code & (1 << (15 - i))) == 0) {
                current = current->left;
            } else {
                current = current->right;
            }
            if (current->left == NULL && current->right == NULL) {
                fputc(current->value, output_file);
                current = root;
            }
        }
    }
}

void huffman_decode_12_bit(node_t* root, FILE* input_file, FILE* output_file) {
    node_t* current = root;
    unsigned char buffer[2];
    buffer[1] = fgetc(input_file);
    while (!feof(input_file)) {
        buffer[0] = buffer[1];
        buffer[1] = fgetc(input_file);
        unsigned short code = (buffer[0] << 4) | (buffer[1] >> 4);
        for (int i = 0; i < 12; i++) {
            if ((code & (1 << (11 - i))) == 0) {
                current = current->left;
            } else {
                current = current->right;
            }
            if (current->left == NULL && current->right == NULL) {
                fputc(current->value, output_file);
                current = root;
            }
        }
    }
}

void huffman_decode_8_bit(node_t* root, FILE* input_file, FILE* output_file) {
    node_t* current = root;
    unsigned char buffer = fgetc(input_file);
    while (!feof(input_file)) {
        for (int i = 0; i < 8; i++) {
            if ((buffer & (1 << (7 - i))) == 0) {
                current = current->left;
            } else {
                current = current->right;
            }
            if (current->left == NULL && current->right == NULL) {
                fputc(current->value, output_file);
                current = root;
            }
        }
        buffer = fgetc(input_file);
    }
}
