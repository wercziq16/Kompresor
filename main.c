#include<stdio.h>
#include <stdlib.h>
#include "huffman.h"


int main() {
char data[] = {'a', 'b', 'c', 'd', 'e', 'f'};
int freq[] = {5, 9, 12, 13, 16, 45};
int size = sizeof(data) / sizeof(data[0]);
HuffmanCodes(data, freq, size);
return 0;
}
