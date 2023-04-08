#ifndef _FREQUENCY_H_
#define _FREQUENCY_H_

#include <stdlib.h>
#include <stdio.h>

typedef struct f {
    unsigned int *frequency;
    int is_padded;
    int padded_zeros;
} FrequencyResult;

FrequencyResult *getFrequency_8bit(FILE *in);
FrequencyResult *getFrequency_12bit(FILE *in);
FrequencyResult *getFrequency_16bit(FILE *in);

FrequencyResult *getFrequency(int compression_level, FILE *in);

#endif