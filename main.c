#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prepfile.h"
#include "huffman.h"


/*
char * help = 
	"\n\tPOMOC\n\n
	składnia: ./huffman [plik wejściowy] [plik wyjściowy] [FLAGI] \n
	\tjeżeli plik wejściowy jest nieskompresowany\n
	\tto domyślnie zostanie skompresowany i przekazany jako plik wyjściowy\n
	\tjeżeli plik wejściowy jest skompresowany\n
	\tto domyślnie zostanie zdekompresowany i przekazany jako plik wyjściowy\n\n
	pomoc: ./huffman -h \n\t ./huffman h\n
	flagi:\n
	\t-c bezwzględnie skompresuj plik wejściowy\n"

*/

int main (int argc, char ** argv) {

/*	Takie rzeczy to w przyszłości XD
 *	if (argc == 2 && ( argv[1] == 'h' || (argv[1][0] == '-' && argv[1][1] == 'h') ) ){
		fprintf(stderr, help);
		return EXIT_FAILURE;
	}
*/
	if (argc != 3) {
	       	fprintf(stderr, "Podaj in i out\n");
		return EXIT_FAILURE;
	}

	FILE *in = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "w+");

	if (in == NULL) {
		fprintf(stderr, "Nie udało się otworzyć pliku wejściowego\n");
		return EXIT_FAILURE;
	}

	if (out == NULL) {
		fprintf(stderr, "Nie udało się otworzyć pliku wyjściowego\n");
		return EXIT_FAILURE;
	}

	//Trzeba napisać funkcję sprawdzającą czy input jest do zakodowania czy do zdekodowania

	if(checkInput(in))
		encode(in, out);
	else decode(in, out);
}
