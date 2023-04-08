#include <stdio.h>
#include <stdlib.h>
#include <string.h> //do strcmp

#include "suma.h"
#include "help.h"
#include "input.h"
#include "huff.h"

#define MAX_CHARS 256

int main (int argc, char **argv)
{
    	char * data = calloc(MAX_CHARS, sizeof(char));
	unsigned int * frequency = calloc(MAX_CHARS, sizeof(int));

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
            		printf("Nieznana flaga: %s\n", argv[i]);
            		exit(2);
       		 }
  	  }	
    
	if (compression_level!=0 && decompress==1){
		printf("Nie można jednocześnie skompresować i zdekompresować pliku.");
		exit(3);
	}

	if (show_stats==1 && decompress==1){
		printf("Nie obsługujemy opcji pokazywania statystyk z dekompresji.");
		exit(4);
	}
	
	if (argc < 3) {
		print_help();
		exit(5);
	}

	if (strcmp(argv[1], argv[2])==0){
		printf("Błąd. Podano ten sam plik na wejście i wyjście.");
		exit(6);
	}

	FILE * in = fopen(argv[2], "r");
	FILE * out = fopen(argv[3], "w");

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


	
