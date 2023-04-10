#include "frequency.h"

#define SIZE8 256
#define SIZE12 4096
#define SIZE16 65536

/*
FrequencyResult *getFrequency_8bit(FILE *in) {
    if (in == NULL) {
        fprintf(stderr, "Nie można odczytać pliku.\n");
        return NULL;
    }
    FrequencyResult *result = NULL;
    do {
        result = malloc(sizeof(FrequencyResult));
        if (result == NULL) {
            fprintf(stderr, "Nie można zaalokować pamięci.\n");
            break;
        }
        result->frequency = calloc(SIZE8, sizeof(uint16_t));
        if (result->frequency == NULL) {
            fprintf(stderr, "Nie można zaalokować pamięci.\n");
            free(result);
            break;
        }
        
        // get the size of the file in bytes
        fseek(in, 0L, SEEK_END);
        long file_size = ftell(in);
        fseek(in, 0L, SEEK_SET);

        // calculate the number of 8-bit characters in the file
        int num_chars = file_size;
        
        // read the rest of the file as 8-bit characters
        while (!feof(in) && num_chars > 0) {
            unsigned char c = fgetc(in);
            for (int i = 0; i < 8; i++) {
                result->frequency[(c >> (7 - i)) & 1]++;
            }
            num_chars--;
        }
        break;
    } while (1);
    return result;
}

FrequencyResult *getFrequency_12bit(FILE *in) {
    if (in == NULL) {
        fprintf(stderr, "Nie można odczytać pliku.\n");
        return NULL;
    }
    unsigned char buffer = 0; // buffer to store the bits read from the file
    int bits_read = 0; // number of bits read so far
    FrequencyResult *result = NULL;
    do {
        result = malloc(sizeof(FrequencyResult));
        if (result == NULL) {
            fprintf(stderr, "Nie można zaalokować pamięci.\n");
            break;
        }
        result->frequency = calloc(SIZE12, sizeof(uint16_t));
        if (result->frequency == NULL) {
            fprintf(stderr, "Nie można zaalokować pamięci.\n");
            free(result);
            break;
        }
        result->is_padded = 0;
        result->padded_zeros = 0;
        // get the size of the file in bytes
        fseek(in, 0L, SEEK_END);
        long file_size = ftell(in);
        fseek(in, (file_size - 1), SEEK_SET);
        // calculate the number of 12-bit characters in the file
        int num_chars = (file_size * 8 + 11) / 12;
        // check if the last byte needs padding
        int bits_remaining = file_size * 8 % 12;
        if (bits_remaining > 0) {
            unsigned char last_byte = fgetc(in);
            result->is_padded = 1;
            result->padded_zeros = 8 - bits_remaining;
            for (int i = 0; i < bits_remaining; i++) {
                buffer = (buffer << 1) | ((last_byte >> (7 - i)) & 1);
                bits_read++;
            }
            for (int i = bits_remaining; i < 8; i++) {
                last_byte = (last_byte << 1) | 0; // pad the last byte with zeros
                bits_read++;
            }
            buffer = (buffer << 4) | (last_byte >> 4); // add the padded last byte to the buffer as a complete 12-bit character
            result->frequency[buffer]++;
            buffer = 0; // reset the buffer for the next 12 bits
            bits_read = 0;
            num_chars++; // increment the number of characters
        }
        // read the rest of the file as 12-bit characters
        while (!feof(in) && num_chars > 0) {
            unsigned char c = fgetc(in);
            for (int i = 0; i < 8; i++) {
                buffer = (buffer << 1) | ((c >> (7 - i)) & 1); // shift the buffer left by 1 bit and add the next bit from the file
                bits_read++;
                if (bits_read == 12) { // if we have read 12 bits, we have a complete 12-bit character
                    result->frequency[buffer]++;
                    buffer = 0; // reset the buffer for the next 12 bits
                    bits_read = 0;
                    num_chars--;
                }
            }
        }
        break;
    } while (1);
    return result;
}

FrequencyResult *getFrequency_16bit (FILE *in) {
    if (in == NULL) {
        fprintf(stderr, "Nie można odczytać pliku.\n");
        return NULL;
    }
    unsigned short buffer = 0; // buffer to store the bits read from the file
    int bits_read = 0; // number of bits read so far
    FrequencyResult *result = NULL;
    do {
        result = malloc(sizeof(FrequencyResult));
        if (result == NULL) {
            fprintf(stderr, "Nie można zaalokować pamięci.\n");
            break;
        }
        result->frequency = calloc(SIZE16, sizeof(uint16_t));
        if (result->frequency == NULL) {
            fprintf(stderr, "Nie można zaalokować pamięci.\n");
            free(result);
            break;
        }
        result->is_padded = 0;
        result->padded_zeros = 0;
        // get the size of the file in bytes
        fseek(in, 0L, SEEK_END);
        long file_size = ftell(in);
        fseek(in, 0L, SEEK_SET);
        // calculate the number of 16-bit characters in the file
        int num_chars = (file_size * 8 + 15) / 16;
        // check if the last byte needs padding
        int bits_remaining = file_size * 8 % 16;
        if (bits_remaining > 0) {
            unsigned char last_byte = fgetc(in);
            result->is_padded = 1;
            result->padded_zeros = 16 - bits_remaining;
            for (int i = 0; i < bits_remaining; i++) {
                buffer = (buffer << 1) | ((last_byte >> (7 - i)) & 1);
                bits_read++;
            }
            for (int i = bits_remaining; i < 8; i++) {
                last_byte = (last_byte << 1) | 0; // pad the last byte with zeros
                bits_read++;
            }
            buffer = (buffer << 8) | (last_byte << 4); // add the padded last byte to the buffer as a complete 16-bit character
            result->frequency[buffer]++;
            buffer = 0; // reset the buffer for the next 16 bits
            bits_read = 0;
            num_chars++; // increment the number of characters
        }
        // read the rest of the file as 16-bit characters
        while (!feof(in) && num_chars > 0) {
            unsigned char c = fgetc(in);
            for (int i = 0; i < 8; i++) {
                buffer = (buffer << 1) | ((c >> (7 - i)) & 1); // shift the buffer left by 1 bit and add the next bit from the file
                bits_read++;
                if (bits_read == 16) { // if we have read 16 bits, we have a complete 16-bit character
                    result->frequency[buffer]++;
                    buffer = 0; // reset the buffer for the next 16 bits
                    bits_read = 0;
                    num_chars--;
                }
            }
        }
        break;
    } while (1);
    return result;
}
*/

