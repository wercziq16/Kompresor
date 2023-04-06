#include <stdio.h>
#include <stdlib.h>

#include "help.h"
#include "input.h"
#include "huff.h"

#define MAX_CHARS 256

int main (int argc, char **argv)
{
	char * data = calloc(MAX_CHARS, sizeof(char));
	unsigned int * frequency = calloc(MAX_CHARS, sizeof(int));

	if (argc < 3) {
		print_help();
		return EXIT_FAILURE;
	}
		
	FILE * in = fopen(argv[2], "r");
	FILE * out = fopen(argv[3], "w");

	if (in == NULL) {
		print_in_open();
		print_help();
		return EXIT_FAILURE;
	}

	if (out == NULL) {
		print_out_open();
		print_help();
		return EXIT_FAILURE;
	}

	frequency = getFrequency(in);
	
}

	/*

	if ( atoi(argv[4][1] == 0) ) {
		if ( atoi(argv[4][2]) == 0 )
			compression_type = 8_bit;	
		else if ( atoi(argv[4][2] == 1) )
			compression_type = 12_bit;
		else if ( atoi(argv[4][2] == 2) )
			compression_type = 16_bit;
	} else compression_type = 8_bit;

	int compression_type = (atoi(argv[4][1]) == 0 && atoi(argv[4][2]) < 3) ? (atoi(argv[4][2])) : 0;

	*/



