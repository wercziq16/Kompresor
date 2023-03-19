#include "prepfile.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 256

//trzeba sprawdzic czy plik jest skompresowany czy nie
void checkFile(){}

//get characters from correct input file

int * getCharacters (FILE * in) {
	int * chars = malloc(MAX_CHARS * sizeof(int));
	char c;
	while ( (c=fgetc(in)) != EOF ) chars[c]++;
	return chars;
}

//make leafs out of the characters

int countLeafs (int * chars) {
	int i;
	int counter = 0;
	for (i = 0; i < MAX_CHARS; i++)
		if (chars[i] != NULL)
			counter++;
	return counter;
}	

node_t * makeLeafs (int * chars) {
	int i;
	int counter = countLeafs (chars);

	node_t * leafs = malloc(counter * sizeof(node_t));

	for (i = 0; i < MAX_CHARS; i++) {
		if (chars[i] == NULL)
			return;
		leafs[i] = createNode ('0' + i, chars[i]);
	}

	return leafs;
}

int compare (const void *a, const void *b) {
	int x = ((node_t*)a)->frequency;
	int y = ((node_t*)b)->frequency;
	return (x-y);
}

void qsort_leafs (node_t * leafs) {
	qsort (leafs, sizeof(leafs)/sizeof(*leafs), sizeof(*leafs), compare);
}