uint16_t* getFrequency_8bit(FILE* in) {
    
    uint16_t* frequency = calloc(SIZE8, sizeof(uint16_t));
    if (frequency == NULL) {
        fprintf(stderr, "Nie można zaalokować pamięci.\n");
        return NULL;
    }

    unsigned char c;
    while ((c = fgetc(in)) != EOF) {
        frequency[c]++;
    }

    return frequency;
}

uint16_t * getFrequency_12bit(FILE * in){
    
    uint16_t * frequency = calloc(SIZE12, sizeof(uint16_t));

    if (frequency == NULL) {
        fprintf(stderr, "Nie można zaalokować pamięci.\n");
        return NULL;
    }

    uint16_t buffer = 0; // buffer to store the bits read from the file
    int bits_read = 0; // number of bits read so far

    while (!feof(in)) {
        unsigned char c = fgetc(in);
        for (int i = 0; i < 8; i++) {
            buffer = (buffer << 1) | ((c >> (7 - i)) & 1); // shift the buffer left by 1 bit and add the next bit from the file
            bits_read++;
            if (bits_read == 12) { // if we have read 12 bits, we have a complete 12-bit character
                frequency[buffer]++;
                buffer = 0; // reset the buffer for the next 12 bits
                bits_read = 0;
            }
        }
    }

    return frequency;
}

uint16_t* getFrequency_16bit(FILE* in) {
    uint16_t* frequency = calloc(SIZE16, sizeof(uint16_t));
    if (frequency == NULL) {
        fprintf(stderr, "Nie można zaalokować pamięci.\n");
        return NULL;
    }

    uint16_t buffer = 0; // buffer to store the bits read from the file
    int bits_read = 0; // number of bits read so far
    while (!feof(in)) {
        unsigned char c = fgetc(in);
        buffer = (buffer << 8) | c; // shift the buffer left by 8 bits and add the next 8 bits from the file
        bits_read += 8;
        if (bits_read == 16) { // if we have read 16 bits, we have a complete 16-bit character
            frequency[buffer]++;
            buffer = 0; // reset the buffer for the next 16 bits
            bits_read = 0;
        }
    }
    return frequency;
}

uint16_t *getFrequency(int compression_level, FILE *in) {
    
    uint16_t * ret = malloc(sizeof(uint16_t));

    if (compression_level == 1) {
        ret = getFrequency_12bit(in);
    }
    else if (compression_level == 2) {
        ret = getFrequency_16bit(in);
    }
    else {
        ret = getFrequency_8bit(in);
    }

    return ret;
}

