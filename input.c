#include "input.h"

#define SIZE8 256
#define SIZE12 4096
#define SIZE16 65536

#define MAX_CHARS 256

#define length(x) ((int)log10(x)+1)

/*
unsigned int * getFrequency (FILE * in) {
	char c;
	unsigned int * frequency = calloc(MAX_CHARS, sizeof(int));
	while ( (c=fgetc(in)) != EOF ) frequency[c]++;
	return * frequency;
}
*/
unsigned int * getFrequency(FILE *in) {
    if (in == NULL) {
        fprintf(stderr, "Nie można odczytać pliku.\n");
        return NULL;
    }
    char c;
    unsigned int *frequency = NULL;
    do {
        frequency = calloc(MAX_CHARS, sizeof(unsigned int));
        if (frequency == NULL) {
            fprintf(stderr, "Nie można zaalokować pamięci.\n");
            break;
        }
        while ((c = fgetc(in)) != EOF) {
            frequency[(unsigned char) c]++;
        }
        break;
    } while (1);
    return frequency;
}

//dopisac verbose
verbose_t * compress(FILE *in, FILE *out, int *codes) {
    char c;
    char bit;
    char x = 0;
    int leftToByte = 8;
    int code = 0;
    int length = 0;
    int in_stats = 0;
    int out_stats = 0;

    verbose_t *verbose = malloc(sizeof(verbose_t));
    if (verbose == NULL) {
        fprintf(stderr, "Nie można zaalokować pamięci dla zmiennej verbose.\n");
        return NULL;
    }
    verbose->in_stats = 0;
    verbose->out_stats = 0;
    verbose->percent = 0.0;

    while ((c = fgetc(in)) != EOF) {
        (verbose->in_stats)++;
        length = length(codes[c]);
        code = codes[c];
        while (length > 0) {
            (verbose->out_stats)++;
            bit = code % 10;
            code /= 10;
            x |= bit;
            leftToByte--;
            length--;
            if (leftToByte == 0) {
                if (fputc(x, out) == EOF) {
                    fprintf(stderr, "Błąd podczas zapisywania skompresowanych danych.\n");
                    free(verbose);
                    return NULL;
                }
                x = 0;
                leftToByte = 8;
            }
            x = x << 1;
        }
    }

    //dopelnienie
    if (leftToByte != 8) {
        x <<= (leftToByte - 1);
        if (fputc(x, out) == EOF) {
            fprintf(stderr, "Błąd podczas zapisywania skompresowanych danych.\n");
            free(verbose);
            return NULL;
        }
    }

    verbose->in_stats *= 8;
    verbose->percent = ((double) verbose->out_stats / verbose->in_stats) * 100;

    return verbose;
}
/*
verbose_t * compress (FILE * in, FILE * out, int * codes) {
	char c;
	char bit;
	char x = 0;

	int leftToByte = 8;
	int code = 0;
	int length = 0;
	int in_stats = 0;
	int out_stats = 0;

	verbose_t verbose = 

	while ( (c=fgetc(in)) != EOF ) {

		(verbose->in_stats)++;
		length = length(codes[c]);
		code = codes[c];

		while (length > 0) {
			(verbose->out_stats)++;
			bit = code % 10;
			code /= 10;
			x |= bit;
			leftToByte--;
			length--;
			if (leftToByte == 0) {
				fputc(x, out);
				x = 0;
				leftToByte = 8;
			}
			x = x << 1;
		}
	}

	//dopelnienie 
	
	if (leftToByte != 8) {
		x <<= (leftToByte - 1);
		fputc(x, out);
	}

	verbose->in_stats *= 8;
	verbose->percent = ((double)verbose->out_stats/verbose->in_stats)*100;

	return verbose;
}
*/
/*
void compression_wrapper (int compression_type, FILE * in) {
	if (compression_type == 0)
		bit_8(in);
	else if (compression_type == 1)
		bit_12(in);
	else 	bit_16(in);
}

*/

//8bit reading wersja weroniki julii jastrzebskiej

char* bit_8(FILE* input) {
    char* symbols = malloc(SIZE8 * sizeof(char)); 
    if (symbols == NULL) {
        return NULL;
    }

    char c;
    char bit;
    char buf = 0b00000000;
    char mask = 0b10000000; 
    int i = 0;

    while ((c = fgetc(input)) != EOF) {
        for (i = 0; i < 8; i++) {
            bit = c & mask;
            c <<= 1;
            buf |= bit;

            if (i == 7) {
                symbols[i] = buf;
                buf = 0b00000000;
            }
        }
    }

    symbols[i] = buf;

    return symbols;
}


//12bit reading
uint16_t * bit_12(FILE * in) {//czy to zadziała????? kto wie
    uint16_t *symbols = malloc(SIZE12 * sizeof(uint16_t)); // zczytane symbole
    uint16_t c;
    uint16_t bit;
    uint16_t buf = 0b000000000000;
    uint16_t mask = 0b100000000000; // maska bierze pod uwagę tylko 1 bit wejścia
    int i;

    while ((c = fgetc(in)) != EOF) {
        for (i = 0; i < 12; i++) {
            bit = c & mask;
            c >>= 1; // przesuwamy w prawo, ponieważ czytamy dane w kolejności Little Endian
            buf |= bit;
        }
    }

    return symbols;
}

//16bit reading
uint16_t *bit_16(FILE *in) {
    uint16_t *symbols = malloc(SIZE16 * sizeof(uint16_t));
    uint16_t c;
    uint16_t bit;
    uint16_t buf = 0b0000000000000000;
    uint16_t mask = 0b1000000000000000;
    int i;

    while ((c = fgetc(in)) != EOF) {
        for (i = 0; i < 16; i++) {
            bit = c & mask;
            c <<= 1;
            buf |= bit;
        }

        if (i % 16 == 0) {
            symbols[i / 16 - 1] = buf;
            buf = 0b0000000000000000;
        }
    }

    if (i % 16 != 0) {
        symbols[i / 16] = buf;
    }


    return symbols;
}

