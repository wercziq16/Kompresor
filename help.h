#ifndef _HELP_H_
#define _HELP_H_

#include <stdio.h>
#include <stdlib.h>

char * help = 	"Pomoc programu kompresor/dekompresor\n\
		 		Wywolanie:\n\
		 	\t ./huff [infile] [outfile] [flagi]\n";

char * in_open = "Nie udalo sie otworzyc pliku wejsciowego\n";
char * out_open = "Nie udalo sie otworzyc pliku wyjsciowego\n";

void print_help();

void print_in_open( );

void print_out_open( );

#endif
