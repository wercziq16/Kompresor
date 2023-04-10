#include "padding.h"

pfile_t * padding_12bit(FILE * in, FILE * padded){
    fseek(in, 0L, SEEK_END);
    long file_size = ftell(in);
    fseek(in, 0L, SEEK_SET);

    int rem_chars = (file_size * 8) % 12;
    unsigned char c;

    pfile_t * padding = (pfile_t*)malloc(sizeof(pfile_t));
    padding->pfile = padded;
    padding->pbytes = rem_chars;

    while (file_size > 0)
    {
        c = fgetc(in);
        fputc(c, padded);
        file_size--;
    }

    while (rem_chars > 0)
    {
        fputc('0', padded);
        rem_chars--;
    }

    return padding;
}

pfile_t * padding_16bit(FILE * in, FILE * padded){
    fseek(in, 0L, SEEK_END);
    long file_size = ftell(in);
    fseek(in, 0L, SEEK_SET);

    int rem_chars = (file_size * 8) % 16;
    unsigned char c;

    pfile_t * padding = (pfile_t*)malloc(sizeof(pfile_t));
    padding->pfile = padded;
    padding->pbytes = rem_chars;

    while (file_size > 0)
    {
        c = fgetc(in);
        fputc(c, padded);
        file_size--;
    }

    while (rem_chars > 0)
    {
        fputc('0', padded);
        rem_chars--;
    }

    return padding;
}