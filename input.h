#ifndef _INPUT_H_
#define _INPUT_H_

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef struct verbose {
	int in_stats;
	int out_stats;
	double percent;
} verbose_t;

typedef struct {
    unsigned int *frequency;
    int is_padded;
    int num_zeros_padded;
} FrequencyResult_12bit;

//unsigned int * getFrequency (FILE * in);
verbose_t * compress (FILE * in, FILE * out, int * frequency);

char* bit_8(FILE* input);
uint16_t * bit_12(FILE * in);
uint16_t *bit_16(FILE *in);

#endif
