#ifndef _PADDING_H_
#define _PADDING_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//paddedfile 

typedef struct padding {
    FILE * pfile;
    int pbytes;
} pfile_t;

pfile_t * padding_12bit(FILE * in, FILE * padded);
pfile_t * padding_16bit(FILE * in, FILE * padded);

#endif

