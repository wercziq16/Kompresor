#ifndef _FREQUENCY_H_
#define _FREQUENCY_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

/*
typedef struct f {
    uint16_t *frequency;
    int is_padded;
    int padded_zeros;
} FrequencyResult;
*/
/*
FrequencyResult *getFrequency_8bit(FILE *in);
FrequencyResult *getFrequency_12bit(FILE *in);
FrequencyResult *getFrequency_16bit(FILE *in);

FrequencyResult *getFrequency(int compression_level, FILE *in);
*/

int countNonZeroFrequency(uint16_t * frequency);

uint16_t *getFrequency_8bit(FILE *in);
uint16_t *getFrequency_12bit(FILE *in);
uint16_t *getFrequency_16bit(FILE *in);

uint16_t *getFrequency(int compression_level, FILE *in);

#endif