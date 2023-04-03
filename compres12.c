#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struktura węzła drzewa Huffman
struct huff_node {
    unsigned int freq; // częstotliwość występowania symbolu
    unsigned short code; // kod Huffmana dla symbolu
    struct huff_node *left; // wskaźnik na lewe poddrzewo
    struct huff_node *right; // wskaźnik na prawe poddrzewo
};

// struktura kolejki priorytetowej
struct priority_queue {
    unsigned int size; // aktualny rozmiar kolejki
    unsigned int capacity; // pojemność kolejki
    struct huff_node **nodes; // tablica wskaźników na węzły drzewa
};

// inicjalizacja węzła drzewa Huffman
struct huff_node *new_huff_node(unsigned int freq, unsigned short code) {
    struct huff_node *node = (struct huff_nod *) malloc(sizeof(struct huff_node));
    node->freq = freq;
    node->code = code;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// inicjalizacja kolejki priorytetowej
struct priority_queue *new_priority_queue(unsigned int capacity) {
    struct priority_queue* queue = (struct priority_queue*) malloc(sizeof(struct priority_queue));
    queue->size = 0;
    queue->capacity = capacity;
    queue->nodes = (struct huff_node**) malloc(capacity * sizeof(struct huff_node*));
    return queue;
}

// wstawienie węzła do kolejki priorytetowej
void enqueue(struct priority_queue *queue, struct huff_node *node) {
    if (queue->size == queue->capacity) {
        fprintf(stderr, "Kolejka priorytetowa jest już pełna\n");
        return;
    }
    unsigned int i = queue->size++;
    while (i > 0 && queue->nodes[(i - 1) / 2]->freq > node->freq) {
        queue->nodes[i] = queue->nodes[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->nodes[i] = node;
}

// pobranie i usunięcie węzła o najmniejszej częstotliwości występowania z kolejki priorytetowej
struct huff_node *dequeue(struct priority_queue *queue) {
    if (queue->size == 0) {
        fprintf(stderr, "Kolejka priorytetowa jest już pusta\n");
        return NULL;
    }
    struct huff_node *min_node = queue->nodes[0];
    queue->nodes[0] = queue->nodes[--queue->size];
    unsigned int i = 0;
    while (2 * i + 1 < queue->size) {
        unsigned int j = 2 * i + 1;
        if (j + 1 < queue->size && queue->nodes[j + 1]->freq < queue->nodes[j]->freq) {
            j++;
        }
        if (queue->nodes[i]->freq <= queue->nodes[j]->freq) {
            break;
        }
        struct huff_node *temp = queue->nodes[i];
        queue->nodes[i] = queue->nodes[j];
        queue->nodes[j] = temp;
        i = j;
 }

return min_node;
}

// zwolnienie pamięci zajmowanej przez drzewo Huffman
void free_huff_tree(struct huff_node *root) {
	if (root != NULL) {
		free_huff_tree(root->left);
		free_huff_tree(root->right);
		free(root);
	}
}

// konstrukcja drzewa Huffman dla symboli o zadanych częstotliwościach występowania
struct huff_node *build_huff_tree(unsigned int freqs[]) {
	struct priority_queue *queue = new_priority_queue(256);
		for (unsigned short code = 0; code < 256; code++) {
			if (freqs[code] > 0) {
				struct huff_node *node = new_huff_node(freqs[code], code);
				enqueue(queue, node);
				}
			}
		while (queue->size > 1) {
			struct huff_node *left = dequeue(queue);
			struct huff_node *right = dequeue(queue);
			struct huff_node *parent = new_huff_node(left->freq + right->freq, 0);
			parent->left = left;
			parent->right = right;
			enqueue(queue, parent);
		}
	struct huff_node *root = dequeue(queue);
	free(queue->nodes);
	free(queue);
	return root;
}

// rekurencyjne przeszukiwanie drzewa Huffman i zapisywanie kodów do tablicy
void traverse_huff_tree(struct huff_node *node, unsigned short code, unsigned short *codes) {
	if (node == NULL) {
		return;
	}
	if (node->left == NULL && node->right == NULL) {
		codes[node->code] = code;
	}
	traverse_huff_tree(node->left, (code << 1) | 0, codes);
	traverse_huff_tree(node->right, (code << 1) | 1, codes);
}

// zapisywanie symboli w postaci skompresowanej
void write_compressed(unsigned char *input, unsigned int input_size, unsigned char *output, unsigned int *output_size, unsigned short *codes) {
	unsigned int bit_buffer = 0;
	unsigned int bit_count = 0;
	for (unsigned int i = 0; i < input_size; i++) {
		unsigned short code = codes[input[i]];
		unsigned int bits_to_write = 12;
		while (bits_to_write > 0) {
			unsigned int bits = bits_to_write < (32 - bit_count) ? bits_to_write : (32 - bit_count);
			bit_buffer |= code << bit_count;
			bit_count += bits;
			bits_to_write -= bits;
			if (bit_count == 32) {
				output[*output_size] = (bit_buffer >> 24) & 0xFF;
				output[*output_size + 1] = (bit_buffer >> 16) & 0xFF;
				output[*output_size + 2] = (bit_buffer >> 8) & 0xFF;
				output[*output_size + 3] = bit_buffer & 0xFF;
				*output_size += 4;
				bit_buffer = 0;
				bit_count = 0;
			}
			else if (bits_to_write == 0) {
				if (bit_count >= 24) {
				output[*output_size] = (bit_buffer >> 24) & 0xFF;
				output[*output_size + 1] = (bit_buffer >> 16) & 0xFF;
				output[*output_size + 2] = (bit_buffer >> 8) & 0xFF;
				output[*output_size + 3] = bit_buffer & 0xFF;
				*output_size += 4;
				bit_buffer = 0;
				bit_count = 0;
				}
			}
		}
	}
	if (bit_count > 0) {
		output[*output_size] = (bit_buffer >> 24) & 0xFF;
		if (bit_count > 8) {
			output[*output_size + 1] = (bit_buffer >> 16) & 0xFF;
			if (bit_count > 16) {
				output[*output_size + 2] = (bit_buffer >> 8) & 0xFF;
			}
		}
		*output_size += (bit_count + 7) / 8;
	}
}

// funkcja kompresująca dane z tablicy input do tablicy output przy użyciu kodowania Huffmana
// zwraca 1 w przypadku sukcesu i 0 w przypadku błędu
int compress_huffman(unsigned char *input, unsigned int input_size, unsigned char *output, unsigned int *output_size) {
	unsigned int freqs[256] = { 0 };
	for (unsigned int i = 0; i < input_size; i++) {
		freqs[input[i]]++;
	}
	struct huff_node *root = build_huff_tree(freqs);
		if (root == NULL) {
			return 0;
		}
	unsigned short codes[256] = { 0 };
	traverse_huff_tree(root, 0, codes);
	*output_size = 0;
	output[*output_size] = (input_size >> 24) & 0xFF;
	output[*output_size + 1] = (input_size >> 16) & 0xFF;
	output[*output_size + 2] = (input_size >> 8) & 0xFF;
	output[*output_size + 3] = input_size & 0xFF;
	*output_size += 4;
	write_compressed(input, input_size, output, output_size, codes);
	free_huff_tree(root);
	return 1;
}

// przykladowe uzycie funkcji compress_huffman
int main() {
	unsigned char input[] = "bardzodlugasny ciag znakow w nadziei ze to lepiej sie skompresujhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkklllllllllllllllllllllllllllllllllllllllllllllllllllllllmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnnbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvccccccccccccccccccccccccccccccccccccccccccccccccccccxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaassssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssdddddddddddddddddddddddddddddddddddddddddddddddddddffffffffffffffffffffffffffffffffffffffffffffffffffffgggggggggggggggggggggggggggggggggggggggggggggggggggggghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwweeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeerrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrttttttttttttttttttttttttttttttttttttttttttttttttttttttttyyyyyyyyyyyyyyyye";
	unsigned int input_size = strlen(input);
	unsigned char output[1024];
	unsigned int output_size;
	if (compress_huffman(input, input_size, output, &output_size)) {
		printf("Input size: %u\n", input_size);
		printf("Output size: %u\n", output_size);
		printf("Compressed data: ");
		for (unsigned int i = 0; i < output_size; i++) {
			printf("%02x ", output[i]);
		}
		printf("\n");
	} else {
	printf("Compression failed!\n");
	}
return 0;
}
