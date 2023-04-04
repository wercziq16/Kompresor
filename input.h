#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct verbose {
	int in_stats;
	int out_stats;
	double percent;
} verbose_t;

unsigned int * getFrequency (FILE * in);
verbose_t * compress (FILE * in, FILE * out, int * frequency);

#endif
