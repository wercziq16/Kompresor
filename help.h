#ifndef _HELP_H_
#define _HELP_H_

//pomieszalo mi sie header z c XDD poprawie w domu

char * help = 	"Pomoc programu kompresor/dekompresor\n\
		 Wywolanie:\n\
		 \t ./huff [infile] [outfile] [flagi]\n";

void print_help() {
	fprintf(stderr, help);
}

char * in_open = "Nie udalo sie otworzyc pliku wejsciowego\n"

void print_in_open() {
	fprintf(stderr, in_open);
}

char * out_open = "Nie udalo sie otworzyc pliku wyjsciowego\n"

void print_out_open() {
	fprintf(stderr, out_open);
}

#endif
