#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define 8BIT_TABLE_SIZE 256
#define 12BIT_TABLE_SIZE 4096
#define 16BIT_TABLE_SIZE 65536

#define MAX_CHARS 256
#define length(x) ((int)log10(x)+1)

unsigned int * getFrequency (FILE * in) {
	char c;
	unsigned int * frequency = calloc(MAX_CHARS, sizeof(int));
	while ( (c=fgetc(in)) != EOF ) frequency[c]++;
	return * frequency;
}

//dopisac verbose

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

/*
void compression_wrapper (int compression_type, FILE * in) {
	if (compression_type == 0)
		8_bit(in);
	else if (compression_type == 1)
		12_bit(in);
	else 	16_bit(in);
}

*/

/* a dupa do wyrzucenia

//8bit reading

char * 8_bit(FILE * in) {

	char * symbols = malloc (8BIT_TABLE_SIZE * sizeof(char)); //zczytane symbole
	char c;
	char bit;
	char buf  = 0b00000000;
	char mask = 0b10000000; //maska bierze pod uwage tylko 1 bit wejscia
	int i;

	while ( (c = fgetc(input)) != EOF ) {
		
		for (i = 0; i < 8; i++) {
			bit = c & mask;
			c <<= 1;
			buf |= bit;
		}



//12bit reading

char * 12_bit(FILE * in) {

	char * symbols = malloc (12BIT_TABLE_SIZE * sizeof(char)); //zczytane symbole
	char c;
	char bit;
	char buf  = 0b000;
	char mask = 0b100; //maska bierze pod uwage tylko 1 bit wejscia
	int i;

	while ( (c = fgetc(input)) != EOF ) {
		
		for (i = 0; i < 8; i++) {
			bit = c & mask;
			c <<= 1;
			buf |= bit;
		}
	}
}

//16bit reading

char * 16_bit(FILE * in) {

	char * symbols = malloc (8BIT_TABLE_SIZE * sizeof(char)); //zczytane symbole
	char c;
	char bit;
	char buf  = 0b00000000;
	char mask = 0b10000000; //maska bierze pod uwage tylko 1 bit wejscia
	int i;

	while ( (c = fgetc(input)) != EOF ) {
		
		for (i = 0; i < 8; i++) {
			bit = c & mask;
			c <<= 1;
			buf |= bit;
		}
