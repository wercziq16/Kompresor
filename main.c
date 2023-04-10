#include <stdio.h>
#include <stdlib.h>
#include <string.h> //do strcmp
#include <stdint.h>

#include "suma.h"
#include "help.h"
#include "input.h"
#include "huffman16.h"
#include "frequency.h"
#include "dekompresor.h"
#include "kompresor.h"
#include "padding.h"

int main (int argc, char **argv)
{
		int compression_level = 0; // domyślnie brak kompresji
    	int show_stats = 0; // domyślnie nie wyświetlamy statystyk
    	int decompress = 0; // domyślnie tryb kompresji
    
   	 	// przeszukiwanie argumentów
    	for (int i = 3; i < argc; i++) {
        	if (strcmp(argv[i], "-0") == 0) {
            		compression_level = 0;
        	} else if (strcmp(argv[i], "-1") == 0) {
            		compression_level = 1;
        	} else if (strcmp(argv[i], "-2") == 0) {
            		compression_level = 2;
       		} else if (strcmp(argv[i], "-3") == 0) {
        	    	compression_level = 3;
       		} else if (strcmp(argv[i], "-v") == 0) {
           		 	show_stats = 1;
        	} else if (strcmp(argv[i], "-d") == 0) {
           		 	decompress = 1;
       		} else {
            		fprintf(stderr, "Nieznana flaga: %s\n", argv[i]);
            		exit(2);
       		}
  	  }	
    
	if (compression_level!=0 && decompress==1){
		fprintf(stderr, "Nie można jednocześnie skompresować i zdekompresować pliku.\n");
		exit(3);
	}

	if (show_stats==1 && decompress==1){
		fprintf(stderr, "Nie obsługujemy opcji pokazywania statystyk z dekompresji.\n");
		exit(4);
	}
	
	if (argc < 3) {
		print_help();
		exit(5);
	}

	if (strcmp(argv[1], argv[2])==0){
		fprintf(stderr, "Błąd. Podano ten sam plik na wejście i wyjście.\n");
		exit(6);
	}

	FILE * in = fopen(argv[1], "r");
	FILE * out = fopen(argv[2], "w");
	FILE * pfile = fopen("padded.txt", "w+");

	if (in == NULL) {
		print_in_open();
		print_help();
		exit(7);
	}

	if (out == NULL) {
		print_out_open();
		print_help();
		exit(8);
	}

	if (decompress == 0 && compression_level == 0)
	{
		uint16_t * frequency = getFrequency_8bit(in);
		uint16_t * data = data_maker(compression_level);
		uint16_t size = (uint16_t)MAX_CHARACTERS_8;
		huffmanCodes(data, frequency, size, compression_level, out);
		
	}
	else exit(9);
	
}

	
