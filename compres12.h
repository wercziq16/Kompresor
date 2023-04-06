/* 

#ifndef _COMPRES_12_H_
#define _COMPRES_12_H_

#include <stdlib.h>
#include <stdio.h>

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

#endif

*/